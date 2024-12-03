/**
*
* \brief Snake V4
* 
* \author UDIN--YVER Mael, étudiant de l'IUT de Lannion, département informatique, groupe TP 1D1
*
* \version 1.07
*
* \date 24 octobre 2024
*
* Ce programme propose de diriger un serpent dans un jeu de snake amélioré
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>
#include <time.h>

// Constantes.


/** \def SERPENT
*
* \brief Taille du serpent au début du programme.
*/
const int SERPENT=10; 


/** \def LIM1
*
* \brief Valeur minimale que l'utilisateur peut saisir pour les coordonnées.
*/
const int LIM1=1;


/** \def LIM2X
*
* \brief Valeur maximale que l'utilisateur peut saisir pour les coordonnées.
*/
const int LIM2X=80;

/** \def LIM2Y
*
* \brief Valeur maximale que l'utilisateur peut saisir pour les coordonnées.
*/
const int LIM2Y=40;


/** \def APPARITION_X
*
* \brief Point d'apparition de la tête du serpent en X.
*/
const int APPARITION_X=40;


/** \def APPARITION_Y
*
* \brief Point d'apparition de la tête du serpent en Y.
*/
const int APPARITION_Y=20;


/** \def TEMPORISATION
*
* \brief constante pour usleep()
*/
const int TEMPORISATION=200000;
// const int TEMPORISATION=50000;

/** \def ACCELERRE
*
* \brief constante pour le pas d'accélération du serpent
*/
const int ACCELERRE=TEMPORISATION/20;


/** \def TETE
*
* \brief caractere representant la tete du serpent
*/
const int TETE='O';


/** \def CORPS
*
* \brief caractere representant un élément du corps du serpent autre que la tete.
*/
const int CORPS='X';


/** \def LIM_VISUELLES
*
* \brief caractere representant un élément d'une limite.
*/
const char LIM_VISUELLES='#';


/** \def COMP_PAVE
*
* \brief caractere representant un élément d'un pavé.
*/
const char COMP_PAVE='#';

/** \def NB_PAVE
*
* \brief nombre de pavés dans la grille de jeu.
*/
const int NB_PAVE=4;

/** \def TAILLE_PAVE
*
* \brief Taille des pavés.
*/
const int TAILLE_PAVE=5;

/** \def POMME
*
* \brief Design des pommes.
*/
const char POMME='6';

/** \def LIM_POMMES
*
* \brief Nombre de pommes que le serpent doit manger avant que progresser ne s'arrête.
*/
const int LIM_POMMES=10;

/** \def PORTAIL
*
* \brief Design des portails (usage interne) pour les différencier du vide
*/
const char PORTAIL='/';

/** \def PORTAIL
*
* \brief Design des portails (visible)
*/
const char PORTAIL_VIS=' ';

/** \def VIDE
*
* \brief Design des espaces vides
*/
const char VIDE=' ';

/** \def TAILLE_PORTAIL_X
*
* \brief Taille des portails en X
*/
const int TAILLE_PORTAIL_X=LIM2X/LIM2X;

/** \def TAILLE_PORTAIL_Y
*
* \brief Taille des portails en Y
*/
const int TAILLE_PORTAIL_Y=LIM2Y/LIM2Y;

/** \def EMPLACEMENT_PORTAIL
*
* \brief LIM2 / EMPLACEMENT_PORTAIL = endroit du portail
*/
const int EMPLACEMENT_PORTAIL=2; //milieu


/** \def DROITE
*
* \brief Caractère représentant la direction "droite"
*/
const char DROITE='d';

/** \def GAUCHE
*
* \brief Caractère représentant la direction "gauche"
*/
const char GAUCHE='q';

/** \def HAUT
*
* \brief Caractère représentant la direction "haut"
*/
const char HAUT='z';

/** \def BAS
*
* \brief Caractère représentant la direction "bas"
*/
const char BAS='s';

/** \def DIRECTION_DEFAUT
*
* \brief Direction (correspondant au caractère) vers laquelle va le serpent par défaut.
*/
const char DIRECTION_DEFAUT=DROITE;


/** \def STOP
*
* \brief Caractère représentant la touche à appuyer pour stopper le programme.
*/
const char STOP='a';




