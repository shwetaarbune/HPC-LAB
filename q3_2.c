#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
 
#define N 100            
 
int main (int argc, char *argv[]) 
{ 
int  tid, nthreads, i, j; 
double a[N][N], b[N][N], c[N][N]; 
omp_set_num_threads(8);
 double time = omp_get_wtime();
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j) 
  { 

  tid = omp_get_thread_num(); 
  if (tid == 0) 
    { 
    nthreads = omp_get_num_threads(); 
    printf("Starting matrix addition example with %d threads\n",nthreads); 
    printf("Initializing matrices...\n"); 
    } 
  /* Initialize matrices */ 
  #pragma omp for 
  for (i=0; i<N; i++) 
    for (j=0; j<N; j++) 
      a[i][j]= i+j; 
      
  #pragma omp for 
  for (i=0; i<N; i++) 
    for (j=0; j<N; j++) 
      b[i][j]= i+j; 
      
 
  
  printf("Thread %d starting matrix addition...\n",tid); 

  #pragma omp for 
  for (i=0; i<N; i++) 
    { 
    printf("Thread=%d did row=%d\n",tid,i); 
    for(j=0; j<N; j++) 
        c[i][j] = a[i][j] + b[i][j]; 
    } 
  }  
printf ("Done In %f Seconds",omp_get_wtime() - time); 
printf("\n Using %d Threads",omp_get_max_threads());

return(0); 
}