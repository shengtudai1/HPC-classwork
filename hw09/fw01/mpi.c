#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"
//输出矩阵
void print_arr(int** arr, int N){
        int row,col;
	printf("[\n");
        for(row=0;row<5&&row<N;row++){
		printf("[");
                for(col=0;col<5&&col<N;col++){
                        printf("%d, ",arr[row][col]);
                }
                printf("……]\n");
        }
        printf("……\n]\n\n");
}

int main(int argc, char* argv[]){
       // srand((unsigned) time(NULL));
        int N,row,col,i,k,temp,r,source;
        int **arr_1, **arr_2,**result = NULL;
        double start, end;
	//printf("输入矩阵维度");

        //scanf("%d",&N);
        N = 20000;
	MPI_Status status;
        start = MPI_Wtime();
	MPI_Init(&argc, &argv);
        int world_rank, world_size;
        MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
        MPI_Comm_size(MPI_COMM_WORLD,&world_size);

        arr_1 = (int**)malloc(sizeof(int*)*(N/world_size));
        arr_2 = (int**)malloc(sizeof(int*)*N);
        result = (int**)malloc(sizeof(int*)*(N/world_size));
        if(arr_1==NULL||arr_2==NULL||result==NULL){
                        printf("内存分配失败");
                        exit(-1);
                }
        for(k=0;k<N/world_size;k++){
                arr_1[k] = (int*)malloc(sizeof(int)*N);
                result[k] = (int*)malloc(sizeof(int)*N);
                if(arr_1[k]==NULL||result[k]==NULL){
                        printf("内存分配失败");
                        exit(-1);
                }
        }
	for(k=0;k<N;k++){
                arr_2[k] = (int*)malloc(sizeof(int)*N);
		if(arr_2[k]==NULL){
                        printf("内存分配失败");
                        exit(-1);
			}
	}
	
	int step = N/world_size;
        for(row=0;row<N;row++){
                for(col=0;col<N;col++){
                        arr_2[row][col] = (2*row+7*col)%100;
			if(row>=step)
				continue;
			arr_1[row][col] = (3*(world_rank*step+row)+2*col)%100;
                }
        }

	if(world_rank==0){
		 print_arr(arr_1,N);
       		 print_arr(arr_2,N);	
	}
        for(row=0;row<step;row++){
		printf("%d:%d/%d\n",world_rank,row,step);
                for(k=0;k<N;k++){
                        r = arr_1[row][k];
                        for(col=0;col<N;col++){
                                result[row][col] += r * arr_2[k][col];
                        }
                }
        }
	for(i=0;i<step;i++)
		MPI_Gather(result[i],N,MPI_INT,arr_2[world_rank*step+i],N,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(world_rank==0){
        print_arr(arr_2,N);
        end = MPI_Wtime();
        printf("clock=%.3f",(end-start));}
        free(arr_1);
        free(arr_2);
        free(result);
        arr_1 = NULL;
        arr_2 = NULL;
        result  = NULL;
        return MPI_Finalize();
}