// Constantes symboliques.

/**
* \def NB_LIGNES
* \brief Taille maximale de la dimension 1 d'un tableau.
*
* Taille maximale de la dimension 1 d'un tableau de type t_tabChar.
*/
# define NB_LIGNES 100

/**
* \def NB_COLONNES
* \brief Taille maximale de la dimension 2 d'un tableau.
*
* Taille maximale de la dimension 2 d'un tableau de type t_tabChar.
*/
# define NB_COLONNES 100








// Nouveaux types.

/**
* \typedef t_tabInt
* \brief Type tableau de NB_LIGNES en dimension 1 et NB_COLONNES en dimension 2
*
*/
typedef int t_tabInt[NB_LIGNES][NB_COLONNES];

/**
* \typedef t_tabChar
* \brief Type tableau de NB_LIGNES en dimension 1 et NB_COLONNES en dimension 2
*
*/
typedef int t_tabChar[NB_LIGNES][NB_COLONNES];









// Prototypes des procedures et fonctions.
// Les détails sont sous le main().
void afficher(int x, int y, char c);
void effacer(int x, int y);
void dessinerSerpent(t_tabChar tabDess);
void progresser(t_tabChar tabProg, char direction, bool *adr_aPercute, bool *adr_aMange);
void gotoXY(int x, int y);
int kbhit();
void initPlateau(t_tabChar aInitialiser);
void init(t_tabInt aInitialiser);
void enableEcho();
void disableEcho();
void parcours_tableau(t_tabChar aParcourir, t_tabChar emplacement);
char selec_direction(char direction, t_tabChar hautBas_gaucheDroite);
void traqueDernier(t_tabInt aEffacer, int tSerpent, bool plusUn);
void plateauVertical(int x, int y);
void plateauHorizontal(int x);
void dessinerPlateau(int x, int y);
void dessinePave(int x, int y, t_tabChar aRemplir);
void ajouterPomme(t_tabChar tPlateau);








// Programme principal

/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal invoque plusieurs fonctions et procédures détaillées plus bas.
*/
int main(){
	srand(time(NULL));
	bool aPercute=false, aMange=false;
    t_tabChar plateau;
	system("clear");
	dessinerPlateau(LIM2X, LIM2Y);  //affichage des limites
	initPlateau(plateau);
	enableEcho();
    plateau[APPARITION_X][APPARITION_Y]=TETE;
	dessinerSerpent(plateau);
	ajouterPomme(plateau);
    progresser(plateau, DIRECTION_DEFAUT, &aPercute, &aMange);
	system("clear");
	enableEcho();
	printf("\n");
	if (aPercute==true){
		printf("Vous avez failli à votre tâche. Souhaitez-vous retenter votre chance ? je n'attends pas de réponses. J'attends des actes.\n");
	}
	else if (aMange==true){
		printf("Si vous avez mangé %d pommes alors vous avez réussi. Félicitations.\n", LIM_POMMES);
	}
	return EXIT_SUCCESS; //la procédure progresser arrête de s'exécuter en cas de collision
	//, le programme doit alors s'arrêter
}

// Procédures et fonctions.


/**
*
* \fn void init(t_tabInt aInitialiser)
* \brief Procédure qui initialise le tableau donné en paramètre.
* \param aInitialiser : Paramètre d'entrée/sortie représentant le tableau à initialiser
*
*/
void init(t_tabInt aInitialiser){
	int i, j;
	for (i=0; i<NB_LIGNES; i++){
		for (j=0; j<NB_COLONNES; j++){
			aInitialiser[i][j]=0;
		}
	}
}

