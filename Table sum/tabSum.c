#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define CHUNKSIZE 10

void main(){
    float temps;
    clock_t t1, t2;
    t1 = clock();
    int i,j;
    int nt = 4;
    int taille = 100;
    int t[nt][taille];
    omp_set_num_threads(4);
    
    /*initialisation*/
    for(i=0;i<nt;i++){
        for(j=0;j<taille;j++){
            t[i][j] = rand()%10;
        }
    }
    
    /*affichage des tableaux avant calcul*/
    printf("Les tableaux avant le calcul \n");
    for(i=0;i<nt;i++){
        printf("le Tableau %d : ",i);
        for(j=0;j<taille;j++){
            printf("%d%d ",i,t[i][j]);
        }
        printf("\n");
    }
    
    /*calcul*/
    #pragma omp parallel private(i,j) shared(t)
    {
        #pragma omp for schedule(dynamic,CHUNKSIZE)
        for(i=0;i<nt;i++){
            t[i][1]=t[i][1]+t[i][0];
            for(j=2;j<taille;j++){
                t[i][j]=t[i][j-2]+t[i][j-1];
            }
        }
    }
    
    /*affichage des tableaux après calcul*/
    printf("Les tableaux après le calcul \n");
    for(i=0;i<nt;i++){
        printf("le Tableau %d : ",i);
        for(j=0;j<taille;j++){
            printf("%d%d ",i,t[i][j]);
        }
        printf("\n");
    }
    t2 = clock();
    /*calcul la durée d'execution*/
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
    
}