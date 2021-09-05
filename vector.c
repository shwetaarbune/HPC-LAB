#include <omp.h>
#include <stdio.h>
#include<stdlib.h>
int main() {
    int n=5;
    int a[n], c[n];
    int flag[n];
    printf("Total number of elements in the array is %d",n);
    
    for(int i=0;i<n;i++)
    {
    	a[i]=i;
    	flag[i]=0;
    }
	int scalar=10;
	omp_set_num_threads(5);
	#pragma omp parallel shared(c)
	for(int i = 0;i < n;i++) {
		if(!flag[i])
		{
			c[i]=a[i]+scalar;
			flag[i]=1;
			printf("\nThread number %d, executing iteration %d first time",omp_get_thread_num(),i);	

		}
		else
		{
			printf("\nThread number %d, executing iteration %d but already done",omp_get_thread_num(),i);	
		}
	
	}
	
	printf("\ni\ta[i]\t+scalar\t=\tb[i]\n");
        for(int i=0; i<n; i++) 
	{
		printf("%d\t%d\t%d\t=\t%d\n", i, a[i],scalar,c[i]);
        }
	
}
