#include <omp.h>
#include <bits/stdc++.h>
#include<stdlib.h>


void static_schedule(int n,int chunk_size)
{
	int *a, *b, *c;
    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    c=(int*)malloc(n*sizeof(int));
    
    #pragma omp parallel for schedule(static, chunk_size) 
    for(int i=0;i<n;i++)
    {
    	a[i]= i;
    	b[i] = 2*i;
	}
	
	#pragma omp parallel for schedule(static, chunk_size)
	for(int i = 0 ;i < n;i++) {
		c[i] = a[i] + b[i];
	}
	
	free(a);
	free(b);
	free(c);

	
}

void dynamic_schedule(int n,int chunk_size)
{
	int *a, *b, *c;
    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    c=(int*)malloc(n*sizeof(int));
    
    #pragma omp parallel for schedule(static, chunk_size)
    for(int i=0;i<n;i++)
    {
    	a[i]= i;
    	b[i] = 2*i;
  }
	
	#pragma omp parallel for schedule(static, chunk_size)
	for(int i = 0;i < n;i++) {
		c[i] = a[i] + b[i];
	}
	
	free(a);
	free(b);
	free(c);

	
}


int main() {

    int n = 200;
	
	int chunk[] = {1,2,4,18,16};
	printf("\nStatic scheduling \n\n");
	while(n < 800000)
	{
		printf("\nfor vector size %d ",n);
		for(int i=0;i<5;i++)
		{
			clock_t t;
	    	t = clock();
	    	static_schedule(n,chunk[i]);
	    	t = clock() - t;
			double time_taken = ((double)t)/CLOCKS_PER_SEC;
		
			printf("\nfor chunck with size %d it will take time %f",chunk[i],time_taken);
		}
		printf("\n\n");
		n += n;
	}
	
	n = 200;
	printf("\n Dynamic scheduling \n\n");
	while(n < 80000)
	{
		printf("\nfor vector size %d ",n);
		for(int i=0;i<5;i++)
		{
			clock_t t;
	    	t = clock();
	    	dynamic_schedule(n,chunk[i]);
	    	t = clock() - t;
			double time_taken = ((double)t)/CLOCKS_PER_SEC;
		
			printf("\nfor chunck with size %d it will take time %f",chunk[i],time_taken);
		}
		printf("\n\n");
		n += n;
	}
	
	int *a, *b, *c,i=0;
	n = 200;
    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    c=(int*)malloc(n*sizeof(int));
    
	
	printf("\nNo wait clause\n\n");
	#pragma omp parallel private(i) num_threads(4)
	{
		int tid = omp_get_thread_num();
		#pragma omp for
		for(i=0;i<n;i++)
			c[i] = a[i] + b[i];
		printf("\nThread %d has executed first for", tid);
		printf("\nDone first for by %d!",tid);
		
		#pragma omp for nowait
		for(i=0;i<n;i++)
			c[i] = a[i] + b[i];
		printf("\nThread %d has executed nowait for", tid);
		printf("\nDone no wait for by %d!",tid);
		
		
	}
}
