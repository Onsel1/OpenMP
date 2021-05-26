#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

// Fonction a integrer
double f(double a) {
  return 4/(1 + a*a);
}

// Dimension par defaut de la taille des matrices
#ifndef VAL_N
#define VAL_N 100000
#endif
#ifdef _OPENMP
#include <omp.h>
#endif
 
int main() {
//#ifdef omp_in_parallel()
//	printf("Ce code est parallel");
//#else 
//	printf("Ce code est sequentiel");

  //                
  //  But : calcul de la constante d'archimède par la methode des rectangles (point milieu).
  //
  //                   / 1
  //                  |       4                   
  //                  |   ----------  dx = constante d'archimède
  //                  |    1 + x**2
  //                 / 0


  int n=VAL_N, k,i;
  double valeur_calculee;
  // Longueur de l'intervalle d'integration.
  double h = 1.0 / n;

  // Temps CPU de calcul initial.
  clock_t t_cpu_0 = clock();

  // Temps elapsed de reference.
  struct timeval t_elapsed_0;
  gettimeofday(&t_elapsed_0, NULL);
  
// Boucle artificielle a ne pas toucher
	for(k=0; k<100; k++) {
		valeur_calculee = 0;
		//#pragma omp parallel for schedule(runtime)
		//#pragma omp parallel for schedule(runtime) private(i) shared(valeur_calculee)
		//#pragma omp parallel for reduction(+:valeur_calculee) schedule(runtime) 
	    for(i = 0; i<n; i++) {
	      double x = h * (i + 0.5); //declaree dans la region parallele donc privee  
	      //#pragma omp atomic
	      //#pragma omp critical
	      valeur_calculee += f(x);
	    }
	    valeur_calculee = h * valeur_calculee;
	}
    
  // Temps elapsed final
  struct timeval t_elapsed_1;
  gettimeofday(&t_elapsed_1, NULL);
  double t_elapsed = (t_elapsed_1.tv_sec - t_elapsed_0.tv_sec) + (t_elapsed_1.tv_usec - t_elapsed_0.tv_usec) / (double)1000000;
  
  // Temps CPU de calcul final
  clock_t t_cpu_1 = clock();
  double t_cpu = (t_cpu_1 - t_cpu_0) / (double)CLOCKS_PER_SEC;

  // Ecart entre la valeur estimee et la valeur calculee 
  double valeur_estimee = acos(-1);   // Valeur estimée 
  double ecart = fabs(valeur_estimee - valeur_calculee);

  // Impression du resultat
  fprintf(stdout, "\n\n"
	  "   Nombre d intervalles       : %10d\n"
	  "   Valeur calculee      : %10.3E\n"
	  "   Valeur estimee      : %10.3E\n"
	  "   |valeur_estimee - valeur_calculee | : %10.3E\n"
	  "   Temps elapsed              : %10.3E sec.\n"
	  "   Temps CPU                  : %10.3E sec.\n",
	  n, valeur_calculee, valeur_estimee, ecart, t_elapsed, t_cpu
	  );

  return EXIT_SUCCESS;
//#endif
}
