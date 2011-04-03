#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Vecteurs */
typedef struct {
     char nom[15];
     int dimension;
     int* tableau;
} vecteur;

vecteur* creer_vecteur(char*, int);
void remplir_vecteur(vecteur, int*);
void afficher_vecteur(vecteur);
int produit_scalaire(vecteur, vecteur);
void detruire_vecteur(vecteur*);




/* Matrices */


#define TYPE_ELEMENTS_MATRICE int    // permet de changer facilement le type de donnees gerees, ici on gere des tableaux d'entiers
/* Proprietes de la matrice */
#define NON_SYMETRIQUE 0
#define SYMETRIQUE 1


/* Structure de la matrice */
typedef struct matrice {
     char nom[25];
     int nb_lignes;
     int nb_colonnes;
     int proprietes;			// NON_SYMETRIQUE, SYMETRIQUE, ...
     void (*remplir)(struct matrice, TYPE_ELEMENTS_MATRICE*);
     void (*afficher)(struct matrice);
     TYPE_ELEMENTS_MATRICE** tableau_2d;
} matrice;





/* Prototypes */
matrice* creer_matrice(char*, int, int, int);
TYPE_ELEMENTS_MATRICE** allouer_matrice_pleine(int, int);
TYPE_ELEMENTS_MATRICE** allouer_matrice_symetrique(int);
void afficher_matrice(matrice);
void afficher_matrice_pleine(matrice);
void afficher_matrice_symetrique(matrice);
void remplir_matrice_pleine(matrice, int*);
void detruire_matrice(matrice*);

matrice* produit_matriciel(matrice*, matrice*);