#include "head.h"

TYPE_ELEMENTS_MATRICE* recuperer_n_entiers(int n)
{
     int i=0;
     TYPE_ELEMENTS_MATRICE *TAB=(TYPE_ELEMENTS_MATRICE*) malloc (n*sizeof(TYPE_ELEMENTS_MATRICE));
     
     for(i=0; i<n; i++)
          scanf("%"FORMAT_PRINTF,&TAB[i]);
         
     return TAB;
}






/* Matrices -------------------------------------------------------*/

matrice* creer_matrice(char *nom_matrice, int nb_lignes_matrice, int nb_colonnes_matrice, int prop_matrice)
{
     int i=0;
     
     matrice *nouvelle_matrice;
     nouvelle_matrice=(matrice*) malloc (sizeof(matrice));
     strcpy(nouvelle_matrice->nom,nom_matrice);                 // methode pour assigner une chaine de caracteres; ne pas oublier d'inclure string.h
     nouvelle_matrice->nb_lignes=nb_lignes_matrice;
     nouvelle_matrice->nb_colonnes=nb_colonnes_matrice;
     nouvelle_matrice->proprietes=prop_matrice;
     
     if(prop_matrice==NON_SYMETRIQUE)
     {
          nouvelle_matrice->remplir=&remplir_matrice_pleine;
          nouvelle_matrice->afficher=&afficher_matrice_pleine;
          nouvelle_matrice->tableau_2d=allouer_matrice_pleine(nb_lignes_matrice, nb_colonnes_matrice);
     }
     
     else if(prop_matrice==SYMETRIQUE)
     {
          nouvelle_matrice->remplir=&remplir_matrice_symetrique;
          nouvelle_matrice->afficher=&afficher_matrice_symetrique;
          nouvelle_matrice->tableau_2d=allouer_matrice_symetrique(nb_lignes_matrice);
     }
     
     return nouvelle_matrice;
}



/* Fonctions d'allocation */
TYPE_ELEMENTS_MATRICE** allouer_matrice_pleine(int nb_lignes_matrice, int nb_colonnes_matrice)
{
     int i=0;
     TYPE_ELEMENTS_MATRICE** matrice_allouee;
     
     matrice_allouee=(TYPE_ELEMENTS_MATRICE**) malloc (nb_lignes_matrice*sizeof(TYPE_ELEMENTS_MATRICE*));
     matrice_allouee[0]=(TYPE_ELEMENTS_MATRICE*) malloc (nb_lignes_matrice*nb_colonnes_matrice*sizeof(TYPE_ELEMENTS_MATRICE));
     for(i=1;i<nb_lignes_matrice;i++)
     {
          matrice_allouee[i]=matrice_allouee[i-1]+nb_colonnes_matrice;
     }
          
     return matrice_allouee;
}

TYPE_ELEMENTS_MATRICE** allouer_matrice_symetrique(int nb_lignes_matrice)
{
     int i=0;
     TYPE_ELEMENTS_MATRICE** matrice_allouee;
     
     matrice_allouee=(TYPE_ELEMENTS_MATRICE**) malloc (nb_lignes_matrice*sizeof(TYPE_ELEMENTS_MATRICE*));
     matrice_allouee[0]=(TYPE_ELEMENTS_MATRICE*) malloc (nb_lignes_matrice*(nb_lignes_matrice+1)/2*sizeof(TYPE_ELEMENTS_MATRICE));  // calcul la somme des n premiers entiers pour trouver le nombre d'elements a stocker dans la matrice symetrique
     for(i=1;i<nb_lignes_matrice;i++)
     {
          matrice_allouee[i]=matrice_allouee[i-1]+i; // le nombre d'elements par ligne est croissant de 1 à n
     }
     
     return matrice_allouee;
}



/* Fonctions d'affichage */
void afficher_matrice(matrice matriceA)
{
     matriceA.afficher(matriceA);
}

void afficher_matrice_pleine(matrice matriceA)             //    /!\ distinguer affichage de matrices pleines et symetriques
{
     int i,j;
     printf("\n############# Matrice %s #############\n",matriceA.nom);

     for (i=0; i<matriceA.nb_lignes; i++)
     {
          printf("[\t");
          for (j=0; j<matriceA.nb_colonnes; j++)
               printf("%+"FORMAT_PRINTF"\t",matriceA.tableau_2d[i][j]);
          
          printf("]\n");
     }
     printf("#############################################\n\n");
}

