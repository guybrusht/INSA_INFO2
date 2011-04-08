#include "head.h"

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
          matrice *produit=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceB->nb_colonnes,NON_SYMETRIQUE, NON_INVERSIBLE, NON_POSITIVE);
          
          
          /* Calcul du produit */
          if(matriceA->symetrique==SYMETRIQUE)
               calculProduitSym(matriceA->tableau_2d, matriceB->tableau_2d, produit->tableau_2d, matriceA->nb_lignes, matriceA->nb_colonnes, matriceB->nb_colonnes);

          else
               calculProduit(matriceA->tableau_2d, matriceB->tableau_2d, produit->tableau_2d, matriceA->nb_lignes, matriceA->nb_colonnes, matriceB->nb_colonnes);

          return produit;
     }
     
}


void calculProduit(TYPE_ELEMENTS_MATRICE **tableauA, TYPE_ELEMENTS_MATRICE **tableauB, TYPE_ELEMENTS_MATRICE **tableauResultat, int nbLignesA, int nbColonnesA, int nbColonnesB)
{
     int i,j,k;
     TYPE_ELEMENTS_MATRICE tmp;
     
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

void calculProduitSym(TYPE_ELEMENTS_MATRICE **tableauA, TYPE_ELEMENTS_MATRICE **tableauB, TYPE_ELEMENTS_MATRICE **tableauResultat, int nbLignesA, int nbColonnesA, int nbColonnesB)
{
     int i,j,k;
     TYPE_ELEMENTS_MATRICE tmp;
     
     for(i=0;i<nbLignesA;i++)  // ligne de calcul de la premiere matrice
     {
          for(j=0;j<nbColonnesB;j++)  // colonne de calcul de la deuxieme matrice
          {
               tmp=0;
               for(k=0;k<=i;k++)
               {
                    tmp+=tableauA[i][k]*tableauB[k][j];
               }
               for(k=i+1;k<nbColonnesA;k++)
               {
                    tmp+=tableauA[k][i]*tableauB[k][j];
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
     if(matriceA->symetrique==SYMETRIQUE || matriceA->inversible!=INVERSIBLE || matriceA->positive!=POSITIVE || matriceA->nb_lignes!=matriceB->nb_lignes)
          return NULL;
     
     else
     {    
          char nouveauNom[255];
          
          strcpy(nouveauNom,"Solution[");
          strcat(nouveauNom,matriceA->nom);
          strcat(nouveauNom,"*(?)=");
          strcat(nouveauNom,matriceB->nom);
          strcat(nouveauNom,"]");
          matrice *solAXB=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceB->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, NON_POSITIVE);
          
          if(pivotDeGauss(matriceA->tableau_2d, matriceB->tableau_2d, matriceA->nb_lignes, matriceB->nb_colonnes, solAXB->tableau_2d)==0) return NULL;
          else
          {
               return solAXB;
          }
     }
     
}


int pivotDeGauss(TYPE_ELEMENTS_MATRICE **tableauA, TYPE_ELEMENTS_MATRICE **tableauB, int n, int m, TYPE_ELEMENTS_MATRICE **tableauX) // vaut 0 si pivot nul et resolution impossible ou 1 si succes
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
               for(j=k;j<n;j++) TAB[i][j]=TAB[i][j]-pivot*TAB[k][j];
               for(j=0;j<m;j++) tableauB[i][j]=tableauB[i][j]-pivot*tableauB[k][j];//
          }
     }
     
     /*  resolution par pivot de Gauss */
     
     for(k=0;k<m;k++)//
     {
          
          for(i=n-1;i>=0;i--)
          {

               tmp=tableauB[i][k];   
               for(j=i+1;j<n;j++)
                    tmp-=TAB[i][j]*tableauX[j][k];                    
               tableauX[i][k]=tmp/TAB[i][i];

          }     
     }
 
     free(TAB[0]);
     free(TAB);
     return 1;
}





