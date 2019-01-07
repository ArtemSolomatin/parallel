#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ISIZE 10
#define JSIZE 10

int main(int argc, char **argv)
{
double a[ISIZE][JSIZE];
int i, j;
for (i=0; i<ISIZE; i++){
for (j=0; j<JSIZE; j++){
a[i][j] = 10*i +j;
}
}
for (i=0; i<ISIZE-3; i++){
for (j = 4; j < JSIZE; j++){
a[i][j] =
sin(0.00001*a[i+3][j-4]);
}
}
for(i=0; i < ISIZE; i++){
for (j=0; j < JSIZE; j++){
printf("%f ",a[i][j]);
}
printf("\n");
}
}
