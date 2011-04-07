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
     free(matriceA->tableau_2d[0]);
     free(matriceA->tableau_2d);
     free(matriceA);
}


/* Fonctions de calcul */
matrice* produitMatriciel(matrice *matriceA, matrice *matriceB)
{
     /* Verification compatibilite matrices */
     if(matriceA->nb_colonnes!=matriceB->nb_lignes)
          return NULL;
     
     else
     {
          char nouveauNom[255];
          strcpy(nouveauNom,matriceA->nom);
          strcat(nouveauNom," * ");
          strcat(nouveauNom,matriceB->nom);
          
          /* Creation matrice bonnes dimensions */
          matrice *produit=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceB->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
          
          /* Calcul du produit */
          calculProduit(matriceA->tableau_2d, matriceB->tableau_2d, produit->tableau_2d, matriceA->nb_lignes, matriceA->nb_colonnes, matriceB->nb_colonnes);

          return produit;
     }
     
}


void calculProduit(TYPE_ELEMENTS_MATRICE **tableauA, TYPE_ELEMENTS_MATRICE **tableauB, TYPE_ELEMENTS_MATRICE **tableauResultat, int nbLignesA, int nbColonnesA, int nbColonnesB)
{
     int i,j,k,tmp;
     
     for(i=0;i<nbLignesA;i++)  // ligne de calcul de la premiere matrice
     {
          for(j=0;j<nbColonnesB;j++)  // colonne de calcul de la deuxieme matrice
          {
               tmp=0;
               for(k=0;k<nbColonnesA;k++)
               {
                    tmp+=tableauA[i][k]*tableauB[k][j];
               }
               tableauResultat[i][j]=tmp;
          }
     }
}


matrice* decompositionCholesky(matrice *matriceA)      // retourne un pointeur vers la matrice decomposee ou NULL si une erreur s'est produite
{
     if(matriceA->symetrique==NON_SYMETRIQUE || matriceA->inversible!=INVERSIBLE || matriceA->positive!=POSITIVE)
          return NULL;
     
     else
     {
          char nouveauNom[255];
          strcpy(nouveauNom,matriceA->nom);
          strcat(nouveauNom,"_Cholesky");
          /* Creation matrice resultat */
          matrice *decompCholesky=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceA->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
          if(cholesky(matriceA->tableau_2d,decompCholesky->tableau_2d,matriceA->nb_lignes)==0)  // y a t il eu un probleme?
          {
               detruire_matrice(decompCholesky);
               return NULL;
          }
          return decompCholesky;
     }
     
}

int cholesky(TYPE_ELEMENTS_MATRICE **tableauADecomposer, TYPE_ELEMENTS_MATRICE **tableauResultat, int dimension)
{
     int i,j,k;
     TYPE_ELEMENTS_MATRICE Cii;
     
     /* Implementation de la methode de Cholesky */
     for (i=0; i<dimension; i++)
     {
          for (j=0; j<=i; j++)
          {
               Cii=tableauADecomposer[i][j];
     
               tableauResultat[j][i] = 0;
     
               for (k=0; k<j; k++)
                    Cii-=tableauResultat[i][k]*tableauResultat[j][k];      
     
               if (i==j)
               {
                    if(Cii<0) return 0;  // pas de racine de nombre neg, sinon erreur.
                    Cii = sqrt(Cii);
                    
                    tableauResultat[i][j] = Cii;
               } 
               else tableauResultat[i][j] = Cii/tableauResultat[j][j];
          }
     } 
     return 1; // tout est ok
}




int decompositionLU(matrice *matriceA, matrice **matriceA_L, matrice **matriceA_U)      // retourne 1 si succes ou 0 si une erreur s'est produite
{
     if(matriceA->symetrique==SYMETRIQUE || matriceA->inversible!=INVERSIBLE || matriceA->positive!=POSITIVE)
          return 0;
     
     else
     {    
          char nouveauNom[255];
          
          strcpy(nouveauNom,matriceA->nom);
          strcat(nouveauNom,"_L");
          matrice *decompL=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceA->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
          
          strcpy(nouveauNom,matriceA->nom);
          strcat(nouveauNom,"_U");
          matrice *decompU=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceA->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);
          
          if(decompLU(matriceA->tableau_2d, decompL->tableau_2d, decompU->tableau_2d, matriceA->nb_lignes)==0) return 0;
          else
          {
               *matriceA_L=decompL;
               *matriceA_U=decompU;
               return 1;
          }
     }
     
}

int decompLU(TYPE_ELEMENTS_MATRICE **tableauADecomposer, TYPE_ELEMENTS_MATRICE **tableauL, TYPE_ELEMENTS_MATRICE **tableauU, int dimension)
{
     int i,j,k;
     
     TYPE_ELEMENTS_MATRICE tmpLU;
     
     for(j=0;j<dimension;j++)
     {
          tableauL[j][j]=1;
          for(i=0;i<=j;i++)
          {
               tmpLU=tableauADecomposer[i][j];
               tableauU[j][i]=0;
               for(k=0;k<i;k++)
               {
                    tmpLU-=tableauL[i][k]*tableauU[k][j];
               }
               tableauU[i][j]=tmpLU;
          }
          for(i=j+1;i<dimension;i++)
          {
               tmpLU=tableauADecomposer[i][j];
               tableauL[j][i]=0;
               for(k=0;k<j;k++)
                    {
                         tmpLU-=tableauL[i][k]*tableauU[k][j];
                    }
               tableauL[i][j]=tmpLU/tableauU[j][j];
          }
     }
     
     
     return 1;
}



