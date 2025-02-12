#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>


// taille du serpent
#define TAILLE 10
// dimensions du plateau
#define LARGEUR_PLATEAU 80	
#define HAUTEUR_PLATEAU 40

// position initiale de la tête du serpent
/*Serpent 1*/
#define X_INITIAL1 40
#define Y_INITIAL1 13
/*Serpent 2*/
#define X_INITIAL2 40
#define Y_INITIAL2 27
// nombre de pommes à manger pour gagner
#define NB_POMMES 10
// temporisation entre deux déplacements du serpent (en microsecondes)
#define ATTENTE 200000
// caractères pour représenter le serpent
#define CORPS 'X'
#define TETESERP1 '1'
#define TETESERP2 '2'
// touches de direction ou d'arrêt du jeu
#define HAUT 'z'
#define BAS 's'
#define GAUCHE 'q'
#define DROITE 'd'
#define STOP 'a'
//direction initiale des 2 serpents
#define DIRECTION_INITIALE1 DROITE
#define DIRECTION_INITIALE2 GAUCHE
// caractères pour les éléments du plateau
#define BORDURE '#'
#define VIDE ' '
#define POMME '6'
#define PORTAIL '/'
#define PORTAIL_VISUEL VIDE
#define NB_PORTAILS 4
#define NB_PAVES 6
#define TAIlLE_PAVES 5
#define PAVES '#'

// définition d'un type pour le plateau : tPlateau
// Attention, pour que les indices du tableau 2D (qui commencent à 0) coincident
// avec les coordonées à l'écran (qui commencent à 1), on ajoute 1 aux dimensions
// et on neutralise la ligne 0 et la colonne 0 du tableau 2D (elles ne sont jamais
// utilisées)
typedef char tPlateau[LARGEUR_PLATEAU+1][HAUTEUR_PLATEAU+1];

typedef int lesPommes[NB_POMMES+1];

typedef int lesPortails[NB_PORTAILS+1];

//variables globales
lesPommes pommesX = {40, 75, 78, 2, 9, 78, 74, 2, 72, 5};
lesPommes pommesY = {20, 38, 2, 2, 5, 38, 32, 38, 32, 2};

int lesPavesX[NB_PAVES] = { 4, 73, 4, 73, 38, 38};
int lesPavesY[NB_PAVES] = { 4, 4, 33, 33, 14, 22};

lesPortails portailsX = {1, LARGEUR_PLATEAU, (LARGEUR_PLATEAU+1)/2, (LARGEUR_PLATEAU+1)/2}; //gauche, droite, haut, bas
lesPortails portailsY = {(HAUTEUR_PLATEAU+1)/2, (HAUTEUR_PLATEAU+1)/2, 1, HAUTEUR_PLATEAU};


void initPlateau(tPlateau plateau);
void dessinerPlateau(tPlateau plateau);
void dessinerPaves(tPlateau Plateau);
void ajouterPomme(tPlateau plateau, int numPomme);
void afficher(int, int, char);
void effacer(int x, int y);
void dessinerSerpent(int lesX[], int lesY[], char tete);
void progresser1(int lesX[], int lesY[], char direction, tPlateau plateau, bool * collision, bool * pomme, bool * traverse_portail, int lesXautre[], int lesYautre[], int *mouvement);
void progresser2(int lesX[], int lesY[], char direction, tPlateau plateau, bool * collision, bool * pomme, bool * traverse_portail, int lesXautre[], int lesYautre[], int *mouvement);
char direction1(bool *collision, int destination[], char direction, int lesX[], int lesY[], tPlateau lePlateau, int *nbPommes, int *nbPommesMangees, bool *pommeMangee, int *mouvement, int lesXautre[], int lesYautre[]);
char direction2(bool *collision, int destination[], char direction, int lesX[], int lesY[], tPlateau lePlateau, int *nbPommes, int *nbPommesMangees, bool *pommeMangee, int *mouvement, int lesXautre[], int lesYautre[]);
bool testBlocage(char direction, int lesXt, int lesYt, tPlateau plateau);
void gotoxy(int x, int y);
int kbhit();
void disable_echo();
void enable_echo();


