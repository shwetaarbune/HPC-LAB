#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#define tot_threads 1
int main(int argc, char *argv[])
{
clock_t t;
t = clock();
int tid;
int i,j;
int rows,cols;

printf("Enter Number of Rows of matrices\n");
scanf("%d",&rows);
printf("Enter Number of Columns of matrices\n");
scanf("%d",&cols);

int a[rows][cols];
int b[rows][cols];
int c[rows][cols];

int *d,*e,*f;
int nthreads;

printf("Enter %d elements of first matrix\n",rows*cols);
for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       scanf("%d",&a[i][j]);
    }

printf("Enter %d elements of second matrix\n",rows*cols);
for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       scanf("%d",&b[i][j]);
    }

d=(int *)malloc(sizeof(int)*rows*cols);
e=(int *)malloc(sizeof(int)*rows*cols);
f=(int *)malloc(sizeof(int)*rows*cols);

d=(int *)a;
e=(int *)b;
f=(int *)c;
#pragma omp parallel shared(d,e,f,nthreads) private(tid,i,j) num_threads(8)
	{
	
		tid = omp_get_thread_num();
		if (tid == 0)
		{
			nthreads = 4;
			printf("Starting matrix Addition example with %d threads\n",nthreads);
			printf("Initializing matrices...\n");
		}
}


#pragma omp parallel num_threads(rows*cols)
  {
    tid=omp_get_thread_num();
    f[tid]=d[tid]+e[tid];
  }

printf("Values of Resultant Matrix C are as follows:\n");

for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       printf("Value of C[%d][%d]=%d\n",i,j,c[i][j]);
    }
printf ("Done.\n");
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("\nTime taken by program for %d threads with matrix size %d + %d is %f sec",tot_threads,rows,cols,time_taken);
	
return 0;

}