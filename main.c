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
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*colonnes);
     remplir_matrice(*A, valeurs);
     afficher_matrice(*A);
     
     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     matrice *B=creer_matrice("B",lignes,colonnes,NON_SYMETRIQUE);
     valeurs=recupererNValeurs(lignes*colonnes);
     remplir_matrice(*B, valeurs);
     afficher_matrice(*B);
     
     afficher_matrice(*produitMatriciel(A,B));
     detruire_matrice(A);
     detruire_matrice(B);
     */
     
     
     
     
     
     
     
     /* Programme test matrices sym */
     /*
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs du triangle inf: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes,SYMETRIQUE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*(lignes+1)/2);
     remplir_matrice(*A, valeurs);
     afficher_matrice(*A);
     
     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs du triangle inf: ");
     matrice *B=creer_matrice("B",lignes,colonnes,SYMETRIQUE);
     valeurs=recupererNValeurs(lignes*(lignes+1)/2);
     remplir_matrice(*B, valeurs);
     afficher_matrice(*B);
     
//     afficher_matrice(*produitMatriciel(A,B));
     detruire_matrice(A);
     detruire_matrice(B);
     */
     
     
     
     
     
     
     
     
     /* Programme test Cholesky */
     
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes,SYMETRIQUE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*(lignes+1)/2);
     remplir_matrice(*A, valeurs);
     afficher_matrice(*A);
     
     matrice *B=decompositionCholesky(A);
     if(B==NULL)
          printf("La matrice que vous essayez de decomposer n'est pas symetrique ou pas definie positive.\n");
     else
     {
          afficher_matrice(*B);
          detruire_matrice(B);
     }
               
     detruire_matrice(A);

     
     
     
}