int main(){
	

	// le plateau de jeu
	tPlateau lePlateau;

	
	bool collision=false;
	bool pommeMangee=false;
    

	// compteur de pommes mangées
	int nbPommes = 0;
	int nbPommesMangees1 = 0;
	int nbPommesMangees2 = 0;
	int mouvement1=0;
	int mouvement2=0;

	int destination1[2];

	destination1[0]=pommesX[nbPommes];
	destination1[1]=pommesY[nbPommes];

	int destination2[2];

	destination2[0]=pommesX[nbPommes];
	destination2[1]=pommesY[nbPommes];

    int lesX1[TAILLE];
    int lesY1[TAILLE];
    int lesX2[TAILLE];
    int lesY2[TAILLE];
    //direction courante du serpent (HAUT, BAS, GAUCHE ou DROITE)
    char dirCour1;
    char dirCour2;
   
	// initialisation de la position du serpent : positionnement de la
	// tête en (X_INITIAL, Y_INITIAL), puis des anneaux à sa gauche
	for(int i=0 ; i<TAILLE ; i++){
		lesX1[i] = X_INITIAL1-i;
		lesY1[i] = Y_INITIAL1;
	}

    for(int i=0 ; i<TAILLE ; i++){
		lesX2[i] = X_INITIAL2+i;
		lesY2[i] = Y_INITIAL2;
	}

	// mise en place du plateau
	initPlateau(lePlateau);
	system("clear");
	dessinerPlateau(lePlateau);
	dessinerPaves(lePlateau);

	// mise en plus des serpents
	dessinerSerpent(lesX1, lesY1, TETESERP1);
	dessinerSerpent(lesX2, lesY2, TETESERP2);

	//srand(time(NULL));
	ajouterPomme(lePlateau, 0);

	// initialisation : le serpent se dirige vers la DROITE
	dirCour1 = DIRECTION_INITIALE1;
	disable_echo();

    dirCour2 = DIRECTION_INITIALE2;
	disable_echo();

	// représente la touche frappée par l'utilisateur : touche d'arrêt
	char touche;

	// boucle de jeu. Arret si touche STOP, si collision avec une bordure ou
	// si toutes les pommes sont mangées	
	do {
		/* ------------------------- MAIN ------------------------- */

		dirCour1=direction1(&collision, destination1, dirCour1, lesX1, lesY1, lePlateau, &nbPommes, &nbPommesMangees1, &pommeMangee, &mouvement1, lesX2, lesY2);
		dirCour2=direction2(&collision, destination2, dirCour2, lesX2, lesY2, lePlateau, &nbPommes, &nbPommesMangees2, &pommeMangee, &mouvement2, lesX1, lesY1);
		// touche=STOP;
		if (nbPommes != NB_POMMES){
			if (!collision){
				usleep(ATTENTE);
				if (kbhit()==1){
					touche = getchar();
				}
			}
		}
	} while (touche != STOP && !collision && (nbPommes != NB_POMMES));
	if (nbPommes == NB_POMMES){
	
	}
    enable_echo();
	// gotoxy(1, HAUTEUR_PLATEAU+1);
	

	// system("clear");
	
	printf("Serpent1 : %d déplacements et %d pommes mangées\n", mouvement1, nbPommesMangees1);
	printf("Serpent2 : %d déplacements et %d pommes mangées\n", mouvement2, nbPommesMangees2);
	return EXIT_SUCCESS;
}


/************************************************/
/*		FONCTIONS ET PROCEDURES DU JEU 			*/
/************************************************/
void initPlateau(tPlateau plateau){
	// initialisation du plateau avec des espaces
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		for (int j=1 ; j<=HAUTEUR_PLATEAU ; j++){
			plateau[i][j] = VIDE;
		}
	}
	// Mise en place la bordure autour du plateau
	// première ligne
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		plateau[i][1] = BORDURE;
	}
	// lignes intermédiaires
	for (int j=1 ; j<=HAUTEUR_PLATEAU ; j++){
			plateau[1][j] = BORDURE;
			plateau[LARGEUR_PLATEAU][j] = BORDURE;
		}
	// dernière ligne
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		plateau[i][HAUTEUR_PLATEAU] = BORDURE;
	}
	for (int i=0; i<NB_PORTAILS; i++){
		plateau[portailsX[i]][portailsY[i]] = PORTAIL;
	}
}

void dessinerPlateau(tPlateau plateau){
	// affiche eà l'écran le contenu du tableau 2D représentant le plateau
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		for (int j=1 ; j<=HAUTEUR_PLATEAU ; j++){
			afficher(i, j, plateau[i][j]);
		}
	}
    for (int i=0; i<NB_PORTAILS; i++){
		afficher(portailsX[i], portailsY[i], PORTAIL_VISUEL);
	}

}

void dessinerPaves(tPlateau Plateau){
	int x, y;
	for(int i = 0; i < NB_PAVES; i++){
		x = lesPavesX[i];
		y = lesPavesY[i];
		for(int ligne = 0; ligne < TAIlLE_PAVES; ligne ++){
			for(int colonne = 0; colonne < TAIlLE_PAVES; colonne++){
				Plateau[x][y] = PAVES;
				afficher(x, y, PAVES);
				x = x + 1;
			}
			y = y + 1;
			x = lesPavesX[i];
		}
	}
}