/**
*
* \fn void initPlateau(t_tabChar aInitialiser)
* \brief Procédure qui initialise le plateau/grille de jeu
* \param aInitialiser : Paramètre d'entrée/sortie représentant le plateau
*
*/
void initPlateau(t_tabChar aInitialiser){
	int empPortX, empPortY;
	empPortX=LIM2X/EMPLACEMENT_PORTAIL;
	empPortY=LIM2Y/EMPLACEMENT_PORTAIL;
	int i, j, alea1=-10, alea2=-10;
	for (i=1; i<NB_LIGNES; i++){
		for (j=1; j<NB_COLONNES; j++){
			if ((i==LIM1) || (j==LIM1) || (i==LIM2X) || (j==LIM2Y)){
				//si bordures
				if ((j>=empPortY-TAILLE_PORTAIL_Y/2) && (j<=empPortY+TAILLE_PORTAIL_Y/2)){
					aInitialiser[i][j]=PORTAIL;
				}
				else if ((i>=empPortX-TAILLE_PORTAIL_X/2) && (i<=empPortX+TAILLE_PORTAIL_X/2)){
					aInitialiser[i][j]=PORTAIL;
				}
				else{
					aInitialiser[i][j]=COMP_PAVE;
				}
			}
			else{
				aInitialiser[i][j]=VIDE;
			}
		}
	}
	bool ok=false;
	for (int paveBoucle=0;paveBoucle<NB_PAVE;paveBoucle++){
		ok=false;
		while (ok==false){
			alea1=-10;
			alea2=-10;
			while ((alea1<LIM1+2) || (alea1>LIM2X-(TAILLE_PAVE+2))){
        		alea1=rand() % (LIM2X+1); //résultat entre 0 et LIM2X
    		}
			while ((alea2<LIM1+2) || (alea2>LIM2Y-(TAILLE_PAVE+2))){
        		alea2=rand() % (LIM2Y+1); //résultat entre 0 et LIM2Y
    		}
			if ((((alea1<APPARITION_X-(SERPENT+TAILLE_PAVE)) || (alea1>APPARITION_X+3)) && ((alea2>APPARITION_Y) || (alea2<APPARITION_Y+TAILLE_PAVE+1)))){
				//si le pavé ne déborde pas sur l'espace réservé au serpent
				ok=true;
			}
		}
		dessinePave(alea1, alea2, aInitialiser);
	}
}


/**
* \fn void afficher(int x, int y, char c).
* \brief Procédure qui affiche un caractère.
* \param x : paramètre d'entrée qui représente les coordonnées, en x, de l'élément à afficher.
* \param y : paramètre d'entrée qui représente les coordonnées, en y, de l'élément à afficher.
* \param c : paramètre qui indique quelle caractère doit être afficher.
*
*/
void afficher(int x, int y, char c){
	enableEcho();
	fflush(stdout); //sert à l'affichage progressif d'une ligne
    gotoXY(x,y);
    printf("%c", c);
	disableEcho();
//     Cette procédure doit afficher le caractère c à la position (x, y), où x représente le numéro de colonne
// et y le numéro de ligne
}


/**
* \fn void effacer(int x, int y).
* \brief Procédure qui rempalce un caractère par VIDE.
* \param x : paramètre d'entrée qui représente les coordonnées, en x, de l'élément à remplacer.
* \param y : paramètre d'entrée qui représente les coordonnées, en y, de l'élément à remplacer.
* Procédure qui rempalce un caractère par VIDE.
*/
void effacer(int x, int y){
	enableEcho();
	fflush(stdout);
	gotoXY(x,y);
    printf(VIDE);
	disableEcho();
//     Cette procédure doit afficher un espace à la position (x, y), où x représente le numéro de colonne et y
// le numéro de ligne.
}


/**
* \fn void parcours_tableau(t_tabChar aParcourir, t_tabChar emplacement)
* \brief Procédure qui parcours un tableau pour renseigner l'emplacement du serpent.
* \param aParcourir : paramètre d'entrée/sortie qui représente le tableau à parcourir.
* \param emplacement : paramètre d'entrée/sortie qui représente le tableau où noter les emplacements du serpent.
* Procédure qui parcours un tableau t_tabChar pour renseigner 
* l'emplacement de toutes les parties du serpent dans le tableau emplacement.
*/
void parcours_tableau(t_tabChar aParcourir, t_tabInt emplacement){
	// parcours d'un tableau
	init(emplacement);
	int indice1, indice2, nb_parties_serpent=1;
	for (indice1=0 ; indice1<NB_LIGNES ; indice1++){
	// accès ou modif de tab[i]
		for (indice2=0 ; indice2<NB_COLONNES ; indice2++){
			if (aParcourir[indice1][indice2]==TETE){
					emplacement[0][0]=indice1;
					emplacement[1][0]=indice2;
			}
			if (aParcourir[indice1][indice2]==CORPS){
				emplacement[0+nb_parties_serpent][0+nb_parties_serpent]=indice1;
				emplacement[1+nb_parties_serpent][0+nb_parties_serpent]=indice2;
			}
		}
	}
}



