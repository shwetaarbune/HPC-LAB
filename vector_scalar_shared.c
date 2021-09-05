#include<omp.h>
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	printf("Enter how many numbers you want in array: ");
	scanf("%d",&n);
	int a[n],b,c[n],i;
	
	for(i=0;i<n;i++)
	{
		a[i] = i;
	}
	printf("\nEnter scalar: ");
	scanf("%d",&b);
	
	
	
	#pragma omp parallel for shared(a,b,c) num_threads(n/3)
	for(i=0;i<n;i++)
	{
		c[i] = a[i] + b;
		printf("Thread %d works on element %d of the array\n", omp_get_thread_num(), i);
	}
	
	printf("i\ta[i]\t+\t%d\t=\tc[i]\n",b);
    for(i=0; i<n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], b, c[i]);
    }
	return 0;
}