void ajouterPomme(tPlateau plateau, int numPomme){
	// génère aléatoirement la position d'une pomme,
	// vérifie que ça correspond à une case vide
	// du plateau puis l'ajoute au plateau et l'affiche

	plateau[pommesX[numPomme]][pommesY[numPomme]]=POMME;
	afficher(pommesX[numPomme], pommesY[numPomme], POMME);
}

void afficher(int x, int y, char car){
	gotoxy(x, y);
	printf("%c", car);
	gotoxy(1,1);
}

void effacer(int x, int y){
	gotoxy(x, y);
	printf(" ");
	gotoxy(1,1);
}

void dessinerSerpent(int lesX[], int lesY[], char tete){
	// affiche les anneaux puis la tête
	for(int i=1 ; i<TAILLE ; i++){
		afficher(lesX[i], lesY[i], CORPS);
	}
	afficher(lesX[0], lesY[0],tete);
}

bool testBlocage(char direction, int lesXt, int lesYt, tPlateau plateau){
	bool blocage=false;
	int nbDirectionBloquee=0;
	//simulation de l'avancement prévu du serpent
	if (direction==DROITE){
		lesXt++;
	}
	else if (direction==GAUCHE){
		lesXt--;
	}
	else if (direction==HAUT){
		lesYt--;
	}
	else{
		lesYt++;
	}
	/* Mise en place de tests pour connaître le nombre de direction bloquées autour du serpent */
	if (lesXt>LARGEUR_PLATEAU){
		nbDirectionBloquee++;
	}
	if (lesXt< 1){
		nbDirectionBloquee++;
	}
	if (lesYt<1){
		nbDirectionBloquee++;
	}
	if (lesYt>HAUTEUR_PLATEAU){
		nbDirectionBloquee++;
	}
	/* si le serpent ne va pas à gauche alors il peut aller à droite */
	if (direction!=GAUCHE && lesXt<LARGEUR_PLATEAU && (plateau[lesXt+1][lesYt]==BORDURE || plateau[lesXt+1][lesYt]==PAVES || plateau[lesXt+1][lesYt]==CORPS)){
		nbDirectionBloquee++;
	}
	/* si le serpent ne va pas à droite alors il peut aller à gauche */
	if (direction!=DROITE && lesXt>1 && (plateau[lesXt-1][lesYt]==BORDURE || plateau[lesXt-1][lesYt]==PAVES || plateau[lesXt-1][lesYt]==CORPS)){
		nbDirectionBloquee++;
	}
	/* si le serpent ne va pas en haut alors il peut aller en bas */
	if (direction!=HAUT && lesYt<HAUTEUR_PLATEAU && (plateau[lesXt][lesYt+1]==BORDURE || plateau[lesXt][lesYt+1]==PAVES || plateau[lesXt][lesYt+1]==CORPS)){
		nbDirectionBloquee++;
	}
	/* si le serpent ne va pas en bas alors il peut aller en haut */
	if (direction!=BAS && lesYt>1 && (plateau[lesXt][lesYt-1]==BORDURE || plateau[lesXt][lesYt-1]==PAVES || plateau[lesXt][lesYt-1]==CORPS)){
		nbDirectionBloquee++;
	}
	/*Étant donné que le serpent ne peux pas retourner en arrière, s'il a 3 issues bloquées ou plus alors il faut changer de direction.*/
	if (nbDirectionBloquee>2){
		blocage=true;
	}
	return blocage;
}


void calculDestination(int *nbPommes, int lesX[], int lesY[], int destination[]){
	lesPortails diffValPortailsX;
	lesPortails diffValPortailsY;
	lesPortails diffVal;
	int absDiffPlusCourt;

	destination[0]=pommesX[*nbPommes];
	destination[1]=pommesY[*nbPommes];
	diffVal[0]=lesX[0]-pommesX[*nbPommes];
	diffVal[1]=lesY[0]-pommesY[*nbPommes];

	//if (abs(lesX[0]-portailsX[0])<)
	diffValPortailsX[0]=abs(lesX[0]-portailsX[0])+abs(portailsX[1]-pommesX[*nbPommes])+1; //gauche
	diffValPortailsY[0]=abs(lesY[0]-portailsY[0])+abs(portailsY[1]-pommesY[*nbPommes])+1;

	diffValPortailsX[1]=abs(lesX[0]-portailsX[1])+abs(portailsX[0]-pommesX[*nbPommes])+1; //droite
	diffValPortailsY[1]=abs(lesY[0]-portailsY[1])+abs(portailsY[0]-pommesY[*nbPommes])+1;

	diffValPortailsX[2]=abs(lesX[0]-portailsX[2])+abs(portailsX[3]-pommesX[*nbPommes])+1;
	diffValPortailsY[2]=abs(lesY[0]-portailsY[2])+abs(portailsY[3]-pommesY[*nbPommes])+1;

	diffValPortailsX[3]=abs(lesX[0]-portailsX[3])+abs(portailsX[2]-pommesX[*nbPommes])+1;
	diffValPortailsY[3]=abs(lesY[0]-portailsY[3])+abs(portailsY[2]-pommesY[*nbPommes])+1;
	
	absDiffPlusCourt=abs(diffVal[0])+abs(diffVal[1]);
	
	for (int assigne_portails=0; assigne_portails<NB_PORTAILS; assigne_portails++){
		if ((diffValPortailsX[assigne_portails]+diffValPortailsY[assigne_portails]) < absDiffPlusCourt){
			destination[0]=portailsX[assigne_portails];
			destination[1]=portailsY[assigne_portails];
			absDiffPlusCourt=diffValPortailsX[assigne_portails]+diffValPortailsY[assigne_portails];
		}
	}
}

