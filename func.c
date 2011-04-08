#include "head.h"


TYPE_ELEMENTS_MATRICE* recupererNValeurs(int n)
{
     int i=0;
     TYPE_ELEMENTS_MATRICE *TAB=(TYPE_ELEMENTS_MATRICE*) malloc (n*sizeof(TYPE_ELEMENTS_MATRICE));
     
     for(i=0; i<n; i++)
     {
          printf(" >   ");
          scanf("%"FORMAT_PRINTF,&TAB[i]);
     }
         
     return TAB;
}






/* Matrices -------------------------------------------------------*/

matrice* creer_matrice(char *nom_matrice, int nb_lignes_matrice, int nb_colonnes_matrice, int sym, int inv, int pos)
{
     int i=0;
     
     matrice *nouvelle_matrice;
     nouvelle_matrice=(matrice*) malloc (sizeof(matrice));
     strcpy(nouvelle_matrice->nom,nom_matrice);                 // methode pour assigner une chaine de caracteres; ne pas oublier d'inclure string.h
     nouvelle_matrice->nb_lignes=nb_lignes_matrice;
     nouvelle_matrice->nb_colonnes=nb_colonnes_matrice;
     nouvelle_matrice->symetrique=sym;
     nouvelle_matrice->inversible=inv;
     nouvelle_matrice->positive=pos;
     
     if(sym==NON_SYMETRIQUE)
     {
          nouvelle_matrice->remplir=&remplir_matrice_pleine;
          nouvelle_matrice->afficher=&afficher_matrice_pleine;
          nouvelle_matrice->tableau_2d=allouer_matrice_pleine(nb_lignes_matrice, nb_colonnes_matrice);
     }
     
     else if(sym==SYMETRIQUE)
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
     printf("\n############# Matrice ( %s ) \n",matriceA.nom);

     for (i=0; i<matriceA.nb_lignes; i++)
     {
          printf("[\t");
          for (j=0; j<matriceA.nb_colonnes; j++)
               printf("%+"FORMAT_PRINTF"\t",matriceA.tableau_2d[i][j]);
          
          printf("]\n");
     }
     printf("\n");
}

void afficher_matrice_symetrique(matrice matriceA)             //    /!\ distinguer affichage de matrices pleines et symetriques
{
     int i,j;
     printf("\n############# Matrice ( %s ) \n",matriceA.nom);

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
     printf("\n");
}





/* Fonctions de remplissage */
void remplir_matrice(matrice matriceA, TYPE_ELEMENTS_MATRICE *TAB)
{
     matriceA.remplir(matriceA, TAB);
}

void remplir_matrice_pleine(matrice matriceA, TYPE_ELEMENTS_MATRICE *TAB)               /*   /!\ TAB doit contenir le meme nombre d'elements que matriceA, soit nb_lignes*nb_colonnes */
{
     int i=0,j=0;
     
     for(i=0;i<matriceA.nb_lignes;i++)
          for(j=0;j<matriceA.nb_colonnes;j++)
               matriceA.tableau_2d[i][j]=TAB[j+i*matriceA.nb_colonnes];
}

void remplir_matrice_symetrique(matrice matriceA, TYPE_ELEMENTS_MATRICE *TAB)               /*   /!\ TAB doit contenir le meme nombre d'elements que matriceA, soit nb_lignes*nb_colonnes */
{
     int i=0,j=0;
     
     for(i=0;i<matriceA.nb_lignes*(matriceA.nb_lignes+1)/2;i++)
          matriceA.tableau_2d[0][i]=TAB[i];

}


matrice* transposerMatrice(matrice *matriceA)
{
     int i,j;
     
     char nouveauNom[255];
     strcpy(nouveauNom,matriceA->nom);
     strcat(nouveauNom," transposee");
     
     /* Creation matrice */
     matrice *transposee=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceA->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);     

     for(i=0;i<matriceA->nb_lignes;i++)
          for (j=0;j<matriceA->nb_colonnes;j++)
               transposee->tableau_2d[i][j]=matriceA->tableau_2d[j][i];
          
     return transposee;
}




/* Liberation de la memoire allouee */
void detruire_matrice(matrice *matriceA)   
{
     #ifdef DBG
          printf("Liberation memoire de %s...",matriceA->nom);
     #endif
     free(matriceA->tableau_2d[0]);
     free(matriceA->tableau_2d);
     free(matriceA);
     #ifdef DBG
          printf(" OK!\n");
     #endif
}

