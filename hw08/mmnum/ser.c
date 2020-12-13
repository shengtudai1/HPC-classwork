#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "time.h"
#include "crt_rand.h"  
//定义结构体 
typedef struct{
float value;
int index;
} mess;
int main(int argc, char* argv[]){
	int i,j,N;
	double t1, t2; 
	N = atoi(argv[1]);
	float* a;
 	a = crtarr(N,1); //生成N个0-1的随机数 
	mess* arr = NULL;
	arr = (mess*)malloc(sizeof(mess)*N);
        if(arr==NULL){
                printf("内存分配失败\n");
                exit(-1);
                }
	for(i=0;i<N;i++){
		arr[i].value = a[i];
		arr[i].index = i;
	} //将生成的N个随机数依次赋值给arr数组 
	free(a);
	a = NULL;
	mess max, min, out;
	max = min=arr[0];
	t1 = omp_get_wtime();
	for(i=0;i<N;i++){
		if(max.value<arr[i].value)
			max = arr[i];
	}
	free(arr);
	arr = NULL;
	t2 = omp_get_wtime();
	printf("maxindex=%d,maxvalue=%f,time=%f(s)\n",max.index,max.value,t2-t1);
	return 0;
}