/* ------------------------- Serpent 1 ------------------------- */

void progresser1(int lesX[], int lesY[], char direction, tPlateau plateau, bool * collision, bool * pomme, bool * traverse_portail, int lesXautre[], int lesYautre[], int *mouvement){
	(*mouvement)++;
	// efface le dernier élément avant d'actualiser la position de tous les 
	// éléments du serpent et de le redessiner. Détecte les
	// collisions avec une pomme ou avec une bordure
	effacer(lesX[TAILLE-1], lesY[TAILLE-1]);

	for(int i=TAILLE-1 ; i>0 ; i--){
		lesX[i] = lesX[i-1];
		lesY[i] = lesY[i-1];
	}
	//faire progresser la tete dans la nouvelle direction
	switch(direction){
		case HAUT : 
			lesY[0] = lesY[0] - 1;
			break;
		case BAS:
			lesY[0] = lesY[0] + 1;
			break;
		case DROITE:
			lesX[0] = lesX[0] + 1;
			break;
		case GAUCHE:
			lesX[0] = lesX[0] - 1;
			break;
	}
	*pomme = false;
	// détection d'une "collision" avec une pomme
	if (plateau[lesX[0]][lesY[0]] == POMME){
		*pomme = true;
		// la pomme disparait du plateau
		plateau[lesX[0]][lesY[0]] = VIDE;
	}
	// détection d'une collision avec la bordure ou un pavé
	else if (plateau[lesX[0]][lesY[0]] == BORDURE || plateau[lesX[0]][lesY[0]] == PAVES || plateau[lesX[0]][lesY[0]] == CORPS){
		*collision = true;
	}

	//détection d'une collision avec le corps du serpent
	for (int indice = 1; indice < TAILLE - 1; indice++){
        if(lesX[0] == lesX[indice] && lesY[0] == lesY[indice]){
            *collision = true;
        }
		//détection d'une collision avec le corps de l'autre serpent
		else if(lesX[0] == lesXautre[indice] && lesY[0] == lesYautre[indice]){
            *collision = true;
        }
	}
	/* teleportation du serpent avec les portails */
	if (plateau[lesX[0]][lesY[0]] == PORTAIL){
		if (lesX[0]>= LARGEUR_PLATEAU){
			lesX[0]=1;
		}
		else if (lesX[0]<= 1){
			lesX[0]=LARGEUR_PLATEAU;
		}
		else if (lesY[0]>= HAUTEUR_PLATEAU){
			lesY[0]=1;
		}
		else if (lesY[0]<= 1){
			lesY[0]= HAUTEUR_PLATEAU;
		}
		*traverse_portail = true;
	}
   	dessinerSerpent(lesX, lesY, TETESERP1);
}


