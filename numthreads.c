#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    omp_set_num_threads(8);
 
    #pragma omp parallel
    {
 	printf("Hello from 2019BTECS00205 with thread id= %d\n",omp_get_thread_num());
    }
    

}