/**
* \fn void dessinerSerpent(t_tabChar tabDess)
* \brief Procédure qui dessine le serpent.
* \param tabDess : paramètre d'entrée/sortie qui représente la grille (plateau de jeu)
*
* Procédure chargée d’afficher à l’écran un à un les éléments du serpent dont les coordonnées
* sont fournies dans le tableau donné en paramètre emplacement après le lancement de la 
* procédure parcours_tableau
*/
void dessinerSerpent(t_tabChar tabDess){
	t_tabInt emplacement;
	parcours_tableau(tabDess, emplacement);
	afficher(emplacement[0][0], emplacement[1][0], TETE);
    tabDess[emplacement[0][0]][emplacement[1][0]]=TETE;  //màj de tabDess
	if (emplacement[0][0]!=1){
		/** s'arrête si la taille du serpent dépasse la taille de la constante SERPENT */
		for (int i=0; (i<emplacement[0][0]) && (i<SERPENT); i++){
			afficher((emplacement[0][0]-(i+1)), emplacement[1][0], CORPS);
			tabDess[emplacement[0][0]-(i+1)][emplacement[1][0]]=CORPS; //màj de tabDess
		}
	}
	enableEcho();
	printf("\n");
	disableEcho();
}


/**
* \fn void plateauVertical(int x, int y)
* \brief Procédure qui dessine la partie verticale des limites
* \param x : nombre d'espaces entre les LIM_VISUELLES
* \param y : nombre de LIM_VISUELLES à afficher
*
*/
void plateauVertical(int x, int y){
	int empPortY=LIM2Y/EMPLACEMENT_PORTAIL;
	for (int i=0; i<y-1; i++){
		if ((i>=(empPortY-TAILLE_PORTAIL_Y/2)-1) && (i<empPortY+TAILLE_PORTAIL_Y/2)){
			printf("%c",PORTAIL_VIS);
		}
		else{
			printf("%c",LIM_VISUELLES);
		}
        for (int j=0; j<x-1; j++){
            printf(VIDE);
        }
		if ((i>=(empPortY-TAILLE_PORTAIL_Y/2)-1) && (i<empPortY+TAILLE_PORTAIL_Y/2)){
			printf("%c",PORTAIL_VIS);
		}
		else{
			printf("%c",LIM_VISUELLES);
		}
		printf("\n");
    }
}


/**
* \fn void plateauHorizontal(int x)
* \brief Procédure qui dessine la partie horizontale de la limite
* \param x : nombre de LIM_VISUELLES à afficher
*/
void plateauHorizontal(int x){
	int empPortX=LIM2X/EMPLACEMENT_PORTAIL;
    for (int i=1; i<x+1; i++){
        if ((i>=empPortX-TAILLE_PORTAIL_X/2) && (i<=empPortX+TAILLE_PORTAIL_X/2)){
			printf("%c",PORTAIL_VIS);
		}
		else{
			printf("%c",LIM_VISUELLES);
		}
    }
}




/**
* \fn void dessinerPlateau(int x, int y)
* \brief Procédure qui appelle les procédures chargés de dessiner la limite
* \param x : paramètre d'entrée pour les procédures appelées
* \param y : paramètre d'entrée numéro 2 pour plateauVertical()
*
* Appelle les procédures chargés de dessiner les différentes
* limites
*/
void dessinerPlateau(int x, int y){
	enableEcho();
	plateauVertical(x,y);
	plateauHorizontal(x);
	gotoXY(LIM1,LIM1);
	plateauHorizontal(x);
	disableEcho();
}




