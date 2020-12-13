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
	int world_rank, world_size;
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
	mess max, min, out;
	max = min=arr[0];
	t1 = omp_get_wtime();
	#pragma omp parallel for
	for(i=0;i<N;i++){
		if(max.value<arr[i].value)
			max = arr[i];
	}
	free(arr);
	arr = NULL;
	t2 = omp_get_wtime();
	printf("maxrank=%d,maxindex=%d,maxvalue=%f,time=%f(s)\n",max.index,max.index,max.value,t2-t1);

	return 0;
}

