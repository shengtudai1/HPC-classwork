#include <stdio.h>
#include <omp.h>
#define N 100000000
int arr[N];
int main(){
	double start, end;
	int NUM_THREADS = omp_get_max_threads();
	int i,j = 0;
	double k =0;
	#pragma omp prallel for private(i)
	for(i=0;i<N;i++)
		arr[i] = i+1;
	long long sum = 0;
	start = omp_get_wtime();
	#pragma omp parallel for private(i) reduction(+:sum)
	for(i=0;i<N-2;i++){
		sum += (arr[i]+arr[i+1]+arr[i+2]);
	}
	k = sum/2.0;
	end = omp_get_wtime();
	printf("%d\t%f\t%f\n",NUM_THREADS,k,end-start);
	return 0;
}
