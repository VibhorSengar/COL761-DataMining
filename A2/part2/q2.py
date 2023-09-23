import numpy as np
import sys
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

if(len(sys.argv)<4):
    sys.exit("Not Enough Arguments.")

data = np.genfromtxt(sys.argv[1],dtype=np.float64,delimiter=" ")

def euclidean(a,b):
    sum=0
    for i in range(len(a)):
        sum+= (a[i]-b[i])**2
    return np.sqrt(sum)

variance = []
k = np.arange(1,16)
print(k)
for i in range(15):
    kmean = KMeans(n_clusters=i+1,n_init=10)
    kmean.fit(data)
    # sum_dist_from_cluster_center = 0
    # for j in range(len(data)):
    #     sum_dist_from_cluster_center+= euclidean(data[j], kmean.cluster_centers_[kmean.labels_[j]] )
    # variance.append(sum_dist_from_cluster_center/len(data))
    variance.append(kmean.inertia_)

variance=np.array(variance)
print(variance)
plt.title("Elbow Plot for dimension= "+sys.argv[2])
plt.xlabel("K")
plt.ylabel("Variation within cluster")
plt.plot(k,variance)
plt.savefig(sys.argv[3])