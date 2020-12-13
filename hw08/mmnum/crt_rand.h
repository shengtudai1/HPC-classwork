#include <stdio.h>
#include <stdlib.h>
float* crtarr(int N, int seed){
	int i;
	float* a =(float*)malloc(sizeof(float)*N);
	srand(seed);
	for(i=0;i<N;i++){
                a[i] = 1.0*rand()/(double)(RAND_MAX);
        }
	return a;
}
