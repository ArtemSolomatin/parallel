#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void count_step(double ** res, int i , int j, double tau, double h, double t0, double a){
	res[i + 1][j + 1] = (t0 + i * tau) * (a + (j + 1) * h);
	res[i + 1][j + 1] +=  0.5 * tau * (res[i][j + 2]  - 2 * res[i][j + 1] + res[i][j]) / (h * h);
	res[i + 1][j + 1] -= (res[i][j + 2] - res[i][j]) / (2*h);
	res[i + 1][j + 1] *= tau;
	res[i + 1][j + 1] += res[i][j + 1];
}

int main(int argc, char const *argv[]){
	double a, b, T_1, t0;
	a = 0;
	b = 1;
	T_1 = 1;
	t0 = 0;
	char *endptr = NULL;
	double tau, h = 0;
	tau = strtof(argv[1], &endptr);
    h = strtof(argv[2], &endptr);

    long num_h =   (long)(((b - a) / h)) + 2;
    long num_tau = (long)((T_1 - t0) / tau)+ 2;
    double **res;
	res = (double**)calloc(num_tau, sizeof(double *));

    for (int i = 0; i < num_tau; i++){
    	res[i] = (double*)calloc(num_h, sizeof(double *));
    }
    for (int i = 0; i < num_h; i++){
    	res[0][i] = a + i * h;
    }

    for(int i = 0; i < num_tau; i++){
    	res[i][0] = t0 + i * h;
    }

	int i,j = 0;
    for (i = 0; i < (num_tau - 1); i++){
    	for (j = 0; j < (num_h - 2); j++){
    			count_step(res, i, j, tau, h, t0, a);
    	}

    	res[i + 1][j + 1] = (t0 + i * tau) * (a + (j + 1) * h) - (res[i][j + 1] - res[i][j]) / h;
    	res[i + 1][j + 1] *= tau;
    	res[i + 1][j + 1] += res[i][j + 1];
    }

    for (int i = 0; i < num_tau; i++){
    	for (int j = 0; j < num_h; j++){
    		printf("%lf ", res[i][j]);
    	}
    	printf("\n");
    }

	return 0;
}
