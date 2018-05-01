%%
% When Is the Standard Deviation Equal to Zero?:
% https://www.thoughtco.com/when-standard-deviation-equal-to-zero-3126506

% kernel SVM:
% https://www.quora.com/What-are-kernels-in-machine-learning-and-SVM-and-why-do-we-need-them
% https://www.youtube.com/watch?v=19cI5rehcxI&index=70&list=PL0Smm0jPm9WcCsYvbhPCdizqNKps69W4Z

%%
clc; clear all; format compact; close all;

%%
% read hw data set
% instead of trying to reduce to my own data set from the original 10% UCI
% data set...I will use the provided data set but along with using randperm 
% I will also shuffle the rows first in python 

hw_data_set = csvread('kdd_for_HW_original.csv');
%hw_data_set = csvread('kdd_for_HW_original_py_shuffled.csv');
[rows, cols] = size(hw_data_set);

% https://www.mathworks.com/help/matlab/ref/randperm.html
% https://www.mathworks.com/help/matlab/ref/rng.html

% rng
% rng('shuffle');
p = randperm(rows);

X = hw_data_set(p, 1:end-1);
Y = hw_data_set(p, end);

[rowsX, colsX] = size(X);

%%
% do cross validation on X
% even when choosing k=10 I get the same pattern of CM outputs...

k = 5;
bin_size = rowsX/k;
bin_indices = crossvalind('kfold', rowsX, k);

for i=1:k
    
    % division to train/test sets
    [X_train, X_test, Y_train, Y_test] = train_test_division(X, Y, bin_indices, i);
    
    % normalize the train data to have 0 mean and 1 standart deviation.
    % https://www.mathworks.com/help/stats/zscore.html
    [X_train_normlz ,mean, std] = zscore(X_train);

    % transform normalized train data to new space calc' using PCA
    [eigenvecs, Z_train, eigenvals] = do_pca(X_train_normlz);
   
    % plot eigenvalues/lambdas
    figure;
    plot(eigenvals,'*');
    title(['eigenvalues/lambdas bin=', num2str(i)]);
    
    % plot 3-tuple feature cols consecutively, 3 times
    for j=1:3
        figure; 
        scatter3(Z_train(:,0+j),Z_train(:,1+j),Z_train(:,2+j), 25, Y_train, 'filled');
        xlabel(['Ztrain(',num2str(0+j),')']);
        ylabel(['Ztrain(',num2str(1+j),')']);
        zlabel(['Ztrain(',num2str(2+j),')']);
        title(['plot Ztrain: bin=', num2str(i)]);
    end
    
    % choose how many lambdas i.e. in the new space how many axis will we
    % have, how many principal components(pcs) 
    % try with 3 to see sub' diff' between LR and SVM
    num_of_pcs = 6; 
    Z_train = Z_train(:,1:num_of_pcs);
    
    % normalize the test data to have 0 mean and 1 std.
    % use values calculated before for train set
    X_test_normlz = my_normlz(mean, std, X_test);
    
    % transform normalized test data to new space calc' using PCA
    % use values calculated before for train set
    Z_test = X_test_normlz*eigenvecs;
    Z_test = Z_test(:,1:num_of_pcs);
    
    % logistic regression
    Y_hat_test_LR = my_logistic_regression(Z_train, Y_train, Z_test);
    Y_hat_test_SVM = my_svm_2(Z_train, Y_train, Z_test);
    Y_hat_test_kernel_SVM = my_kernel_svm_2(Z_train, Y_train, Z_test);
    
    % calc' confusion matrix for logistic regression and SVM
    % notice: logistic regression predicts probabilities
    CM_LR = confusionmat(Y_test, round(Y_hat_test_LR));
    disp_cm(CM_LR, i, 'CM_LR for iter/bin: ');
    CM_SVM = confusionmat(Y_test, Y_hat_test_SVM);
    disp_cm(CM_SVM, i, 'CM_SVM for iter/bin: ');
    CM_kernel_SVM = confusionmat(Y_test, Y_hat_test_SVM);
    disp_cm(CM_kernel_SVM, i, 'CM_kernel_SVM for iter/bin: ');
    disp('--------------------------------'); 
    
end


% close all;
disp('#DONE#');



