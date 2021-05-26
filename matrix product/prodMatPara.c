#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define CHUNKSIZE 10

void initMat(int n,int m, int *A){
    int i,j;
    /*Initialiser la matrice avec des valeurs aléatoires entre 0 et 10*/
    #pragma omp parallel private(i,j) 
      {
      #pragma omp for schedule(dynamic,CHUNKSIZE)
      for(i=0;i<n;i++)
          for(j=0;j<m;j++)
              A[i*m+j] = rand()%10;
      }
}

void afficheMat(int n,int m, int *A){
    int i,j;
    #pragma omp parallel private(i,j)
    {
        #pragma omp for schedule(dynamic,CHUNKSIZE)
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                printf("%d ",A[i*m+j]);
            }
            printf("\n");
        }
    }
}

void produitMat(int n,int m, int p, int *A, int *B, int *C){
    int i,j,k;
    
    /*initialiser les coefficients de C à 0*/
    #pragma omp parallel private(i,k)
      {
      #pragma omp for schedule(dynamic,CHUNKSIZE)
      for(i=0;i<n;i++){
         for(k=0;k<p;k++){
              C[i*n+k] = 0;
          }
      }
      }
    
    /* Affecter le resultat de multiplication de A et B à C*/ 
    #pragma omp parallel private(i,j,k) shared(A,B,C)
      {
        #pragma omp for schedule(dynamic,CHUNKSIZE)
        for(i=0;i<n;i++){
            for(k=0;k<p;k++){
                for(j=0;j<m;j++){
                    C[i*p+k] += A[i*m+j] * B[j*p+k];
                }
            }
        }
      }
}

void main(){
    float temps;
    clock_t t1, t2;
    t1 = clock();
    int np = omp_get_num_procs();
    omp_set_num_threads(np);
    int *A, *B, *C;
    const int n = 20;
    const int m = 30;
    const int p = 40;
    A=(int*)malloc(n*m*sizeof(int));
    B=(int*)malloc(m*p*sizeof(int));
    C=(int*)malloc(n*p*sizeof(int));
    initMat(n,m,A);
    initMat(m,p,B);
    produitMat(n,m,p,A,B,C);
    printf("La matrice A \n");
    afficheMat(n,m,A);
    printf("La matrice B \n");
    afficheMat(m,p,B);
    printf("La matrice C \n");
    afficheMat(n,p,C);
    t2 = clock();
    /*calcul la durée d'execution*/
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
}
