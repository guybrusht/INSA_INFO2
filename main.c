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
     
     matrice *A=creer_matrice("A",lignes,colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*colonnes);
     remplir_matrice(*A, valeurs);
     afficher_matrice(*A);
     
     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     matrice *B=creer_matrice("B",lignes,colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
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
     
     matrice *A=creer_matrice("A",lignes,colonnes, SYMETRIQUE, INVERSIBLE, POSITIVE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*(lignes+1)/2);
     remplir_matrice(*A, valeurs);
     afficher_matrice(*A);
     
     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs du triangle inf: ");
     matrice *B=creer_matrice("B",lignes,colonnes, SYMETRIQUE, INVERSIBLE, POSITIVE);
     valeurs=recupererNValeurs(lignes*(lignes+1)/2);
     remplir_matrice(*B, valeurs);
     afficher_matrice(*B);
     
//     afficher_matrice(*produitMatriciel(A,B));
     detruire_matrice(A);
     detruire_matrice(B);
     */
     
     
     
     
     
     
     
     
     /* Programme test Cholesky */
     /*
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes, SYMETRIQUE, INVERSIBLE, POSITIVE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*(lignes+1)/2);
     remplir_matrice(*A, valeurs);
     free(valeurs);
     afficher_matrice(*A);
     
     matrice *B=decompositionCholesky(A);
     if(B==NULL)
          printf("La matrice que vous essayez de decomposer n'est pas symetrique ou pas definie positive.\n");
     else
     {
          afficher_matrice(*B);
          matrice *BT=transposerMatrice(B);

          afficher_matrice(*BT);
          matrice *P=produitMatriciel(B,BT);
          afficher_matrice(*P);
          detruire_matrice(B);
          detruire_matrice(BT);
          detruire_matrice(P);
     }
     

               
     detruire_matrice(A);
     */
     
     
     
     
     
     
     
     /* Programme test LU */
     /*
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*colonnes);
     remplir_matrice(*A, valeurs);
     free(valeurs);
     afficher_matrice(*A);
     
     matrice *A_L, *A_U;
     if(decompositionLU(A,&A_L,&A_U)==0) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
          
     else
     {
          afficher_matrice(*A_L);
          afficher_matrice(*A_U);
          
          matrice *P=produitMatriciel(A_L,A_U);
          afficher_matrice(*P);
          detruire_matrice(A_L);
          detruire_matrice(A_U);
          detruire_matrice(P);
     }
     
               
     detruire_matrice(A);
     */
     
     
     /* Programme test Gauss */
     
     int lignes, colonnes;

     
     printf("Nombre de lignes: ");
     scanf("%d",&lignes);
     printf("Nombre de colonnes: ");
     scanf("%d",&colonnes);     
     
     printf("Donner les valeurs: ");
     
     matrice *A=creer_matrice("A",lignes,colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
     TYPE_ELEMENTS_MATRICE* valeurs=recupererNValeurs(lignes*colonnes);
     remplir_matrice(*A, valeurs);
     free(valeurs);
     afficher_matrice(*A);
     
     printf("Donner les valeurs pour vecteur B: ");
     
     matrice *B=creer_matrice("B",lignes,1,NON_SYMETRIQUE, INVERSIBLE, NON_POSITIVE);
     valeurs=recupererNValeurs(lignes*1);
     remplir_matrice(*B, valeurs);
     free(valeurs);
     afficher_matrice(*B);
     
     
     matrice *X=resolutionGauss(A, B);
     if(X==NULL) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
          
     else
     {
          afficher_matrice(*X);
          
          matrice *P=produitMatriciel(A,X);
          afficher_matrice(*P);
          detruire_matrice(X);
          detruire_matrice(P);
     }
          
     detruire_matrice(A);
     
     
}


