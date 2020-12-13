#include <stdio.h>  
#include <time.h>
long num_steps;  
double step;   
int main(){
    printf("输入num_steps:");
    scanf("%d",&num_steps);
    clock_t start,end;  
    int i;  
    double x,pi,sum = 0.0;  
    start = clock();  
    step = 1.0/(double)num_steps;  
    for(i=1;i<=num_steps;i++){  
        x = (i-0.5)*step;   
        sum += 4.0/(1.0+x*x);  
    }  
    pi = step * sum;  
    end = clock();  
    printf("pi=%f\tclock=%.3lf\n",pi,(double)(end-start)/CLOCKS_PER_SEC);  
    return 0;  
}  
