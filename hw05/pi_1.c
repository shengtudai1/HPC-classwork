#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
double start, end;
int main(){
	start = omp_get_wtime();
	int i;
	double x, pi, sum[omp_get_max_threads()];
	step = 1.0/(double)num_steps;
	#pragma omp parallel private(x,i)
	{
	int id;
	id = omp_get_thread_num();
	for(i=id,sum[id]=0.0;i<num_steps;i+=omp_get_num_threads()){
		x = (i-0.5) * step;
		sum[id] += 4.0/(1.0+x*x);		
		}
	}

	for(i=0,pi=0.0;i<omp_get_max_threads();i++)
		pi += sum[i]*step;
	end = omp_get_wtime();
	printf("%d\t%fs\t",omp_get_max_threads(),end-start);


	return 0;

}
