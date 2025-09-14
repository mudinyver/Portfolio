import genPoint as gen
from collections import Counter
A=22
B=1057


def obtenirEtiquettes(dist,k):
    lEti=[]
    for i in range (k):
        lEti.append(dist[i][1])
    return lEti

def regression(dist,k):
    numerateur=0
    for i in range (k):
        numerateur+=(dist[i][0])
    return numerateur/k

def classification(dist,k):
    lEti=[]
    for i in range (k):
        lEti.append(dist[i][0])
    most_common_numbers = Counter(lEti).most_common(k)
    nbOccurences=most_common_numbers[0][1]
    maxi=most_common_numbers[0][0]
    for a in range (len(most_common_numbers)):
        if most_common_numbers[a][1] > nbOccurences:
            nbOccurences=most_common_numbers[a][1]
            maxi=most_common_numbers[a][0]
    print("Le nombre ",maxi," apparait ",nbOccurences," fois.\n")
    
def afficheKval(dist,k):
    pr=[]
    for i in range (k):
        pr.append(dist[i][0])
    return pr

def afficheKvalDiff(dist,k):
    lEti=[]
    valDiff=[]
    for i in range (k):
        lEti.append(dist[i][0])
    most_common_numbers = Counter(lEti).most_common(k)
    for a in range (len(most_common_numbers)):
        valDiff.append(most_common_numbers[a][0])
    return valDiff
