#include <stdio.h>
#include <omp.h>
int main(){
	int num_threads;
	omp_set_dynamic(0);
	omp_set_num_threads(omp_get_num_procs());
	#pragma omp parallel
	{
	int id = omp_get_thread_num();
	int max = omp_get_max_threads();
	int dynamics = omp_get_dynamic();
	int procs_num = omp_get_num_procs();
	printf("id=%d\n",id);
	printf("max=%d\n",max);
	printf("dynamics=%d\n",dynamics);
	printf("procs_num=%d\n",procs_num);
	}
	printf("-----------------------------\n");
	int id = omp_get_thread_num();
        int max = omp_get_max_threads();
        int dynamics = omp_get_dynamic();
        int procs_num = omp_get_num_procs();
        printf("id=%d\n",id);
        printf("max=%d\n",max);
        printf("dynamics=%d\n",dynamics);
        printf("procs_num=%d\n",procs_num);
	return 0;
}
