#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <omp.h>
double timer(){
	struct timeval ts;
	gettimeofday(&ts, NULL);
	return (double)ts.tv_sec + 1e-6 * (double)ts.tv_usec;
}

int main(int argc, char const *argv[]){
    int i, n, *a;
	double t;
	if (argc < 2) {
		printf("too few arguments");
		return 1;
	}
	n = atoi(argv[1]);
    i = 0;
    srand(time(NULL));
    t = timer();
    omp_set_num_threads(n); 
	#pragma omp parallel
	{
        int id =  omp_get_thread_num();
        while(i < n){
            if(i == id){
                printf("Hello world, I'm id = %d\n", i);
                i++;
                break;
            }
        }
	}

	t = timer() - t;
	//printf("time: %d\n", t);
    return 0;
}