void afficher_matrice_symetrique(matrice matriceA)             //    /!\ distinguer affichage de matrices pleines et symetriques
{
     int i,j;
     printf("\n############# Matrice %s #############\n",matriceA.nom);

     for (i=0; i<matriceA.nb_lignes; i++)
     {
          printf("[\t");
          for (j=0; j<matriceA.nb_colonnes; j++)
          {
               if(j<=i) printf("%+"FORMAT_PRINTF"\t",matriceA.tableau_2d[i][j]);
               else printf("%+"FORMAT_PRINTF"\t",matriceA.tableau_2d[j][i]);
          }
          printf("]\n");
     }
     printf("#############################################\n\n");
}





/* Fonctions de remplissage */
void remplir_matrice(matrice matriceA, TYPE_ELEMENTS_MATRICE* TAB)
{
     matriceA.remplir(matriceA, TAB);
}

void remplir_matrice_pleine(matrice matriceA, TYPE_ELEMENTS_MATRICE* TAB)		/*   /!\ TAB doit contenir le meme nombre d'elements que matriceA, soit nb_lignes*nb_colonnes */
{
     int i=0,j=0;
     
     for(i=0;i<matriceA.nb_lignes;i++)
          for(j=0;j<matriceA.nb_colonnes;j++)
               matriceA.tableau_2d[i][j]=TAB[j+i*matriceA.nb_colonnes];
}

void remplir_matrice_symetrique(matrice matriceA, TYPE_ELEMENTS_MATRICE* TAB)               /*   /!\ TAB doit contenir le meme nombre d'elements que matriceA, soit nb_lignes*nb_colonnes */
{
     int i=0,j=0;
     
/*
     for(j=0;j<matriceA.nb_colonnes;j++)
          for(i=0;i<matriceA.nb_lignes;i++)
               if(i<=j) matriceA.tableau_2d[i][j]=TAB[j+i*(i+1)/2];
               */

     for(i=0;i<matriceA.nb_lignes*(matriceA.nb_lignes+1)/2;i++)
               matriceA.tableau_2d[0][i]=TAB[i];
}



/* Liberation de la memoire allouee */
void detruire_matrice(matrice* matriceA)   
{
     free(matriceA->tableau_2d[0]);
     free(matriceA->tableau_2d);
     free(matriceA);
}


/* Fonctions de calcul */
matrice* produit_matriciel(matrice* matriceA, matrice* matriceB)
{
     /* Verification compatibilite matrices */
     if(matriceA->nb_colonnes!=matriceB->nb_lignes)
          return 0;
     
     else
     {
          int i,j,k,tmp;
          
          /* Creation matrice bonnes dimensions */
          matrice *produit=creer_matrice(strcat(strcat(matriceA->nom,"*"),matriceB->nom), matriceA->nb_lignes, matriceB->nb_colonnes, NON_SYMETRIQUE);
          
          /* Calcul du produit */
          for(i=0;i<matriceA->nb_lignes;i++)  // ligne de calcul de la premiere matrice
          {
               for(j=0;j<matriceB->nb_colonnes;j++)  // colonne de calcul de la deuxieme matrice
               {
                    tmp=0;
                    for(k=0;k<matriceB->nb_lignes;k++)
                    {
                         tmp+=matriceA->tableau_2d[i][k]*matriceB->tableau_2d[k][j];
                    }
                    produit->tableau_2d[i][j]=tmp;
               }
          }
          return produit;
     }
     
}


matrice* decomposition_cholesky(matrice* matriceA)
{
     int i,j,k;
     TYPE_ELEMENTS_MATRICE Cii, Cji;
     
     
     if(matriceA->proprietes==NON_SYMETRIQUE)
          return 0;
     
     else
     {
          /* Creation matrice resultat */
          matrice *cholesky=creer_matrice(strcat(matriceA->nom, "_Cholesky"), matriceA->nb_lignes, matriceA->nb_colonnes, NON_SYMETRIQUE);
          
          
          /* Implementation de la methode de Cholesky */
          for (i=0; i<cholesky->nb_lignes; i++)
          {
               /* Calcul de Cii */
               Cii=matriceA->tableau_2d[i][i];     
               for(k=0;k<i;k++)
               {
                    Cii-=cholesky->tableau_2d[i][k]*cholesky->tableau_2d[i][k];                         
               }
               cholesky->tableau_2d[i][i]=sqrt(Cii);
               
               for (j=i+1; j<cholesky->nb_colonnes; j++) cholesky->tableau_2d[i][j]=0; // On remplit le triangle vide par des 0
               
               for (j=i+1; j<cholesky->nb_colonnes; j++)
               {
                    Cji=matriceA->tableau_2d[i][j];
                    for(k=0;k<i;k++)
                    {
                         Cji-=cholesky->tableau_2d[i][k]*cholesky->tableau_2d[j][k];                         
                    }
               cholesky->tableau_2d[j][i]=Cji/cholesky->tableau_2d[i][i];
               }
          }
          
          
          return cholesky;
     }
     
     

}