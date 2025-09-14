import minkowski

def calDist2D(p1,p2):
    dist=0
    for n in range (2):
        dist+=abs(p1[n]-p2[n])
    return dist

def distMatrice2D(dataPoint):
    dist=[]
    e=0
    for i in range (len(dataPoint)):
        for j in range (len(dataPoint)):
            if (i!=j):
                e+=1
                dist.append((calDist2D(dataPoint[i],dataPoint[j]),e,i,j))
    return dist

def printDist2D(dist): #f() utilisée pour le développement (à l'image d'un toString en java)
    e=0
    for i in range (minkowski.A):
        pr=[]
        for j in range (minkowski.A):
            pr.append(dist[e])
            e+=1
        print(pr,"\n")