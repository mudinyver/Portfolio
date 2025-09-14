import math
import minkowski

def calDist3D(p1,p2):
    dist=0
    for n in range (3):
        dist+=(p1[n]-p2[n])**2
    return math.sqrt(dist)

def distMatrice3D(dataPoint):
    dist=[]
    e=0
    for i in range (len(dataPoint)):
        for j in range (len(dataPoint)):
            if (i!=j):
                e+=1
                dist.append((calDist3D(dataPoint[i],dataPoint[j]),e,i,j))
    return dist

def printDist3D(dist): #f() utilisée pour le développement (à l'image d'un toString en java)
    e=0
    for i in range (minkowski.A):
        pr=[]
        for j in range (minkowski.A): 
            pr.append(dist[e])
            e+=1
        print(pr,"\n")