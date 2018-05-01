from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from mlxtend.plotting import plot_confusion_matrix
from sklearn.metrics import confusion_matrix
from sklearn.decomposition import PCA
from sklearn import preprocessing
import numpy as np
from random import shuffle
import time

# program constants
EPOCH_NUM = 30000
ALPHA = 0.001
PCA_NUM = 3


# this is the formula for the sigmoid function derivative
# the function argument is a matrix
def derivative(x):
    return x * (1.0 - x)


# our chosen activation function
# the function argument is a matrix
def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))


# measure run time
start = time.time()

# -------------------------------------------------------------------
with open('spambase.data') as f:
    lines = f.readlines()

# the data set is sorted by labels, we shuffle it in order to get better train/test sets
# notice that because of this shuffle the results may be different between runs
shuffle(lines)

tempX, tempY = [], []
for line in lines:
    curr = line.split(',')
    new_curr = [1.0]
    for item in curr[:len(curr) - 1]:
        new_curr.append(float(item))
    tempX.append(new_curr)
    tempY.append([float(curr[-1])])

# transform python lists to numpy matrices
X = np.array(tempX)
Y = np.array(tempY)

# from Neta:
# looking at the data set it appears that there are many points that are very close to each other
# we can disperse them a little to get a better graphical view of the data set without changing it
X = 1 + np.log(X + 0.01)

# take 80% for train and 25% for test
set_size = len(lines)
train_size = set_size * 80 // 100

# set part of the data set for training
X_train = X[:train_size]
Y_train = Y[:train_size]

# set part of the data set for testing
X_test = X[train_size:]
Y_test = Y[train_size:]
# -------------------------------------------------------------------

# -------------------------------------------------------------------
# feature scaling
# normalize X_train and save mean and std in object StandardScaler
scaler = preprocessing.StandardScaler()
X_train = scaler.fit_transform(X_train)

# pca = PCA(n_components=PCA_NUM)
pca = PCA()
Z = pca.fit_transform(X_train)
Z_train = Z[:, 0:PCA_NUM]

# set bias unit
Z_rows, Z_cols = Z_train.shape
Z_train_temp = np.ones((Z_rows, Z_cols + 1))
Z_train_temp[:, 1:Z_cols + 1] = Z_train
Z_train = Z_train_temp
# -------------------------------------------------------------------

# -------------------------------------------------------------------
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(Z_train[:, 1], Z_train[:, 2], Z_train[:, 3], c=Y_train[:, 0], marker='o')
ax.set_xlabel('Z0_train Feature')
ax.set_ylabel('Z1_train Feature')
ax.set_zlabel('Z2_train Feature')
plt.show()
# -------------------------------------------------------------------

# -------------------------------------------------------------------
# our ANN:

# we have 3 layers: input layer, hidden layer and output layer
# input layer has 4 nodes (1 for each feature + bias unit)
# hidden layer has 5 nodes (1 bias unit + 4 working neurons)
# output layer has 1 node
dim1 = Z_train.shape[1]
dim2 = 5

# randomly initialize the weight matrices to values between -1 to 1
np.random.seed(1)
weight1 = 2 * np.random.random((dim1, dim2)) - 1
weight2 = 2 * np.random.random((dim2, 1)) - 1

for j in range(EPOCH_NUM):
    # forward propagation: first evaluate the output for each training sample
    a_1 = Z_train
    v2 = np.dot(a_1, weight1)
    a_2 = sigmoid(v2)

    # ------------------------
    # add bias to layer_2
    a_2_rows, a_2_cols = a_2.shape
    a_2_temp = np.ones((a_2_rows, a_2_cols))
    a_2_temp[:, 1:a_2_cols + 1] = a_2[:, 1:a_2_cols + 1]
    a_2 = a_2_temp
    # ------------------------

    v3 = np.dot(a_2, weight2)
    a_3 = sigmoid(v3)

    # calculate the error, perform back propagation
    delta_3 = Y_train - a_3
    delta_2 = delta_3.dot(weight2.T) * derivative(a_2)

    # update the weight vectors
    weight2 += ALPHA * a_2.T.dot(delta_3)
    weight1 += ALPHA * a_1.T.dot(delta_2)
# -------------------------------------------------------------------

# -------------------------------------------------------------------
# scale according to train data
X_test = scaler.transform(X_test)

# pca transform according to train data
Z = pca.transform(X_test)
Z_test = Z[:, 0:PCA_NUM]

# set bias unit
Z_rows, Z_cols = Z_test.shape
Z_test_temp = np.ones((Z_rows, Z_cols + 1))
Z_test_temp[:, 1:Z_cols + 1] = Z_test
Z_test = Z_test_temp

# evaluation on the testing data
a_1 = Z_test
a_2 = sigmoid(np.dot(a_1, weight1))

# ------------------------
# add bias to layer_2
a_2_rows, a_2_cols = a_2.shape
a_2_temp = np.ones((a_2_rows, a_2_cols))
a_2_temp[:, 1:a_2_cols + 1] = a_2[:, 1:a_2_cols + 1]
a_2 = a_2_temp
# ------------------------

# layer 3 is y_hat - our prediction
a_3 = sigmoid(np.dot(a_2, weight2))

# add Y_hat_test to plot the predictions as probabilities and so clear distinction between spam and not spam
Y_hat_test = np.array(a_3)
# -------------------------------------------------------------------

# -------------------------------------------------------------------
# if the (prediction-val > 0.5) then label as spam=1 else label not-spam=0
correct = 0
for i in range(len(a_3)):
    if a_3[i][0] > 0.5:
        a_3[i][0] = 1
    else:
        a_3[i][0] = 0

    if a_3[i][0] == Y_test[i][0]:
        correct += 1

cm = confusion_matrix(Y_test, a_3)
# -------------------------------------------------------------------

# ------------------------------------------------
# show final result
print("mail samples in test set:\n%d" % len(a_3))
print("correct predictions:\n%d" % correct)
print("model accuracy:\n%.4f" % (correct * 100.0 / len(a_3)))
fig, ax = plot_confusion_matrix(conf_mat=cm)
plt.show()
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(Z_test[:, 1], Z_test[:, 2], Z_test[:, 3], c=Y_hat_test[:, 0], marker='o')
ax.set_xlabel('Z0_test Feature')
ax.set_ylabel('Z1_test Feature')
ax.set_zlabel('Z2_test Feature')
plt.show()
# ------------------------------------------------

end = time.time()
print("Run Time is sec: %.3f" % (end - start))