int solve(matrice *matriceA, matrice *matriceB, matrice **matriceX)
{
     if(matriceA->symetrique==NON_SYMETRIQUE)   //methode LU
     {
          matrice *A_L, *A_U;
          if(decompositionLU(matriceA,&A_L,&A_U)==0)
          {
               #ifdef DBG
               printf("ECHEC: La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
               #endif
               return 0;
          }
          
          else
          {
               printf("La decomposition LU donne la matrice L suivante:");
               afficher_matrice(*A_L);

               matrice *Y=resolutionGauss(A_L, matriceB);
               if(Y==NULL)
               {
                    #ifdef DBG
                    printf("ECHEC: La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                    #endif
                    return 0;
               }
               
               else
               {
                    printf("La resolution par Gauss donne la matrice Y suivante:");
                    afficher_matrice(*Y);
                    
                    matrice *X=resolutionGauss(A_U, Y);
                    if(X==NULL)
                    {
                         #ifdef DBG     
                         printf("ECHEC: La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                         #endif
                         return 0;
                    }
                    
                    else
                    {
                         printf("\n\n\n\n\n");       
                         printf("****************************************************\n");       
                         printf("La resolution par Gauss donne la matrice X suivante:\n");
                         printf("****************************************************");                           
                         strcpy(X->nom,"SOLUTION FINALE");
                         afficher_matrice(*X);
                         *matriceX=X;
                    }               
                    detruire_matrice(Y);
               } 
               detruire_matrice(A_L);
               detruire_matrice(A_U);
               
               return 1;

          }
          
     }
     
     else                                       //methode Cholesky
     {
          matrice *C=decompositionCholesky(matriceA);
          if(C==NULL)
          {
               #ifdef DBG
               printf("ECHEC: La matrice que vous essayez de decomposer n'est pas symetrique ou pas definie positive.\n");
               #endif
               return 0;
          }
          
          else
          {

               printf("La decomposition Cholesky donne la matrice C suivante:");               
               afficher_matrice(*C);
               matrice *Y=resolutionGauss(C, matriceB);
               if(Y==NULL)
               {
                    #ifdef DBG     
                    printf("ECHEC: La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                    #endif
                    return 0;
               }
               
               else
               {

                    printf("La resolution par Gauss donne la matrice Y suivante:");
                    afficher_matrice(*Y);
                    matrice *CT=transposerMatrice(C);               
                    afficher_matrice(*CT);
                    
                    matrice *X=resolutionGauss(CT, Y);
                    if(X==NULL)
                    {
                         #ifdef DBG     
                         printf("ECHEC: La matrice que vous essayez de decomposer est symetrique ou pas definie positive.\n");
                         #endif
                         return 0;
                    }
                    
                    else
                    {
                         printf("\n\n\n\n\n");       
                         printf("****************************************************\n");       
                         printf("La resolution par Gauss donne la matrice X suivante:\n");
                         printf("****************************************************");                        
                         strcpy(X->nom,"SOLUTION FINALE");
                         afficher_matrice(*X);
                         *matriceX=X;
                    }      
                    detruire_matrice(CT);
                    detruire_matrice(Y);
               }         
               detruire_matrice(C);
               return 1;
          }
          
     }
          
}


TYPE_ELEMENTS_MATRICE determinantMatrice(matrice* matriceA)
{
     if(matriceA->symetrique==NON_SYMETRIQUE) return determinant(matriceA->tableau_2d,matriceA->nb_lignes);
     else
     {
          TYPE_ELEMENTS_MATRICE **pleine = malloc((matriceA->nb_lignes)*sizeof(TYPE_ELEMENTS_MATRICE *));
          int i,j;
          for (i=0;i<matriceA->nb_lignes;i++)
               pleine[i] = malloc((matriceA->nb_lignes)*sizeof(TYPE_ELEMENTS_MATRICE));
          
          for (i=0;i<matriceA->nb_lignes;i++)
          {
               for (j=0;j<=i;j++)
                    pleine[i][j]=matriceA->tableau_2d[i][j];
               for (j=i+1;j<matriceA->nb_lignes;j++)
                    pleine[i][j]=matriceA->tableau_2d[j][i];
          }
          
          
          TYPE_ELEMENTS_MATRICE det=determinant(pleine,matriceA->nb_lignes);
          for (i=0;i<matriceA->nb_lignes;i++)
               free(pleine[i]);
          free(pleine);
          return det;
     }
          
}


TYPE_ELEMENTS_MATRICE determinant(TYPE_ELEMENTS_MATRICE **tableauA, int n) // n doit etre > 1
{
     int i,j,j1,j2;
     TYPE_ELEMENTS_MATRICE det = 0;
     TYPE_ELEMENTS_MATRICE **m = NULL;

     if (n==2)
          det = tableauA[0][0] * tableauA[1][1] - tableauA[1][0] * tableauA[0][1];
     else if (n>2)
     {
          det = 0;
          for (j1=0;j1<n;j1++)
          {
               m = malloc((n-1)*sizeof(TYPE_ELEMENTS_MATRICE *));
               for (i=0;i<n-1;i++)
                    m[i] = malloc((n-1)*sizeof(TYPE_ELEMENTS_MATRICE));
               for (i=1;i<n;i++)
               {
                    j2 = 0;
                    for (j=0;j<n;j++) 
                    {
                         if (j == j1) continue;
                    m[i-1][j2] = tableauA[i][j];
                    j2++;
                    }
               }
               det += pow(-1.0,1.0+j1+1.0) * tableauA[0][j1] * determinant(m,n-1);
               for (i=0;i<n-1;i++)
                    free(m[i]);
               free(m);
          }
     }
     return(det);
}