matrice* resolutionGauss(matrice *matriceA, matrice *matriceB)      // retourne pointeur vers X si succes ou NULL si une erreur s'est produite
{
     if(matriceA->symetrique==SYMETRIQUE || matriceA->inversible!=INVERSIBLE || matriceA->positive!=POSITIVE || matriceA->nb_lignes!=matriceB->nb_lignes || matriceB->nb_colonnes!=1)
          return NULL;
     
     else
     {    
          char nouveauNom[255];
          
          strcpy(nouveauNom,"Solution[");
          strcat(nouveauNom,matriceA->nom);
          strcat(nouveauNom,"*(?)=");
          strcat(nouveauNom,matriceB->nom);
          strcat(nouveauNom,"]");
          matrice *solAXB=creer_matrice(nouveauNom, matriceA->nb_lignes, 1,NON_SYMETRIQUE, INVERSIBLE, NON_POSITIVE);
          
          if(pivotDeGauss(matriceA->tableau_2d, matriceB->tableau_2d, matriceA->nb_lignes, solAXB->tableau_2d)==0) return NULL;
          else
          {
               return solAXB;
          }
     }
     
}


int pivotDeGauss(TYPE_ELEMENTS_MATRICE **tableauA, TYPE_ELEMENTS_MATRICE **tableauB, int n, TYPE_ELEMENTS_MATRICE **tableauX) // vaut 0 si pivot nul et resolution impossible ou 1 si succes
{

     int i,j,k;
     TYPE_ELEMENTS_MATRICE pivot,tmp;
     
     TYPE_ELEMENTS_MATRICE **TAB=(TYPE_ELEMENTS_MATRICE**) malloc (n*sizeof(TYPE_ELEMENTS_MATRICE*));
     TAB[0]=(TYPE_ELEMENTS_MATRICE*) malloc (n*n*sizeof(TYPE_ELEMENTS_MATRICE));
     
     for(i=1;i<n;i++)                   //on copie tableauA dans un tableau temporaire
     {                                  // pour pouvoir faire les permutations sans perdre les informations d'origine
          TAB[i]=TAB[i-1]+n;
     }
     
     for(i=0; i<n*n; i++)
     {
          TAB[0][i]=tableauA[0][i];          
     } 
         
         
     for(k=0;k<n-1;k++)
     {
          if(TAB[k][k]==0)
          {
               free(TAB[0]);
               free(TAB);
               return 0;
          }

          //reduction
          for(i=k+1;i<n;i++)
          {
               pivot=TAB[i][k]/TAB[k][k];
               for (j=k;j<n;j++) TAB[i][j]=TAB[i][j]-pivot*TAB[k][j];
               tableauB[0][i]=tableauB[0][i]-pivot*tableauB[0][k];
          }
     }
     
     /*  resolution par pivot de Gauss */
     
     for(i=n-1;i>=0;i--)
     {
          tmp=tableauB[0][i];   
          for(j=i+1;j<n;j++)
               tmp-=TAB[i][j]*tableauX[0][j];                    
          tableauX[0][i]=tmp/TAB[i][i];
     }     
 
     free(TAB[0]);
     free(TAB);
     return 1;
}





int solve(matrice *matriceA, matrice *matriceB, matrice *matriceX)
{
     if(matriceA->symetrique==NON_SYMETRIQUE)   //methode LU
     {
          matrice *A_L, *A_U;
          if(decompositionLU(matriceA,&A_L,&A_U)==0) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
               
          else
          {
               printf("La decomposition LU donne la matrice L suivante:");
               afficher_matrice(*A_L);

               matrice *Y=resolutionGauss(A_L, matriceB);
               if(Y==NULL) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                    
               else
               {
                    printf("La resolution par Gauss donne la matrice Y suivante:");
                    afficher_matrice(*Y);
                    
                    matriceX=resolutionGauss(A_U, Y);
                    if(matriceX==NULL) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                         
                    else
                    {
                         printf("La resolution par Gauss donne la matrice X suivante:");                     
                         strcpy(matriceX->nom,"SOLUTION FINALE");
                         afficher_matrice(*matriceX);
                         detruire_matrice(matriceX);

                    }               
                    detruire_matrice(Y);
               } 
               detruire_matrice(A_L);
               detruire_matrice(A_U);

          }
          
     }
     
     else                                       //methode Cholesky
     {
          matrice *C=decompositionCholesky(matriceA);
          if(C==NULL)
               printf("La matrice que vous essayez de decomposer n'est pas symetrique ou pas definie positive.\n");
          else
          {
               printf("La decomposition Cholesky donne la matrice C suivante:");               
               afficher_matrice(*C);
               
               matrice *Y=resolutionGauss(C, matriceB);
               if(Y==NULL) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                    
               else
               {
                    printf("La resolution par Gauss donne la matrice Y suivante:");
                    afficher_matrice(*Y);
                    matrice *CT=transposerMatrice(C);               
                    afficher_matrice(*CT);
                    
                    matriceX=resolutionGauss(CT, Y);
                    if(matriceX==NULL) printf("La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                         
                    else
                    {
                         printf("La resolution par Gauss donne la matrice X suivante:");                     
                         strcpy(matriceX->nom,"SOLUTION FINALE");
                         afficher_matrice(*matriceX);
                         detruire_matrice(matriceX);                         
                    }      
                    detruire_matrice(CT);
                    detruire_matrice(Y);
               }         
               detruire_matrice(C);
          }
          
     }
          
}