char direction1(bool *collision, int destination[], char direction, int lesX[], int lesY[], tPlateau lePlateau, int *nbPommes, int *nbPommesMangees, bool *pommeMangee, int *mouvement, int lesXautre[], int lesYautre[]){
	bool gagne = false;
	bool traverse_portail=false;
	bool intervertirX=false;
	int lesXt=lesX[0], lesYt=lesY[0];
	int parcourirTab;
	
	/* mise en place des serpents dans le plateau pour détecter les collisions possibles entre eux */
	for (parcourirTab=0; parcourirTab<TAILLE; parcourirTab++){
		if (lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]==VIDE){
			lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]=CORPS;
		}
		if (lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]==VIDE){
			lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]=CORPS;
		}
	}

	//direction de secours pour éviter au serpent de faire volte-face
	char sauveX;
	char sauveY;

	//difference entre les coordonnées du serpent et celles d'une pomme
	lesPortails diffVal;
	if (*pommeMangee){
		//si l'autre serpent a mangé une pomme alors il faut
		//refaire les calculs servant à déterminer la direction du serpent
		calculDestination(nbPommes, lesX, lesY, destination);
	}

	*pommeMangee = false;
	/* calcule la différence en X et Y du serpent avec le X et le Y de la destination */
	diffVal[0]=lesX[0]-destination[0];
    diffVal[1]=lesY[0]-destination[1];

    //calcule la direction en X et en Y qui rapproche le serpent de sa destination
    if ((lesX[0] < destination[0]) && (direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE && lePlateau[lesX[0]+1][lesY[0]] != PAVES && lePlateau[lesX[0]+1][lesY[0]] != CORPS)){
        sauveX=DROITE;
    }
    else if ((lesX[0] > destination[0]) && (direction!=DROITE) && (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS)){
        sauveX=GAUCHE;
    }
    //si les conditions pour un déplacement optimisé ne sont pas remplies alors on abandonne l'optimisation
    //au profit du respect des règles
    else if ((direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE && lePlateau[lesX[0]+1][lesY[0]] != PAVES && lePlateau[lesX[0]+1][lesY[0]] != CORPS)){
        sauveX=DROITE;
    }
    else if (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS){
        sauveX=GAUCHE;
    }
    else{
        intervertirX=true; //intervertit sauveX et sauveY
        //sauveX mène à une collision, il faut donc que sauveX prenne la futur valeur de sauveY.
    }		
	
    if ((lesY[0] > destination[1]) && (direction!=BAS) && (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS)){
        sauveY=HAUT;
    }
    else if ((lesY[0] < destination[1]) && (direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
        sauveY=BAS;
    }
    //si les conditions pour un déplacement optimisé ne sont pas remplies alors on abandonne l'optimisation
    //au profit du respect des règles
    else if ((direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
        sauveY=BAS;
    }
    else if (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS){
        sauveY=HAUT;
    }
    else{
        sauveY=sauveX;
        direction=sauveX;
		//sauveY mène à une collision, il faut donc que sauveY prenne la futur valeur de sauveX.
    }
    
    if (intervertirX==true){
        sauveX=sauveY;
        intervertirX=false;
    }
    

    //si les valeurs absolus des différences de position entre le serpent et une destination en X sont plus petite qu'en Y alors
    if (abs(diffVal[0]) < abs(diffVal[1])){	
        if ((lesY[0]<destination[1]) && (direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
            direction=BAS;
        }
        else if ((lesY[0]>destination[1]) && (direction!=BAS) && (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS)){
            direction=HAUT;
        }
        else{
            direction=sauveX;
        }
    }
	//si les valeurs absolus des différences de position entre le serpent et une destination en X sont plus grande qu'en Y alors
    else if (abs(diffVal[0]) > abs(diffVal[1])){
        if ((lesX[0]<destination[0]) && (direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE) && (lePlateau[lesX[0]+1][lesY[0]] != PAVES && (lePlateau[lesX[0]+1][lesY[0]] != CORPS))){
            direction=DROITE;
		}
        else if ((lesX[0]>destination[0]) && (direction!=DROITE) && (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS)){
            direction=GAUCHE;
		}
        else{
            direction=sauveY;
		}
    }
	// Si les valeurs absolus sont égales entre elles alors on les oublie


	else if (lesX[0]!=destination[0]){
		if ((lesX[0]<destination[0]) && (direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE) && (lePlateau[lesX[0]+1][lesY[0]] != PAVES && (lePlateau[lesX[0]+1][lesY[0]] != CORPS))){
            direction=DROITE;
			}
        else if ((lesX[0]>destination[0]) && (direction!=DROITE) && (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS)){
            direction=GAUCHE;
			}
        else{//lesX[0]==destination[0]
            direction=sauveY;
		}
	}
	else{//lesY[0]!=destination[1]
		if ((lesY[0]<destination[1]) && (direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
            direction=BAS;
        }
        else if ((lesY[0]>destination[1]) && (direction!=BAS) && (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS)){
            direction=HAUT;
        }

        else{//lesY[0]==destination[1]
            direction=sauveX;
        }
	}

	/* Quand la tête du serpent prend un portail on lui force la première direction pour pas qu'il se prenne le mur */
    if ((lesX[0]==portailsX[0]) && (lesY[0]==portailsY[0]) && traverse_portail){
        direction=DROITE;
    }
    else if ((lesX[0]==portailsX[1]) && (lesY[0]==portailsY[1])&& traverse_portail){
        direction=GAUCHE;
    }
    else if ((lesX[0]==portailsX[2]) && (lesY[0]==portailsY[2])&& traverse_portail){
        direction=BAS;
		
    }
    else if ((lesX[0]==portailsX[3]) && (lesY[0]==portailsY[3])&& traverse_portail){
        direction=HAUT;
    }
	// on remet la variable à false, la tête du serpent est sortie du portail
    traverse_portail=false;


	/* On vérifie si la direction prise par le serpent  mène à une impasse*/
	if (testBlocage(direction, lesXt, lesYt, lePlateau)){
		//si c'est le cas on change de direction et on reteste jusqu'à
		//ce qu'une direction ne menant pas à une impasse soit prise

		//on préviligie d'abord sauveX et sauveY
		if (false==testBlocage(sauveX, lesXt, lesYt, lePlateau)){
			direction=sauveX;
		}
		else if (false==testBlocage(sauveY, lesXt, lesYt, lePlateau)){
			direction=sauveY;
		}
		//Si sauveX et sauveY mènent à une impasse alors on teste toutes les directions une à une
		else if (false==testBlocage(DROITE, lesXt, lesYt, lePlateau)){
			direction=DROITE;
		}
		else if (false==testBlocage(GAUCHE, lesXt, lesYt, lePlateau)){
			direction=GAUCHE;
		}
		else if (false==testBlocage(BAS, lesXt, lesYt, lePlateau)){
			direction=BAS;
		}
		else if (false==testBlocage(HAUT, lesXt, lesYt, lePlateau)){
			direction=HAUT;
		}
	}

	
	/* nettoyage du plateau pour supprimer les corps des serpents et ne pas le remplir avec des 'X' */
	for (parcourirTab=0; parcourirTab<TAILLE; parcourirTab++){
		if (lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]==CORPS){
			lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]=VIDE;
		}
		if (lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]==CORPS){
			lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]=VIDE;
		}
	}
	
	

	/* on fait avancer le serpent */
    progresser1(lesX, lesY, direction, lePlateau, collision, pommeMangee, &traverse_portail, lesXautre, lesYautre, mouvement);
    if (*pommeMangee){
        (*nbPommes)++;
		(*nbPommesMangees)++;
		
        gagne = ((*nbPommes)==NB_POMMES);
        if (!gagne){
            ajouterPomme(lePlateau, *nbPommes);
			calculDestination(nbPommes, lesX, lesY, destination);
        }
        
    }
	/* Après avoir traversé un portail, la destination revient sur la pomme */
    if (traverse_portail){
        destination[0]=pommesX[*nbPommes];
        destination[1]=pommesY[*nbPommes];
    }
	return direction;
}



