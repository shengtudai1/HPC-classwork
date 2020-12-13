#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
int main(){
	int NUM_THREADS = omp_get_max_threads();
	double start, end;
	start = omp_get_wtime();
	double pi,sum = 0.0;
	step = 1.0/(double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{double x;
	int i;
	#pragma omp for reduction(+:sum)
	for(i=1;i<num_steps;i++){
		x = (i+0.5) * step;
		sum += 4.0/(1.0+x*x);
	}
		pi =  sum * step;
	}
	end = omp_get_wtime();
	printf("%f\n",end-start);
	return 0;
}