/**
* \fn void progresser(t_tabChar tabProg, char direction, bool *adr_aPercute, bool *adr_aMange)
* \brief Procédure qui fait avancer le serpent.
* \param tabProg : paramètre d'entrée/sortie qui représente la grille (plateau de jeu)
* \param direction : paramètre d'entrée ne servant quasiment à rien en tant que paramètre
* \param adr_aPercute : paramètre de sortie signalant si la procédure s'est arrêtée en raison d'un percutage ou non
* \param adr_aMange : paramètre de sortie signalant si la procédure s'est arrêtée car elle a mangee plus de LIM_POMMES ou non
*
* Procédure chargée de remplacer la tête du serpent par un élément du corps et d'afficher la tête.
*/
void progresser(t_tabChar tabProg, char direction, bool *adr_aPercute, bool *adr_aMange){
	int arret=0, i=1, tailleSerpent=SERPENT, unErBoucleProg=0, pas=TEMPORISATION, tp1, tp2, telepAffichePas=0, pomme=0;
	char raccourcir=VIDE;
	t_tabInt emplacement, zqsd, aEffacer;
	zqsd[0][0]=0; //hautBas
	zqsd[1][0]=1;  //gaucheDroite
	init(aEffacer);
	parcours_tableau(tabProg, emplacement);
	aEffacer[0][0]=emplacement[0][0]-tailleSerpent;
	aEffacer[1][0]=emplacement[1][0];
	while (i<(tailleSerpent+1)){ 
		//enregistrement des emplacement par défaut des parties du serpent
		aEffacer[i][i]=aEffacer[0][0]+i;
		aEffacer[1+i][i]=aEffacer[1][0];
		i++;
	}
	while (arret!=1){
		unErBoucleProg++;
		parcours_tableau(tabProg, emplacement);
		effacer(aEffacer[0][0], aEffacer[1][0]);
		tabProg[aEffacer[0][0]][aEffacer[1][0]]=VIDE;  //màj du plateau
		traqueDernier(aEffacer, tailleSerpent, false);
		afficher(emplacement[0][0], emplacement[1][0], CORPS); //remplacement de la tête
		afficher(emplacement[0][0]+zqsd[1][0], emplacement[1][0]+zqsd[0][0], TETE); //affichage de la tête selon la direction
		tabProg[emplacement[0][0]][emplacement[1][0]]=CORPS; //màj du plateau
		raccourcir=tabProg[emplacement[0][0]+zqsd[1][0]][emplacement[1][0]+zqsd[0][0]];
		if (raccourcir==COMP_PAVE || raccourcir==CORPS){
			//si percutage
			*adr_aPercute=true;
			return ; //return void, sert à arrêter la procédure
		}
		else if (raccourcir==POMME){
			*adr_aMange=true;
			tailleSerpent++;
			traqueDernier(aEffacer, tailleSerpent, true);
			pas-=ACCELERRE;
			ajouterPomme(tabProg);
			pomme++;
			if (pomme>LIM_POMMES){
				return ; //return void, sert à arrêter la procédure
			}
		}
		//si pomme> 5 alors return;
		if (raccourcir==PORTAIL){
			tp1=0;
			tp2=0;
			effacer(emplacement[0][0]+zqsd[1][0], emplacement[1][0]+zqsd[0][0]); 
			if (emplacement[0][0]+zqsd[1][0]==LIM1){
				tp1=LIM2X-1;
				tp2=emplacement[1][0];
				tabProg[tp1][tp2]=TETE;
			}
			else if (emplacement[0][0]+zqsd[1][0]==LIM2X){
				tp1=LIM1+1;
				tp2=emplacement[1][0];
				tabProg[tp1][tp2]=TETE;
			}
			else if (emplacement[1][0]+zqsd[0][0]==LIM1){
				tp1=emplacement[0][0];
				tp2=LIM2Y-1;
				tabProg[tp1][tp2]=TETE;
				tabProg[tp1][LIM1]=PORTAIL;
				afficher(tp1, LIM1, PORTAIL_VIS);
			}
			else if (emplacement[1][0]+zqsd[0][0]==LIM2Y){
				tp1=emplacement[0][0];
				tp2=LIM1+1;
				tabProg[tp1][tp2]=TETE;
				tabProg[tp1][LIM2Y]=PORTAIL;
				afficher(tp1, LIM2Y, PORTAIL_VIS);
			}
			telepAffichePas++;
			parcours_tableau(tabProg, emplacement);
		}
		if (unErBoucleProg<SERPENT+1){ 
			//sert à effacer une partie du serpent qui traine dans le VIDE et à garder la taille du serpent à SERPENT au début
			effacer(APPARITION_X-tailleSerpent+unErBoucleProg, APPARITION_Y);
			tabProg[APPARITION_X-tailleSerpent+unErBoucleProg][APPARITION_Y]=VIDE;
		}
		if (telepAffichePas==0){
			tabProg[emplacement[0][0]+zqsd[1][0]][emplacement[1][0]+zqsd[0][0]]=TETE; //màj du plateau
			//les 2 aEffacer suivant ajoutent la tête du serpent à la liste d'éléments à effacer
			aEffacer[tailleSerpent-1][tailleSerpent-1]=emplacement[0][0]+zqsd[1][0];
			aEffacer[tailleSerpent][tailleSerpent-1]=emplacement[1][0]+zqsd[0][0];
		}
		else{
			telepAffichePas--;
			//les 2 aEffacer suivant ajoutent la tête du serpent à la liste d'éléments à effacer
			aEffacer[tailleSerpent-1][tailleSerpent-1]=tp1;
			aEffacer[tailleSerpent][tailleSerpent-1]=tp2;
		}
		enableEcho();
		printf("\n");
		disableEcho();
		usleep(pas);
		direction=selec_direction(direction, zqsd);
		if (direction==STOP){
			arret=1;
		}
	}
}


