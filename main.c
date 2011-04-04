#include "head.h"

int main()
{
     
     
     
     /* Programme test matrices pleines */
     /*
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes,NON_SYMETRIQUE);
     int* valeurs=recuperer_n_entiers(lignes*colonnes);
     remplir_matrice_pleine(*A, valeurs);
     afficher_matrice(*A);
     
     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     matrice *B=creer_matrice("B",lignes,colonnes,NON_SYMETRIQUE);
     valeurs=recuperer_n_entiers(lignes*colonnes);
     remplir_matrice_pleine(*B, valeurs);
     afficher_matrice(*B);
     
     afficher_matrice(*produit_matriciel(A,B));
     detruire_matrice(A);
     detruire_matrice(B);
     */
     
     /* Programme test matrices sym */
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs du triangle inf: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes,SYMETRIQUE);
     int* valeurs=recuperer_n_entiers(lignes*(lignes+1)/2);
     remplir_matrice(*A, valeurs);
     afficher_matrice(*A);
     
     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs du triangle inf: ");
     matrice *B=creer_matrice("B",lignes,colonnes,SYMETRIQUE);
     valeurs=recuperer_n_entiers(lignes*(lignes+1)/2);
     remplir_matrice(*B, valeurs);
     afficher_matrice(*B);
     
//     afficher_matrice(*produit_matriciel(A,B));
     detruire_matrice(A);
     detruire_matrice(B);
}


