# -*- coding: utf-8 -*-

from skimage import io
from sklearn.cluster import KMeans
import numpy as np

image = io.imread('fethers.png')
io.imshow(image)
io.show()

rows = image.shape[0]
cols = image.shape[1]
 
image = image.reshape(image.shape[0]*image.shape[1],3)
print("building k menas model")
kmeans = KMeans(n_clusters = 12, n_init=10, max_iter=200)
print("kmeans started..")
kmeans.fit(image)
print("kmeans finsdhed")

clusters = np.asarray(kmeans.cluster_centers_,dtype=np.uint8) 
labels = np.asarray(kmeans.labels_,dtype=np.uint8 )  
labels = labels.reshape(rows,cols); 

np.save('codebook_fethers.npy',clusters)    
io.imsave('compressed_fethers.png',labels);



