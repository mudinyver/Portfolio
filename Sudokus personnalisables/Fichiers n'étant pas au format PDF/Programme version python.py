import colorama
#importation d'une bibliothèque pour permettre la colorisation
from colorama import Fore
from colorama import Style

import random  #importation d'une bibliothèque pour la génération partielle de grilles


def programme():

  grille = [[7, 8, 0, 4, 0, 0, 1, 2, 0], 
            [6, 0, 0, 0, 7, 5, 0, 0, 9],
            [0, 0, 0, 6, 0, 1, 0, 7, 8], 
            [0, 0, 7, 0, 4, 0, 2, 6, 0],
            [0, 0, 1, 0, 5, 0, 9, 3, 0], 
            [9, 0, 4, 0, 6, 0, 0, 0, 5],
            [0, 7, 0, 3, 0, 0, 0, 1, 2], 
            [1, 2, 0, 0, 0, 7, 4, 0, 0],
            [0, 4, 9, 2, 0, 6, 0, 0, 7]]
  #modèle de choix inspiré de mon projet en première
  generateur = -1 #variable de choix pour le mode primaire
  while generateur < 0 or generateur > 3:
    if generateur < 0 or generateur > 3:
      print(
          "Souhaitez vous résoudre un Sudoku (0), en générer un (1), en entrer manuellement un (2) ou bien en en choisissant un dans la liste des Sudoku entrés manuellement (3)?"
      )
      generateur = int(input())
    else:
      pass
  ordre1 = -1 #variable de choix pour le mode génération
  ordre2 = -1 #variable de choix pour le mode génération
  if generateur == 1:
    print(
        "Quel ordre de grille, compris entre 3 et 16, souhaitez vous générer ?"
    )
    while ordre1 < 3 or ordre1 > 16:
      ordre1 = int(input())
      if ordre1 < 3 or ordre1 > 16:
        print(
            "Quel ordre de grille, compris entre 3 et 16, souhaitez vous générer ?"
        )
      else:
        pass
    print(
        "Si vous souhaitez garder une grille carré taper 2 sinon taper le nombre de colonne que vous voulez (compris entre 3 et 16 inclus)."
    )
    while ordre2 < 2 or ordre2 > 16:
      ordre2 = int(input())
      if ordre2 < 2 or ordre2 > 16:
        print(
            "Si vous souhaitez garder une grille carré taper 0 sinon taper le nombre de colonne que vous voulez (compris entre 3 et 16 inclus)."
        )
      else:
        pass
    if ordre2 == 2:
      #si la grille est carré (voir print plus haut)
      ordre2 = ordre1
      ordre = ordre1
      #ordre = plus grand ordre entre orde1 et ordre2
    else:
      if ordre2 > ordre1:
        ordre = ordre2
      else:
        ordre = ordre1
    grille = []
    for o in range(ordre1):
      grille.append([0] * (ordre2))
    #crée une grille remplie de 0 aux dimensions voulues par l'utilisateur
    random_nb = [0]
    random_verif = []
    while random_nb != random_verif:
      random_nb = random.sample(range(ordre + 1), 4)
      #crée une liste de 4 nombres aléatoires entre 1 et ordre+1
      random_verif = []
      for element in random_nb:
        if element not in random_verif:
          random_verif.append(element)
        else:
          if element == 0:
            random_verif.append(element)
          else:
            pass
        #s'assure que les 4 nombres sont différents
    grille[0][0], grille[0][ordre2 - 1], grille[ordre1 - 1][0], grille[ordre1 - 1][ordre2 -1] = random_nb[0], random_nb[1], random_nb[2], random_nb[3]
    #affecte 1 des 4 nombres aux 4 coins de la grille
  elif generateur == 2:
    print(
        "Veuillez entrer une grille de Sudoku valide en entrant les lignes une par une (par exemple: 123)\n",
        "Entrez @ pour arrêter la saisie. \n")
    manuel = []
    i = 0
    manuel.append(input())
    manuel[i] = list(manuel[i])
    #transforme la chaine de caractères en éléments de liste
    print(manuel)
    while "@" not in manuel[i]:
      i += 1
      manuel.append(input())
      manuel[i] = list(manuel[i])
      print(manuel)
    print()  #saut de ligne
    manuel.remove(manuel[i])
    #supprime le dernier élément de la liste, qui contient le caractère "@"
    if manuel == []:
      print(
          print(Fore.RED + Style.BRIGHT +
                "Erreur : Vous n'avez pas entré de grille de Sudoku." +
                Style.RESET_ALL))
      #la grille n'est pas sauvegardée donc la fonction error n'est pas utilisée.
      programme()
      exit()
      #pour que le programme ne continue pas après avoir fini la fonction programme, il est stoppé de force
    else:
      pass
    #la partie de code suivante sert à transformer les numéros entre guillemets en numéro classique (ex: "1" en 1).
    nb = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
    nb = "".join(str(nb))
    nb = list(nb)
    for a in range(len(manuel)):
      if len(manuel[0])!=len(manuel[a]):
        print(
          print(Fore.RED + Style.BRIGHT +
                "Erreur : Les lignes de votre grille n'ont pas toutes la même longueur." +
                Style.RESET_ALL))
        #la grille n'est pas sauvegardée donc la fonction error n'est pas utilisée.
        programme()
        exit()
      else:
        pass
      for b in range(len(manuel[0])):
        if manuel[a][b] in nb:
          manuel[a][b] = int(manuel[a][b])
        else:
          pass
    sauvegarde.append(manuel)
    #pour le mode sauvegarde
    grille = manuel
  elif generateur == 3:
    #mode sauvegarde
    if sauvegarde == []:
      print(
          print(
              Fore.GREEN + Style.BRIGHT +
              "Vous n'avez pas encore entré de grille de Sudoku valide manuellement. Une grille 9*9 préfaite sera donc utilisée."
              + Style.RESET_ALL))
    else:
      if (grille[len(grille) - 1]) == [0]:
        grille.remove(grille[len(grille) - 1])
      else:
        pass
      #résout un problème qui se produit en ajoutant "[0]" à la matrice
      for i in range(len(sauvegarde)):
        print("choix ", i + 1, " = ", sauvegarde[i])
      print()  #saut de ligne
      print("Entrez un nombre entre 1 et", len(sauvegarde), "inclus.")
      save_chx = -1
      while save_chx < 1 or save_chx > len(sauvegarde):
        save_chx = int(input())
        if save_chx < 1 or save_chx > len(sauvegarde):
          print("Entrez un nombre entre 1 et", len(sauvegarde), "inclus.")
        else:
          pass
      grille = sauvegarde[save_chx - 1]
      print(grille)
  else:
    #mode résolution
    pass

  def error():
    #fonction appelé lorsqu'une erreur qui demande potentiellement l'annulation de la dernière grille entré manuellement survient
    if generateur == 2:
      sauvegarde.remove(sauvegarde[len(sauvegarde) - 1])
    else:
      pass
    programme()
    exit()

  #https://www.cours-gratuit.com/tutoriel-python/tutoriel-python-transformer-une-liste-en-matrice-une-matrice-en-liste
  #J'ai utilisé ce site pour les lignes servant à détecter que des listes sont plus grandes que d'autres et pour ajouter les 0.
  rectangle = len(min(grille, key=len))
  rectanglax = len(max(grille, key=len))
  rectanglonne = 0
  rectangligne = 0
  X_pos = 0
  Source1 = (-1, -1)  #localisation de la ligne de l'erreur
  Source2 = (-1, -1)  #localisation de la colonne de l'erreur
  liste_regions = [] #une matrice comprenant une liste de nombres/lettres par région

  nb_varia = len(grille)
  tirets = nb_varia  #variable pour l'affichage des tirets à la fin
  if nb_varia < 2 or nb_varia > 16:
    print(
        print(Fore.RED + Style.BRIGHT +
              "Erreur : grille trop petite ou trop grande." + Style.RESET_ALL))
    error()
  else:
    pass

  #si la grille n'est pas carré
  if rectangle != nb_varia or rectanglax != nb_varia:
    if rectangle < nb_varia:
      if rectangle != rectanglax:
        #Fait en sorte que les listes soient toutes de même longueur.
        grille = [x + [0] * (rectanglax - len(x)) for x in grille]
        rectanglonne = nb_varia - rectangle
      elif nb_varia < rectanglax:
        print("Votre grille n'est ni rectangulaire ni carré.")
        error()
      else:
        grille = [x + [0] * (nb_varia - len(x)) for x in grille]
        rectanglonne = nb_varia - rectangle
    elif rectangle > nb_varia:
      #Quand le nompbre de listes dans la matrice est inférieur au nombre de nombres dans les listes de la matrice
      for i in range(rectangle - nb_varia):
        grille.append([0])  #rajoute une liste à la matrice
        grille = [x + [0] * (rectanglax - len(x)) for x in grille
                  ]  #Rend la liste ajouté de même longueur aux autres.
        rectangligne += 1
      print(
          "Il manque au moins une ligne à votre grille pour qu'elle soit carré."
      )
      print()  #saut de ligne
    elif rectanglax != nb_varia:
      print("Votre grille n'est ni rectangulaire ni carré.")
      error()
    else:
      pass
    print(Fore.GREEN + Style.BRIGHT + "Votre grille n'est pas carrée." +
          Style.RESET_ALL)
    print(
        "Le programme prendra en charge votre grille comme si elle était carré avant d'effacer les éléments qui ont tranformé votre grille en grille carré."
    )
    print()  #saut de ligne
    nb_varia = len(grille)
    X_pos = 1  #Mode X non disponible pour les grilles rectangulaires parce que cela n'aurait pas beaucoup de sens.
  else:
    pass

  indispo = -1
  if nb_varia > 16:
    while indispo < 0 or indispo > 1:
      print(
          "Les grilles supérieur à 16*16 ne sont malheuresement pas bien pris en charge par le programme pour le moment néanmoins une conversion de nombres en leur base ",
          nb_varia,
          "est possible, souhaitez vous la faire ? (0 pour oui et 1 pour tenter de résoudre le Sudoku.)"
      )
      indispo = int(input())
    print()  #saut de ligne
  else:
    pass

  reg_pos = [1]  #possibilités de la taille de la région

  for i in range(2, 26):
    if nb_varia % i == 0:
      reg_pos.append(i)
  #ajoute les nombres qui divisent la longueur de la grille à la liste

  print("Soit n et k des entiers naturels > 0 et n ≠ k.")
  print(
      "Il est recommandé de choisir les régions de type n*n ou de type n-k*n si la première option n'existe pas ."
  )
  print()  #saut de ligne
  print("Voici les types de régions possibles pour votre grille", nb_varia,
        "*", nb_varia, ":")

  for i in range(len(reg_pos)):
    print("choix ", i + 1, " = ", reg_pos[i], "*", nb_varia // reg_pos[i])
  print()  #saut de ligne
  print(
      "Veuillez entrez le type de région que vous voulez en entrant le numéro de votre choix de 1 à",
      len(reg_pos), ".")
  print()  #saut de ligne
  if generateur == 0:
    print(
        "ALERTE : selon le type de région que vous choisissez votre Sudoku peut être insoluble."
    )
  else:
    pass

  chx = 0
  while chx < 1 or chx > len(reg_pos):
    chx = int(input())
    if chx < 1 or chx > len(reg_pos):
      print(
          "Veuillez entrez le type de région que vous voulez en entrant le numéro de votre choix de 1 à",
          len(reg_pos), ".")
    else:
      pass
  for i in range(len(reg_pos)):
    if chx == i + 1:  #i commençant à 0 et chx à 1
      reg_1 = reg_pos[i]
      reg_2 = nb_varia // reg_pos[i]
    else:
      pass
  print()  #saut de ligne

  X = -1
  if X_pos == 0:
    #si la grille est carré
    while X < 0 or X > 1:
      if X < 0 or chx > 1:
        print("Souhaitez vous activer le mode Sudoku X (0 : oui, 1 : non) ?")
        X = int(input())
      else:
        pass
    if X == 0:
      print("Le mode sudoku X est activé.")
      print("Je vous préviens : il va falloir être patient.")
    else:
      pass
    print()  #saut de ligne
  else:
    pass

  diago1 = []  #diago en /
  diago2 = []  #diago en \
  for i in range(nb_varia):
    diago1.append(grille[i][i])
    diago2.append(grille[i][(nb_varia - i - 1)])

  def solve(bo, nb_varia):
    find = find_empty(bo)  #voir fonction find_empty(bo) trouvable bien plus bas.
    if not find:
      return True  #si le programme ne trouve plus de 0 alors cela veut dire que le sudoku est terminé.
    else:
      row, col = find  #le programme va récupérer les coordonnées du 0.

    for i in range(1, nb_varia + 1):
      if valid(bo, i, (row, col)):
        bo[row][col] = i  #si un nombre est valide il est enregistré

        if solve(bo, nb_varia):
          return True  #solution trouvée
        bo[row][col] = 0
    return False  #valeur annulée

  def valid(bo, num, pos):
    #check ligne
    for i in range(len(bo[0])):
      if bo[pos[0]][i] == num and pos[1] != i:
        return False
    #check colonne
    for i in range(len(bo[0])):
      if bo[i][pos[1]] == num and pos[0] != i:
        return False
    if reg_1 != 1 or reg_2 != 1:  #une région ayant 1 en paramètre n'a aucun intérêt.
      #check régions
      region_x = pos[1] // reg_1
      region_y = pos[0] // reg_2

      for i in range(region_y * reg_2, region_y * reg_2 +
                     reg_2):  #étendue de la région en lignes
        for j in range(region_x * reg_1, region_x * reg_1 +
                       reg_1):  #étendue de la région en colonnes
          if bo[i][j] == num and (i, j) != pos:
            return False
          else:
            pass
    else:
      pass
    if X == 0:
      for i in range(len(bo)):
        for e in range(len(bo[0])):
          #check diagonales
          if (num == bo[i][i] and (i, i) != pos and bo[i][i] != 0
              and pos == (e, e)) == True:
            #print(bo[i][i], (i,i))
            return False
          elif (num == bo[i][nb_varia - i - 1] and (i, nb_varia - i - 1) != pos
                and bo[i][nb_varia - i - 1] != 0
                and pos == (e, nb_varia - e - 1)) == True:
            #print(bo[i][nb_varia-i-1], (i,nb_varia-i-1))
            return False
          else:
            pass
    else:
      pass
    return True

  chiffres = "0123456789"
  symboles = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  lettres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

  def convertion(nb):
    for i in range(36):
      if nb == symboles[i]:
        return i  #i commençant par 0, A est le 10ème symbole
      else:
        pass

  def grande_grille():
    if nb_varia > 9:
      for i in range(1, nb_varia + 1):
        for j in range(1, nb_varia + 1):
          if i - 1 >= 0 and j - 1 >= 0 and i - 1 < len(grille) and j - 1 < len(
              grille[0]):  #fait pour éviter les problèmes
            if grille[i - 1][j - 1] != 0:  #pour les tests
              #grille[i-1][j-1] = grille[i-1][j-1]-1
              #dièse en haut fait pour les générateurs hexadécimaux allant de 1 à G au lieu de 0 à F
              grille[i - 1][j - 1] = symboles[(grille[i - 1][j - 1])] if (
                  grille[i - 1][j - 1]) <= nb_varia else print("Erreur")
            else:
              grille[i - 1][j - 1] = "Ø"
          else:
            pass
    else:
      pass

  dico={}

  def convertion_dico(dico, bo, mode):
    if mode ==0:
      for i in range(len(bo)):
        for j in range(len(bo[0])):
          for a in range (len(dico)):
            if list(dico.keys())[a] == (i, j):
              bo[i][j]=0
            else:
             pass
      return bo
    elif mode==1:
      for i in range(len(bo)):
        for j in range(len(bo[0])):
          for a in range (len(dico)):
            if list(dico.keys())[a] == (i,j):
              bo[i][j]=(list(dico.values())[a])
            else:
              pass
      return bo
    else:
      pass
  
  def print_grille(dico, bo, tirets, S1, S2):
    if S1 != (-1, -1):
      #s'il n'y a pas eu d'erreurs
      grande_grille()
    else:
      pass
    if generateur ==1:
      bo=convertion_dico(dico, bo, 0)
    else:
      pass
      
    barres = 0
    for i in range(len(bo)):
      if i % reg_2 == 0 and i != 0:
        #affiche des lignes horizontales pour délimiter les régions
        #lignes préprogrammées
        if nb_varia == 9 and reg_1 == reg_2:
          print("- - - - - - - - - - - -")
        elif reg_2 == 1:
          pass
        elif nb_varia == 2 and reg_1 == reg_2:
          print("- - - -")
        elif nb_varia == 4 and reg_1 == reg_2:
          print("- - - - - -")
        elif nb_varia == 6 and (reg_1 == 2 or reg_2 == 2):
          print("- - - - - - - - -")
        elif nb_varia == 8 and (reg_1 == 2 or reg_2 == 2):
          print("- - - - - - - - - - - - -")
        elif nb_varia == 12 and (reg_1 == 3 or reg_2 == 3):
          print("- - - - - - - - - - - - - - - - -")
        elif nb_varia == 16 and reg_1 == reg_2:
          print("- - - - - - - - - - - - - - - - - - - - -")
        #lignes pour toutes les régions douteuses et autres régions non-préprogrammées
        else:
          print("- " * (tirets + barres // reg_1 + reg_2 // reg_2))

      for j in range(len(bo[0])):
        if j % reg_1 == 0 and j != 0:
          #affiche des lignes verticales pour délimiter les régions
          if reg_1 != 1:
            print(" | ", end="")
          else:
            pass
          barres += 1
        if j == nb_varia - 1:  #si arrivé à fin de ligne
          if (i, j) == S2 or (i, j) == S1:
            print(Fore.RED + Style.BRIGHT + str(bo[i][j]) + Style.RESET_ALL)
          elif X == 0 and ((i, j) == (i, i) or
                           (i, j) == (i, nb_varia - i - 1)):
            #La couleur est importante pour le mode X.
            print(Fore.BLUE + Style.BRIGHT + str(bo[i][j]) + Style.RESET_ALL)
          else:
            print(bo[i][j])
        else:
          if (i, j) == S2 or (i, j) == S1:
            print(Fore.RED + Style.BRIGHT + str(bo[i][j]) + " ",
                  end="" + Style.RESET_ALL)
          elif X == 0 and ((i, j) == (i, i) or
                           (i, j) == (i, nb_varia - i - 1)):
            print(Fore.BLUE + Style.BRIGHT + str(bo[i][j]) + " ",
                  end="" + Style.RESET_ALL)
          else:
            print(str(bo[i][j]) + " ", end="")
    if generateur ==1:
      bo=convertion_dico(dico, bo, 1)
    else:
      pass

  def find_empty(bo):
    for i in range(len(bo)):
      for j in range(len(bo[0])):
        if bo[i][j] == 0:
          return (i, j)
    return None  #si la fonction trouve un 0 elle renvoie son emplacement

  def viabilite(bo):
    for i in range(len(bo)):
      for j in range(len(bo)):
        if bo[i][j] != 0:
          for y in range(len(bo)):
            if bo[i][j] == bo[y][j] and (y, j) != (i, j):
              print(
                  print(
                      Fore.RED + Style.BRIGHT + "Erreur : Grille non viable\n",
                      "Source : Le nombre", bo[y][j],
                      "se répète deux fois sur la colonne", y,
                      "." + Style.RESET_ALL))
              Source1 = (y, j)
              Source2 = (i, j)
              print_grille(dico, bo, tirets, Source1, Source2)
              error()
            elif bo[i][j] == bo[i][y] and (i, y) != (i, j):
              print(
                  print(
                      Fore.RED + Style.BRIGHT + "Erreur : Grille non viable\n",
                      "Source : Le nombre", bo[i][y],
                      "se répète deux fois sur la ligne", y,
                      "." + Style.RESET_ALL))
              Source1 = (i, y)
              Source2 = (i, j)
              print_grille(dico, bo, tirets, Source1, Source2)
              error()
            else:
              pass
    if reg_1 != 1 or reg_2 != 1:  #une région ayant 1 en paramètre n'a aucun intérêt.
      liste_regions = region()
      viab_reg = []
      for e in range(len(liste_regions)):
        #inspiré de https://www.delftstack.com/fr/howto/python/remove-duplicates-from-list-python/
        for element in liste_regions[e]:
          if element not in viab_reg:
            viab_reg.append(element)
          else:
            if element == 0:
              viab_reg.append(element)
            else:
              pass
        if viab_reg != liste_regions[e]:
          print(
              print(Fore.RED + Style.BRIGHT + "Erreur : Grille non viable\n",
                    "Source : Un nombre se répète deux fois dans la région",
                    e + 1, "." + Style.RESET_ALL))
          Source1 = (-2, -2)
          Source2 = (-2, -2)
          print_grille(dico, bo, tirets, Source1, Source2)
          #la fonction error n'est pas utilisée car le problème ne justifie pas la suppression de la grille sauvegardée.
          programme()
          exit()
        else:
          viab_reg = []
    else:
      pass
    if X == 0:
      diago = []
      diago.append(diago1)
      diago.append(diago2)
      viab_diago = []
      for e in range(2):
        #inspiré de https://www.delftstack.com/fr/howto/python/remove-duplicates-from-list-python/
        for element in diago[e]:
          if element not in viab_diago:
            viab_diago.append(element)
          else:
            if element == 0:
              viab_diago.append(element)
            else:
              pass
        if viab_diago != diago[e]:
          if e == 0:
            print(
                print(
                    Fore.RED + Style.BRIGHT + "Erreur : Grille non viable\n",
                    "Source : Un nombre se répète deux fois sur la diagonale en \."
                    + Style.RESET_ALL))
            #la fonction error n'est pas utilisée car le problème ne justifie pas la suppression de la grille sauvegardée.
            programme()
            exit()
          elif e == 1:
            print(
                print(
                    Fore.RED + Style.BRIGHT + "Erreur : Grille non viable\n",
                    "Source : Un nombre se répète deux fois sur la diagonale en /."
                    + Style.RESET_ALL))
            #la fonction error n'est pas utilisée car le problème ne justifie pas la suppression de la grille sauvegardée.
            programme()
            exit()
          else:
            pass
          Source1 = (-2, -2)
          Source2 = (-2, -2)
          print_grille(dico, bo, tirets, Source1, Source2)
        else:
          viab_diago = []
    else:
      pass

  if nb_varia > 9 and X != 0:
    #si le message n'as pas déja été mis et que l'ordre de la grille est >9
    print("Je vous préviens : il va falloir être patient.")
  else:
    pass

  if generateur != 1:
    #si nous ne sommes pas dans le mode génération
    print_grille(dico, grille, tirets, Source1, Source2)
  else:
    pass

  def region():
    a = 0
    liste_regions = []
    if reg_1 != 1 or reg_2 != 1:
      for i in range(len(grille)):
        for j in range(len(grille[0])):
          region_0 = []
          region_p = j // reg_1
          region_o = i // reg_2
          for e in range(region_o * reg_2, region_o * reg_2 +
                         reg_2):  #étendue de la région en lignes
            for m in range(region_p * reg_1, region_p * reg_1 +
                           reg_1):  #étendue de la région en colonnes
              region_0.append(grille[e][m])
          if region_0 not in liste_regions:
            #ce bout de code repasse par des régions déjà vues d'où cette solution
            liste_regions.append(region_0)
          else:
            comparaison = [0] * (len(grille))
            if region_0 == comparaison:
              a += 1
              if a % len(grille) == 0:
                liste_regions.append(region_0)
                #solution à un problème générée par la solution du dessus
                #sert à permettre plusieurs régions remplis de 0
              else:
                pass
            else:
              pass
    else:
      liste_regions = []
    return liste_regions

  if nb_varia > 9:
    for i in range(1, nb_varia + 1):
      for j in range(1, nb_varia + 1):
        if (str(grille[i - 1][j - 1]) in lettres) == True:
          grille[i - 1][j - 1] = convertion(grille[i - 1][j - 1])
          #le diez suivant est pour les sudoku où 0 est valide
          #grille[i-1][j-1] = grille[i-1][j-1]+1
        elif grille[i - 1][j - 1] == "Ø":
          grille[i - 1][j - 1] = 0
        else:
          pass
  else:
    pass

  def verif(bo, nb_varia):
    if (str(bo[nb_varia - 1][nb_varia - 1]) in symboles) == True:
      for i in range(1, nb_varia + 1):
        for j in range(1, nb_varia + 1):
          if (str(grille[i - 1][j - 1]) in chiffres) == True:
            if (bo[i - 1][j - 1] < nb_varia + 1) == False:
              print(
                  print(
                      Fore.RED + Style.BRIGHT +
                      "Erreur : chiffre trop grand pour la grille.\n",
                      "Pour rappel les chiffres utilisées doivent être des entiers positifs et inférieurs à la taille de votre grille."
                      + Style.RESET_ALL))
              error()
            else:
              pass
          elif (str(grille[i - 1][j - 1]) in lettres) == True:
            print(
                print(
                    Fore.RED + Style.BRIGHT +
                    "Erreur : caractère alphabétique détecté alors que la longeur de la grille est inférieur à 10."
                    + Style.RESET_ALL))
            error()
          elif (str(grille[i - 1][j - 1]) in symboles) == False:
            if nb_varia < 10:
              print(
                  print(Fore.RED + Style.BRIGHT +
                        "Erreur : caractère non pris en charge détecté." +
                        Style.RESET_ALL))
              error()
            else:
              pass
          elif (grille[i - 1][j - 1] > -1) == False:
            print(
                print(
                    Fore.RED + Style.BRIGHT +
                    "Erreur : chiffre trop petit pour la grille.\n",
                    "Pour rappel les chiffres utilisées doivent être des entiers positifs et inférieurs à la taille de votre grille."
                    + Style.RESET_ALL))
            error()
          else:
            print(
                print(Fore.RED + Style.BRIGHT +
                      "Erreur : caractère incorrect détecté" +
                      Style.RESET_ALL))
            error()
    else:
      print(
          print(Fore.RED + Style.BRIGHT + "Erreur inconnue" + Style.RESET_ALL))
      error()

  if generateur != 1:
    #si nous ne sommes pas dans le mode génération
    verif(grille, nb_varia)
    viabilite(grille)
  else:
    pass

  if indispo == 0:
    #si le mode secondaire conversion est activé
    pass
  else:
    solve(grille, nb_varia)
    

  if generateur == 1:
    pass
  elif nb_varia == 9:
    print("_______________________\n")
  elif nb_varia == 4:
    print("___________\n")
  elif nb_varia == 2:
    print("_______\n")
  elif nb_varia == 6:
    print("_________________\n")
  elif nb_varia == 8:
    print("_________________________\n")
  elif nb_varia == 12:
    print("________________________________\n")
  elif nb_varia == 16:
    print("__________________________________\n")
  else:
    print("__________________\n")

  grande_grille()

  insoluble = 0
  for i in range(len(grille)):
    for j in range(len(grille)):
      if grille[i][j] == 0 or grille[i][j] == "Ø":
        insoluble = 1
      else:
        pass
    #rogner la grille carré complétée pour la transfromer en grille rectangulaire
    if rectangligne != 0:
      for e in range(rectangligne):
        grille[nb_varia - e - 1][i] = " "
    elif rectanglonne != 0:
      for e in range(rectanglonne):
        grille[i][nb_varia - e - 1] = " "
    else:
      pass

  def neutralisation(suppr):
    dico={}
    print(
        "Souhaitez vous avoir une diffucltée plutot facile (1), moyenne (2), difficile (3) ou aléatoire (4) ?"
    )
    difficulte = -1
    while difficulte < 0 or difficulte > 4:
      difficulte = int(input())
      if difficulte < 0 or difficulte > 4:
        print("Entrez un nombre entre 1 et 4 inclus.")
      else:
        pass
    if difficulte == 3:
      i = ((ordre1 * (ordre2 - 1)), 1)
    elif difficulte == 2:
      i = (((ordre1 * (ordre2 - 1)) // 2) + ((ordre1 * (ordre2 - 1)) // 4), 1)
    elif difficulte == 1:
      i = (((ordre1 * (ordre2 - 1)) // 2) - (ordre // 3), 1)
    else:
      i = random.sample(range(ordre, ordre1 * (ordre2 - 1)), (1))
    for j in range(i[0]):
      efface1 = random.sample(range(ordre1), (1))
      efface2 = random.sample(range(ordre2), (1))
      dico[(efface1[0], efface2[0])] = suppr[efface1[0]][efface2[0]]
      #suppr[efface1[0]][efface2[0]] = 0
    return (dico)

  if generateur == 1:
    print_grille(neutralisation(grille), grille, tirets, Source1, Source2)
  else:
    print_grille(dico, grille, tirets, Source1, Source2)
  if insoluble == 1:
    print()  #saut de ligne
    print(
        "La grille n'est pas soluble ou le programme n'as pas réussi à la résoudre."
    )
    print()  #saut de ligne
    print(
        "Cela est peut-être du à votre grille, à votre choix de région, à l'activation du mode Sudoku X ou bien au fait que vous avez choisi que le programme ne résolve pas la grille de Sudoku."
    )
  else:
    pass

  if X == 1 or X_pos == 1:
    croix = "classique"
  else:
    if nb_varia != 16:
      croix = "X"
    else:
      croix = "super challenger (16*16 et mode Sudoku X)"

  if rectangligne != 0 or rectanglonne != 0:
    carrangle = "avec grille rectangulaire"
  else:
    carrangle = ""
  if indispo == 0:
    indispo = "Conversion"
  else:
    indispo = "Résolution"
  if generateur == 1:
    indispo = "Génération"
  else:
    pass
  print()  #saut de ligne
  print("Grille :\n", nb_varia - rectangligne, "*", nb_varia - rectanglonne,
        "\n Type de région :\n", reg_1, "*", reg_2, "\n", "Mode :\n", "Sudoku",
        croix, carrangle, "\n", indispo)

  def solus_et_diff():
    print()  #saut de ligne
    resol = -1
    print(
        "Souhaitez vous que le programme résolve ce sudoku ? (0 : oui, 1 : non."
    )
    while resol < 0 or resol > 1:
      resol = int(input())
      if resol < 0 or resol > 1:
        print(
            "Souhaitez vous que le programme résolve ce sudoku ? (0 : oui, 1 : non."
        )
      else:
        pass
    if resol == 0:
      #problème le programme n'enregistre pas la version de la grille avant la neutralisation
      print_grille(dico, grille, tirets, Source1, Source2)
    else:
      pass
    ajustement = -1
    print(
        "Souhaitez vous changer la difficultée de la grille ? (0 : oui, 1 : non."
    )
    while ajustement < 0 or ajustement > 1:
      ajustement = int(input())
      if ajustement < 0 or ajustement > 1:
        print(
            "Souhaitez vous changer la difficultée de la grille ? (0 : oui, 1 : non."
        )
      else:
        pass
    if ajustement == 0:
      print_grille(neutralisation(grille), grille, tirets, Source1, Source2)
      solus_et_diff()
    else:
      pass

  if generateur == 1:
    solus_et_diff()
  else:
    pass

  
  re = -1
  print("On est repartis pour un tour ? (0 : oui, 1 : non.")
  while re < 0 or re > 1:
    re = int(input())
    if re < 0 or re > 1:
      print("On est repartis pour un tour ? (0 : oui, 1 : non.")
    else:
      pass
  if re == 0:
    programme()
  else:
    print("Au revoir.")


sauvegarde = []
programme()