/**
* \fn void traqueDernier(t_tabInt aEffacer, int tSerpent, bool plusUn)
* \brief Procédure qui décale les éléments du tableau aEffacer
* \param aEffacer : paramètre d'entrée/sortie représentant le tableau à modifier
* \param tSerpent : paramètre d'entrée représentant la taille du serpent
* \param plusUn : paramètre d'entrée booléen. Définit le sens de décalage des éléments du tableau
* Procédure qui décale les éléments du tableau aEffacer vers la gauche.
*/
void traqueDernier(t_tabInt aEffacer, int tSerpent, bool plusUn){
	int i=tSerpent-1;
	if (plusUn==true){
		aEffacer[tSerpent][tSerpent]=aEffacer[tSerpent-1-i][tSerpent-1-i];
		aEffacer[tSerpent][tSerpent]=aEffacer[tSerpent-i][tSerpent-1-i];
	}
	else{
		while (i>0){
			aEffacer[tSerpent-1-i][tSerpent-1-i]=aEffacer[tSerpent-i][tSerpent-i];
			aEffacer[tSerpent-i][tSerpent-1-i]=aEffacer[tSerpent-(i-1)][tSerpent-i];
			i--;
		}
	}
	// while (i>0){
	// 	aEffacer[tSerpent-1-i][tSerpent-1-i]=aEffacer[tSerpent-i][tSerpent-i];
	// 	aEffacer[tSerpent-i][tSerpent-1-i]=aEffacer[tSerpent-(i-1)][tSerpent-i];
	// 	i--;
	// }
}


/**
* \fn char selec_direction(char direction, t_tabChar hautBas_gaucheDroite)
* \brief Fonction qui réagit aux caractères entrés par l'utilisateur
* \param direction : direction du serpent à l'appel de la fonction
* \param hautBas_gaucheDroite : direction du serpent à l'appel de la fonction
* \return retourne un charactère pouvant être a,d,s,q ou z
*
* Fonction qui réagit aux caractères entrés par l'utilisateur en regardant
* si ces derniers servent à indiquer une direction futur n'étant pas à
* l'opposé de la direction inidiqué dans le paramètre du même nom.
* Est aussi chargé de détecter la saisie de la touche STOP.
*/
char selec_direction(char direction, t_tabInt hautBas_gaucheDroite){
	char chgt=direction;
	char onTourne=direction; 
	if (kbhit()==1){
		scanf("%c", &chgt);
		if (chgt==STOP){
			onTourne=STOP;
		}
		//droite
		else if ((chgt==DROITE) && (direction!=GAUCHE)){
			hautBas_gaucheDroite[1][0]=1;
			hautBas_gaucheDroite[0][0]=0;
			onTourne=DROITE;
		}
		//bas
		else if ((chgt==BAS) && (direction!=HAUT)){
			hautBas_gaucheDroite[1][0]=0;
			hautBas_gaucheDroite[0][0]=1;
			onTourne=BAS;
		}
		//gauche
		else if ((chgt==GAUCHE) && (direction!=DROITE)){
			hautBas_gaucheDroite[1][0]=-1;
			hautBas_gaucheDroite[0][0]=0;
			onTourne=GAUCHE;
		}
		//haut
		else if ((chgt==HAUT) && (direction!=BAS)){
			hautBas_gaucheDroite[1][0]=0;
			hautBas_gaucheDroite[0][0]=-1;
			onTourne=HAUT;
		}
	}
	return onTourne;
}


