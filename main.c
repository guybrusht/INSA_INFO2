#include "head.h"

int main()
{
     /*
     int i=0;
     int tableau_test[3]={45,89,12};
     
     vecteur *A=creer_vecteur("A",3);
     vecteur *B=creer_vecteur("B",3);
     
     
     for(i=0;i<3;i++)
     {
          A->tableau[i]=3;
          B->tableau[i]=2;
     }
     
     remplir_vecteur(*A, tableau_test);
     
     printf("Vecteur A:\n");
     afficher_vecteur(*A);
     printf("\n");     

     printf("Vecteur B:\n");
     afficher_vecteur(*B);
     printf("\n");
     
     printf("Le produit A.B vaut %d.\n",produit_scalaire(*A,*B));

     detruire_vecteur(A);
     detruire_vecteur(B);
     
     */
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
     
     
     
}


