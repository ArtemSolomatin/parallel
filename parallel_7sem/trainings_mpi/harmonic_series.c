#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <time.h> 

double f(float n){ 
    return 1 / n; 
} 

double sum(int N){ 
    double SUM = 0; 
    int n; 
    #pragma omp parallel for 
    for(n = 1; n <= N; n++){ 
        #pragma omp atomic 
        SUM += f(n);  
    } 
    return SUM; 
} 

int main(int argc, char *argv[]){ 
    unsigned long long int N = argc > 1 ? atol(argv[1]) : 100000; 
    printf("sum %lld = ", N); 
    clock_t time = clock(); 
    double SUM; 
    SUM = sum(N); 
    printf("%lf\n", SUM); 
    time = clock() - time; 
    printf("time: %lf\n", (double)time / CLOCKS_PER_SEC); 
    return 0; 
}