/**
* \fn void dessinePave(int x, int y, t_tabChar aRemplir)
* \brief Procédure qui dessine les pavés
* \param x : coordonnées, en x ,de l'élément le plus en haut à gauche du pavé
* \param y : coordonnées, en y ,de l'élément le plus en haut à gauche du pavé
* \param aRemplir : plateau où marquer les coordonnées des éléments du pavé
*
* Procédure qui dessine un pavé en fonction de son élément le plus en haut 
* à gauche
*/
void dessinePave(int x, int y, t_tabChar aRemplir){
	enableEcho();
	gotoXY(x,y);
	for (int i=0; i<TAILLE_PAVE; i++){
		for (int j=0; j<TAILLE_PAVE; j++){
			printf("%c", COMP_PAVE);
			aRemplir[x+i][y+j]=COMP_PAVE;
		}
		gotoXY(x,y+(i+1)); //passer à la ligne
	}
	disableEcho();
}



/**
* \fn void ajouterPomme(t_tabChar tPlateau)
* \brief Procédure qui dessine et place les pommes
* \param tPlateau : plateau où marquer les coordonnées des pommes
*
* Procédure qui dessine un pavé en fonction de son élément le plus en haut 
* à gauche
*/
void ajouterPomme(t_tabChar tPlateau){
	bool occupee=true;
	int alea1, alea2;
	while (occupee==true){
		alea1=-1;
		alea2=-2;
		while ((alea1<LIM1) || (alea1>LIM2X-(TAILLE_PAVE))){
        		alea1=rand() % (LIM2X+1); //résultat entre 0 et LIM2X
    	}
		while ((alea2<LIM1+2) || (alea2>LIM2Y-(TAILLE_PAVE+2))){
        	alea2=rand() % (LIM2Y+1); //résultat entre 0 et LIM2Y
    	}
		if (tPlateau[alea1][alea2]==VIDE){ //si la place n'est pas occupee
			occupee=false;
			tPlateau[alea1][alea2]=POMME;
			afficher(alea1, alea2, POMME);
		}
	}
}


/**
* \fn int kbhit()
* \brief Fonction qui indique si l'utilisateur a saisi un caractère ou non.
* \return : retourne 1 si un caractère est present et 0 si aucun carctère n'est présent.
*
*/
int kbhit(){
	int unCaractere=0;
	struct termios oldt, newt;
	int ch;
	int oldf;

	// mettre le terminal en mode non bloquant
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
	ch = getchar();

	// restaurer le mode du terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
	if(ch != EOF){
		ungetc(ch, stdin);
		unCaractere=1;
	} 
	return unCaractere;
}

/**
* \fn int kbhit()
* \brief Procédure qui permet de saisir un emplacement où afficher un caractère.
* \param x : paramètre d'entrée qui représente les coordonnées ù il faut se positionner en x.
* \param y : paramètre d'entrée qui représente les coordonnées ù il faut se positionner en y.
*
*/
void gotoXY(int x, int y) { 
    printf("\033[%d;%df", y, x);
}


/**
* \fn void disableEcho()
* \brief Procédure qui permet de ne pas afficher ce qui devrait l'être
*/
void disableEcho() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Desactiver le flag ECHO
    tty.c_lflag &= ~ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}


/**
* \fn void enableEcho()
* \brief Procédure permettant de rétablir l'affichage sur le Terminal
*/
void enableEcho() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Reactiver le flag ECHO
    tty.c_lflag |= ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

