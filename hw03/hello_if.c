#include <stdio.h>
#include <omp.h>
int main(int argc,char* argv[]) {
	#pragma omp parallel
	{
		int nthreads,tid;
		int nprocs;
		tid = omp_get_thread_num();
#ifdef _CN
		printf("你好，世界 多线程%d\n",tid);
#else
		printf("Hello World From OMP thread %d\n ",tid);
#endif
		if(tid==0) {
			nthreads = omp_get_num_threads();
#ifdef _CN
			printf("总线程数%d\n",nthreads);
#else
			printf("Num of threads %d\n",nthreads);
#endif
		}
	}
#ifdef _CN
	printf("你好，世界\n");
#else
	printf("Hello, World! \n");
#endif
	return 0;
}

