import numpy as np
import matplotlib.pyplot as plt

def generatePoints(dimension, amounts, clusters, data_range, distance):
    centers = [[round(np.random.uniform(data_range[0], data_range[1]), 3) for i in range(dimension)] for j in range(clusters)]
    #distance = 4#(data_range[1]-data_range[0])/clusters
    points = centers
    for i in range(amounts-clusters):
        group = np.random.randint(0, clusters)
        points = np.append(points, [[round(np.random.uniform(centers[group][j], centers[group][j]+distance), 3) for j in range(dimension)]], axis = 0)
    return points

n = generatePoints(2,50,3,(0,1000), 90)
m = np.array(n)
# plt.scatter(m[:,0], m[:,1])
# plt.show()
np.savetxt("2d-sample-1.txt", m,fmt='%.3f')