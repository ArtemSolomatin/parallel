//
// Created by whale on 07.04.18
//
#include <stdio.h>
#include <stdlib.h>

void makeOneStep(double **twoDimensionResult, int i , int j, double tau, double h);

double t0 = 0;
double start = 0;

int main(int argc, char **argv){
    double end = 1;
    double t1 = 1;

    double tau, h = 0;
    tau = strtof(argv[1], NULL);
    h = strtof(argv[2], NULL);

    long nodesNumber =   (long)(((end - start) / h)) + 2;
    long tauNodesNumber = (long)((t1 - t0) / tau)+ 2;
    double **twoDimensionResult = (double**)calloc(tauNodesNumber, sizeof(double *));

    for (int i = 0; i < tauNodesNumber; i++){
        twoDimensionResult[i] = (double*)calloc(nodesNumber, sizeof(double *));
    }
    for (int i = 0; i < nodesNumber; i++){
        twoDimensionResult[0][i] = start + i * h;
    }

    for(int i = 0; i < tauNodesNumber; i++){
        twoDimensionResult[i][0] = t0 + i * h;
    }

    int i,j = 0;
    for (i = 0; i < (tauNodesNumber - 1); i++){
        for (j = 0; j < (nodesNumber - 2); j++){
            makeOneStep(twoDimensionResult, i, j, tau, h);
        }

        twoDimensionResult[i + 1][j + 1] = (t0 + i * tau) * (start + (j + 1) * h) - (twoDimensionResult[i][j + 1] - twoDimensionResult[i][j]) / h;
        twoDimensionResult[i + 1][j + 1] *= tau;
        twoDimensionResult[i + 1][j + 1] += twoDimensionResult[i][j + 1];
    }

    for(i = 0; i < tauNodesNumber; i++){
        for(j = 0; j < nodesNumber; j++){
            printf("%lf  ", twoDimensionResult[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void makeOneStep(double **twoDimensionResult, int i , int j, double tau, double h){
    twoDimensionResult[i + 1][j + 1] = (t0 + i * tau) * (start + (j + 1) * h);
    twoDimensionResult[i + 1][j + 1] -= (twoDimensionResult[i][j + 2] - twoDimensionResult[i][j]) / (2*h);
    twoDimensionResult[i + 1][j + 1] *= tau;
    twoDimensionResult[i + 1][j + 1] += 0.5 * (twoDimensionResult[i][j + 2] + twoDimensionResult[i][j]);
}