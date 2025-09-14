import math
import minkowski

def calDistND(p1,p2,n):
    dist=[]
    for i in range (n):
        dist.append(abs(p1[i]-p2[i]))
    return max(dist)

def distMatriceND(dataPoint,n):
    dist=[]
    e=0
    for i in range (len(dataPoint)):
        for j in range (len(dataPoint)):
            if (i!=j):
                dist.append((calDistND(dataPoint[i],dataPoint[j],n),e))
                e+=1
    return dist

def printDistND(dist):  #f() utilisée pour le développement (à l'image d'un toString en java)
    e=0
    for i in range (minkowski.A):
        pr=[]
        for j in range (minkowski.A):
            pr.append(dist[e])
            e+=1
        print(pr,"\n")