/* ------------------------- Serpent 2 ------------------------- */

void progresser2(int lesX[], int lesY[], char direction, tPlateau plateau, bool * collision, bool * pomme, bool * traverse_portail, int lesXautre[], int lesYautre[], int *mouvement){
	(*mouvement)++;
	// efface le dernier élément avant d'actualiser la position de tous les 
	// éléments du serpent et de le redessiner. Détecte les
	// collisions avec une pomme ou avec une bordure
	effacer(lesX[TAILLE-1], lesY[TAILLE-1]);

	for(int i=TAILLE-1 ; i>0 ; i--){
		lesX[i] = lesX[i-1];
		lesY[i] = lesY[i-1];
	}
	//faire progresser la tete dans la nouvelle direction
	switch(direction){
		case HAUT : 
			lesY[0] = lesY[0] - 1;
			break;
		case BAS:
			lesY[0] = lesY[0] + 1;
			break;
		case DROITE:
			lesX[0] = lesX[0] + 1;
			break;
		case GAUCHE:
			lesX[0] = lesX[0] - 1;
			break;
	}
	*pomme = false;
	// détection d'une "collision" avec une pomme
	if (plateau[lesX[0]][lesY[0]] == POMME){
		*pomme = true;
		// la pomme disparait du plateau
		plateau[lesX[0]][lesY[0]] = VIDE;
	}
	// détection d'une collision avec la bordure ou un pavé
	else if (plateau[lesX[0]][lesY[0]] == BORDURE || plateau[lesX[0]][lesY[0]] == PAVES || plateau[lesX[0]][lesY[0]] == CORPS){
		*collision = true;
	}

	//détection d'une collision avec le corps du serpent
	for (int indice = 1; indice < TAILLE - 1; indice++){
        if(lesX[0] == lesX[indice] && lesY[0] == lesY[indice]){
            *collision = true;
        }
		//détection d'une collision avec le corps de l'autre serpent
		else if(lesX[0] == lesXautre[indice] && lesY[0] == lesYautre[indice]){
            *collision = true;
        }
	}
	/* teleportation du serpent avec les portails */
	if (plateau[lesX[0]][lesY[0]] == PORTAIL){
		if (lesX[0]>= LARGEUR_PLATEAU){
			lesX[0]=1;
		}
		else if (lesX[0]<= 1){
			lesX[0]=LARGEUR_PLATEAU;
		}
		else if (lesY[0]>= HAUTEUR_PLATEAU){
			lesY[0]=1;
		}
		else if (lesY[0]<= 1){
			lesY[0]= HAUTEUR_PLATEAU;
		}
		*traverse_portail = true;
	}
   	dessinerSerpent(lesX, lesY, TETESERP2);
}

