#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

double func(double x);

int main(int argc, char **argv){
    double a = 0, b = 1, res = 0;
    double x = a;
    int i;

    double step = strtof(argv[1], NULL);
    int nodesNum = (int) ((int)(b - a) / step);
    int threadNum = (int) strtol(argv[2], NULL, 10);

    omp_set_num_threads(threadNum);
#pragma omp parallel for firstprivate(step, a, x) reduction(+:res)

    for(i = 0; i < nodesNum; i++){
//        printf("i=%d step=%lf %lf\n", i, step, x);
        x = a + step / 2 + i * step;
        res += func(x) * step;
    }

    printf("%lf\n", res);
}

double func(double x){
    return x*x;
}