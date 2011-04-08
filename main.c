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
     */
     
     
     
     
     /* Programme principal */
     
     
     int is_A_symetrique, n;

     /* Choix de la methode et parametrage du systeme */
     printf("\n *******************************************************\n");    
     printf(" *                                                     *\n");      
     printf(" *           Resolution de A x = B                     *\n");    
     printf(" *                                                     *\n");      
     printf(" *******************************************************\n");    
     printf(" *                                                     *\n");      
     printf(" *   Precisez si A est :                               *\n"); 
     printf(" *                                                     *\n");
     printf(" *   0 => non symetrique (resolution par LU+Gauss)     *\n");
     printf(" *   1 => symetrique (resolution par Cholesky+Gauss)   *\n");
     printf(" *                                                     *\n");    
     printf(" *******************************************************\n\n");                  
                 

     printf(" *   Choix : ");
     scanf("%d",&is_A_symetrique);
     if(is_A_symetrique!=0 && is_A_symetrique!=1)
     {
          printf(" *   Choix invalide.\n");
          return 0;
     } 
     
     printf(" *   Nombre d'equations :\n *   N = ");
     scanf("%d",&n);  
     
  
     
     /* Remplissage et affichage de A */
     TYPE_ELEMENTS_MATRICE* valeurs;
     printf("\n *   Donner les valeurs de A: \n");
     
     matrice *A=creer_matrice("A",n,n, is_A_symetrique, INVERSIBLE, POSITIVE);
     if(is_A_symetrique==0)
     {
          printf(" *   /!\\ Attention: il faut rentrer les valeurs ligne par ligne, donc toute la premiere puis toute la 2e, etc\n");
          valeurs=recupererNValeurs(n*n);
     }
     else
     {
          printf(" *   /!\\ Attention: seules les valeurs du triangle inferieur sont a entrer,\n *   c'est-a-dire A[0][0], A[1][0], A[1][1], A[2][0], ...\n");
          valeurs=recupererNValeurs(n*(n+1)/2);
     }
     remplir_matrice(*A, valeurs);
     free(valeurs);
     afficher_matrice(*A);
     if(determinantMatrice(A)==0)
     {
          A->inversible=NON_INVERSIBLE;
          printf(" *   /!\\ ATTENTION: LA MATRICE N'EST PAS INVERSIBLE, VOUS ALLEZ DROIT DANS LE MUR!!\n");
     }
     
     
     /* Remplissage et affichage de B */
     printf(" *   Donner les valeurs pour le vecteur B: \n");     
     matrice *B=creer_matrice("B",n,1,NON_SYMETRIQUE, INVERSIBLE, NON_POSITIVE);
     valeurs=recupererNValeurs(n*1);
     remplir_matrice(*B, valeurs);
     free(valeurs);
     afficher_matrice(*B);
     
     
     /* Resolution du systeme */
     matrice *X;
     if(solve(A,B,&X)==1)
     {
          /* Produit y=Ax */
          printf("\n\n\n\n\n *   Passage a la phase de verification.\n");
          printf(" *   Calcul du produit y=Ax");
          matrice *P=produitMatriciel(A,X);
          afficher_matrice(*P);
          
          /* Liberation des allocations */          
          detruire_matrice(P);
          detruire_matrice(X);
     }
     

     /* Liberation des allocations */
     detruire_matrice(B);
     detruire_matrice(A);

}


