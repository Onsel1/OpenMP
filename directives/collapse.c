#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
 
int main(void){
int i;
int j;
#pragma omp parallel for collapse(2) 
for(i=0;i<4;i++){
    for (j=0;j<8;j++){
        printf("Thread: %d, (i,j) = (%d,%d)\n",omp_get_thread_num(),i,j);
    }
}
 printf("Done!");
 
}