char direction2(bool *collision, int destination[], char direction, int lesX[], int lesY[], tPlateau lePlateau, int *nbPommes, int *nbPommesMangees, bool *pommeMangee, int *mouvement, int lesXautre[], int lesYautre[]){
	bool gagne = false;
	bool traverse_portail=false;
	bool intervertirX=false;
	int lesXt=lesX[0], lesYt=lesY[0];
	int parcourirTab;
	
	/* mise en place des serpents dans le plateau pour détecter les collisions possibles entre eux */
	for (parcourirTab=0; parcourirTab<TAILLE; parcourirTab++){
		if (lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]==VIDE){
			lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]=CORPS;
		}
		if (lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]==VIDE){
			lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]=CORPS;
		}
	}

	//direction de secours pour éviter au serpent de faire volte-face
	char sauveX;
	char sauveY;

	//difference entre les coordonnées du serpent et celles d'une pomme
	lesPortails diffVal;
	if (*pommeMangee){
		//si l'autre serpent a mangé une pomme alors il faut
		//refaire les calculs servant à déterminer la direction du serpent
		calculDestination(nbPommes, lesX, lesY, destination);
	}

	*pommeMangee = false;
	/* calcule la différence en X et Y du serpent avec le X et le Y de la destination */
	diffVal[0]=lesX[0]-destination[0];
    diffVal[1]=lesY[0]-destination[1];

    //calcule la direction en X et en Y qui rapproche le serpent de sa destination
    if ((lesX[0] < destination[0]) && (direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE && lePlateau[lesX[0]+1][lesY[0]] != PAVES && lePlateau[lesX[0]+1][lesY[0]] != CORPS)){
        sauveX=DROITE;
    }
    else if ((lesX[0] > destination[0]) && (direction!=DROITE) && (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS)){
        sauveX=GAUCHE;
    }
    //si les conditions pour un déplacement optimisé ne sont pas remplies alors on abandonne l'optimisation
    //au profit du respect des règles
    else if ((direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE && lePlateau[lesX[0]+1][lesY[0]] != PAVES && lePlateau[lesX[0]+1][lesY[0]] != CORPS)){
        sauveX=DROITE;
    }
    else if (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS){
        sauveX=GAUCHE;
    }
    else{
        intervertirX=true; //intervertit sauveX et sauveY
        //sauveX mène à une collision, il faut donc que sauveX prenne la futur valeur de sauveY.
    }		
	
    if ((lesY[0] > destination[1]) && (direction!=BAS) && (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS)){
        sauveY=HAUT;
    }
    else if ((lesY[0] < destination[1]) && (direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
        sauveY=BAS;
    }
    //si les conditions pour un déplacement optimisé ne sont pas remplies alors on abandonne l'optimisation
    //au profit du respect des règles
    else if ((direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
        sauveY=BAS;
    }
    else if (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS){
        sauveY=HAUT;
    }
    else{
        sauveY=sauveX;
        direction=sauveX;
		//sauveY mène à une collision, il faut donc que sauveY prenne la futur valeur de sauveX.
    }
    
    if (intervertirX==true){
        sauveX=sauveY;
        intervertirX=false;
    }
    

    //si les valeurs absolus des différences de position entre le serpent et une destination en X sont plus petite qu'en Y alors
    if (abs(diffVal[0]) < abs(diffVal[1])){	
        if ((lesY[0]<destination[1]) && (direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
            direction=BAS;
        }
        else if ((lesY[0]>destination[1]) && (direction!=BAS) && (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS)){
            direction=HAUT;
        }
        else{
            direction=sauveX;
        }
    }
	//si les valeurs absolus des différences de position entre le serpent et une destination en X sont plus grande qu'en Y alors
    else if (abs(diffVal[0]) > abs(diffVal[1])){
        if ((lesX[0]<destination[0]) && (direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE) && (lePlateau[lesX[0]+1][lesY[0]] != PAVES && (lePlateau[lesX[0]+1][lesY[0]] != CORPS))){
            direction=DROITE;
		}
        else if ((lesX[0]>destination[0]) && (direction!=DROITE) && (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS)){
            direction=GAUCHE;
		}
        else{
            direction=sauveY;
		}
    }
	// Si les valeurs absolus sont égales entre elles alors on les oublie


	else if (lesX[0]!=destination[0]){
		if ((lesX[0]<destination[0]) && (direction!=GAUCHE) && (lePlateau[lesX[0]+1][lesY[0]]!=BORDURE) && (lePlateau[lesX[0]+1][lesY[0]] != PAVES && (lePlateau[lesX[0]+1][lesY[0]] != CORPS))){
            direction=DROITE;
			}
        else if ((lesX[0]>destination[0]) && (direction!=DROITE) && (lePlateau[lesX[0]-1][lesY[0]]!=BORDURE && lePlateau[lesX[0]-1][lesY[0]] != PAVES && lePlateau[lesX[0]-1][lesY[0]] != CORPS)){
            direction=GAUCHE;
			}
        else{//lesX[0]==destination[0]
            direction=sauveY;
		}
	}
	else{//lesY[0]!=destination[1]
		if ((lesY[0]<destination[1]) && (direction!=HAUT) && (lePlateau[lesX[0]][lesY[0]+1]!=BORDURE && lePlateau[lesX[0]][lesY[0]+1] != PAVES && lePlateau[lesX[0]][lesY[0]+1] != CORPS)){
            direction=BAS;
        }
        else if ((lesY[0]>destination[1]) && (direction!=BAS) && (lePlateau[lesX[0]][lesY[0]-1]!=BORDURE && lePlateau[lesX[0]][lesY[0]-1] != PAVES && lePlateau[lesX[0]][lesY[0]-1] != CORPS)){
            direction=HAUT;
        }

        else{//lesY[0]==destination[1]
            direction=sauveX;
        }
	}

	/* Quand la tête du serpent prend un portail on lui force la première direction pour pas qu'il se prenne le mur */
    if ((lesX[0]==portailsX[0]) && (lesY[0]==portailsY[0]) && traverse_portail){
        direction=DROITE;
    }
    else if ((lesX[0]==portailsX[1]) && (lesY[0]==portailsY[1])&& traverse_portail){
        direction=GAUCHE;
    }
    else if ((lesX[0]==portailsX[2]) && (lesY[0]==portailsY[2])&& traverse_portail){
        direction=BAS;
		
    }
    else if ((lesX[0]==portailsX[3]) && (lesY[0]==portailsY[3])&& traverse_portail){
        direction=HAUT;
    }
	// on remet la variable à false, la tête du serpent est sortie du portail
    traverse_portail=false;


	/* On vérifie si la direction prise par le serpent  mène à une impasse*/
	if (testBlocage(direction, lesXt, lesYt, lePlateau)){
		//si c'est le cas on change de direction et on reteste jusqu'à
		//ce qu'une direction ne menant pas à une impasse soit prise

		//on préviligie d'abord sauveX et sauveY
		if (false==testBlocage(sauveX, lesXt, lesYt, lePlateau)){
			direction=sauveX;
		}
		else if (false==testBlocage(sauveY, lesXt, lesYt, lePlateau)){
			direction=sauveY;
		}
		//Si sauveX et sauveY mènent à une impasse alors on teste toutes les directions une à une
		else if (false==testBlocage(DROITE, lesXt, lesYt, lePlateau)){
			direction=DROITE;
		}
		else if (false==testBlocage(GAUCHE, lesXt, lesYt, lePlateau)){
			direction=GAUCHE;
		}
		else if (false==testBlocage(BAS, lesXt, lesYt, lePlateau)){
			direction=BAS;
		}
		else if (false==testBlocage(HAUT, lesXt, lesYt, lePlateau)){
			direction=HAUT;
		}
	}

	
	/* nettoyage du plateau pour supprimer les corps des serpents et ne pas le remplir avec des 'X' */
	for (parcourirTab=0; parcourirTab<TAILLE; parcourirTab++){
		if (lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]==CORPS){
			lePlateau[lesX[parcourirTab]][lesY[parcourirTab]]=VIDE;
		}
		if (lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]==CORPS){
			lePlateau[lesXautre[parcourirTab]][lesYautre[parcourirTab]]=VIDE;
		}
	}
	
	

	/* on fait avancer le serpent */
    progresser2(lesX, lesY, direction, lePlateau, collision, pommeMangee, &traverse_portail, lesXautre, lesYautre, mouvement);
    if (*pommeMangee){
        (*nbPommes)++;
		(*nbPommesMangees)++;
		
        gagne = ((*nbPommes)==NB_POMMES);
        if (!gagne){
            ajouterPomme(lePlateau, *nbPommes);
			calculDestination(nbPommes, lesX, lesY, destination);
        }
        
    }
	/* Après avoir traversé un portail, la destination revient sur la pomme */
    if (traverse_portail){
        destination[0]=pommesX[*nbPommes];
        destination[1]=pommesY[*nbPommes];
    }
	return direction;
}

/************************************************/
/*				 FONCTIONS UTILITAIRES 			*/
/************************************************/
void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
}



int kbhit(){
	// la fonction retourne :
	// 1 si un caractere est present
	// 0 si pas de caractere présent
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

// Fonction pour désactiver l'echo
void disable_echo() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Désactiver le flag ECHO
    tty.c_lflag &= ~ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour réactiver l'echo
void enable_echo() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Réactiver le flag ECHO
    tty.c_lflag |= ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}