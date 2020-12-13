#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "time.h"
#include "crt_rand.h"
typedef struct{
float value;
int index;
} mess;
int main(int argc, char* argv[]){
	int i,j,N;
	double t1, t2;
	N = atoi(argv[1]);
	float* a;
	a = crtarr(N,1);
	int numt = omp_get_max_threads();
	mess* arr = NULL;
	arr = (mess*)malloc(sizeof(mess)*N);
        if(arr==NULL){
                printf("内存分配失败\n");
                exit(-1);
                }
	for(i=0;i<N;i++){
	//	printf("%f\n",a[i]);
		arr[i].value = a[i];
		arr[i].index = i;
	}
	free(a);
	a = NULL;
	mess out;
	mess** max = (mess**)malloc(sizeof(mess*)*numt);
	for(i=0;i<numt;i++){
		max[i] = (mess*)malloc(sizeof(mess)*8);
		}
	t1 = omp_get_wtime();
	#pragma omp parallel
	{
	int id = omp_get_thread_num();
	int nums = omp_get_num_threads();
	int step = N/nums;
	max[id][0] = arr[id*step];
	if(id!=nums-1){
		for(i=id*step;i<(id+1)*step;i++){
			if(max[id][0].value<arr[i].value)
				max[id][0] = arr[i];
		}
	}
	else{
		for(i=id*step;i<N;i++){
			if(max[id][0].value<arr[i].value)
				max[id][0] = arr[i];
		}
	}
	}
	free(arr);
	arr = NULL;
	out = max[0][0];
	for(i=0;i<numt;i++){
		if(out.value<max[i][0].value)
                                out.value = max[i][0].value;
	}
	t2 = omp_get_wtime();
	printf("maxrank=%d,maxindex=%d,maxvalue=%f,time=%f(s)\n",out.index,out.index,out.value,t2-t1);

	return 0;
}

