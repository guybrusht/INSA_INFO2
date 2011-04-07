#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* Matrices */


#define TYPE_ELEMENTS_MATRICE double    // permet de changer facilement le type de donnees gerees, ici on gere des tableaux de doubles
#define FORMAT_PRINTF "lf"
/* Proprietes de la matrice */
#define NON_SYMETRIQUE 0
#define SYMETRIQUE 1


/* Structure de la matrice */
typedef struct matrice {
     char nom[255];
     int nb_lignes;
     int nb_colonnes;
     int proprietes;			// NON_SYMETRIQUE, SYMETRIQUE, ...
     void (*remplir)(struct matrice, TYPE_ELEMENTS_MATRICE*);
     void (*afficher)(struct matrice);
     TYPE_ELEMENTS_MATRICE** tableau_2d;
} matrice;





/* Fonctions de gestion de memoire */
matrice* creer_matrice(char*, int, int, int);
TYPE_ELEMENTS_MATRICE** allouer_matrice_pleine(int, int);
TYPE_ELEMENTS_MATRICE** allouer_matrice_symetrique(int);
void detruire_matrice(matrice*);

/* Fonctions d'affichage */
void afficher_matrice(matrice);
void afficher_matrice_pleine(matrice);
void afficher_matrice_symetrique(matrice);

/* Fonctions de remplissage */
void remplir_matrice(matrice, TYPE_ELEMENTS_MATRICE*);
void remplir_matrice_pleine(matrice, TYPE_ELEMENTS_MATRICE*);
void remplir_matrice_symetrique(matrice, TYPE_ELEMENTS_MATRICE*);

/* Fonctions de manipulation de matrices */
matrice* transposerMatrice(matrice* matriceA);

/* Fonctions de calcul */
matrice* produitMatriciel(matrice*, matrice*);
void calculProduit(TYPE_ELEMENTS_MATRICE**, TYPE_ELEMENTS_MATRICE**, TYPE_ELEMENTS_MATRICE**, int, int, int);  // 3e niveau

matrice* decompositionCholesky(matrice*);
int cholesky(TYPE_ELEMENTS_MATRICE**, TYPE_ELEMENTS_MATRICE**, int);  // 3e niveau; vaut 0 si un probleme est survenu, 1 si succes

int decompositionLU(matrice*, matrice*, matrice*);
int decompLU(TYPE_ELEMENTS_MATRICE**, TYPE_ELEMENTS_MATRICE**, TYPE_ELEMENTS_MATRICE**); // 3e niveau