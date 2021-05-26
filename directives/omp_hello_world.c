#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
 
int main(void){
int i;
int x;
x=44;
int OMP_NUM_THREADS=7;
#pragma omp parallel for shared(x) 
for(i=0;i<=5;i++){
x=i;
printf("Thread number: %d     x: %d\n",omp_get_thread_num(),x);
}
printf("x is %d\n", x);
 
 
}
