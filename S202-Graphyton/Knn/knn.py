import minkowski
nbPoints=0
while(nbPoints<2 or nbPoints>100):
    print("Combien de points souhaitez-vous générer (vous devez générer au moins 2 points et au plus 100 points) ?")
    nbPoints=int(input())
valMax=0
while(valMax<1 or valMax>15000):
    print("Quel est la valeur maximum que vous souhaitez que le programme génère (elle doit être comprise entre 1 et 1 500) ?")
    valMax=int(input())
nDim=0
while(nDim<2 or nDim>10):
    print("Combien de dimensions souhaitez-vous ([2;10] dimensions) ?")
    nDim=int(input())
if (nDim==2):
    import manhattan
    dist=manhattan.distMatrice2D(minkowski.gen.gen(nbPoints,valMax))  #generation des points, assignement des étiquettes et calcul des résultats
    dist=sorted(dist,key=lambda dist: dist[0]) #tri des résultats
elif (nDim==3):
    import euclidienne
    dist=euclidienne.distMatrice3D(minkowski.gen.gen(nbPoints,valMax,3)) #generation des points, assignement des étiquettes et calcul des résultats
    dist=sorted(dist,key=lambda dist: dist[0]) #tri des résultats
else:
    import chebyshev
    dist=chebyshev.distMatriceND(minkowski.gen.gen(nbPoints,valMax,nDim),nDim) #generation des points, assignement des étiquettes et calcul des résultats
    dist=sorted(dist,key=lambda dist: dist[0]) #tri des résultats
k=0
while(k<1 or k>(nbPoints**2)-nbPoints):
    print("Combien de distances souhaitez-vous considérer (le maximum considérable est ",(nbPoints**2)-nbPoints, ") ?")
    k=int(input())

menu=-1
while(menu!=0):
    print("Tapez 0 pour : quitter le programme.")
    print("Tapez 1 pour : afficher les k premières valeurs générées.")
    print("Tapez 2 pour : afficher les k premières valeurs différentes générées.")
    print("Tapez 3 pour : obtenir les étiquettes des k premières valeurs générées.")
    print("Tapez 4 pour : effectuer une classification sur les k premières valeurs générées.")
    print("Tapez 5 pour : effectuer une régression sur les k premières valeurs générées.")
    menu=int(input())
    if (menu==0):
        print("Arrêt du programme.\n")
    elif (menu==1):
        print(minkowski.afficheKval(dist,k),"\n")
    elif (menu==2):
        print(minkowski.afficheKvalDiff(dist,k),"\n")
    elif (menu==3):
        print(minkowski.obtenirEtiquettes(dist,k),"\n")
    elif (menu==4):
        minkowski.classification(dist,k)
    elif (menu==5):
        print("La moyenne des k premières valeurs générées est ",minkowski.regression(dist,k),"\n")
    else:
        print("Erreur, signification de la valeur inconnue.\n")