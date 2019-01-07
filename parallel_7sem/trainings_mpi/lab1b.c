#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ISIZE 10
#define JSIZE 10


int main(int argc, char **argv) {
	int rank = 0, size = 0;
	double a[ISIZE][JSIZE];
	double b[ISIZE][JSIZE];
	double b_recv[ISIZE][JSIZE];
	int i, j;
//	FILE *ff;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int k = ISIZE/size;
	int k_first = ISIZE - k*(size-1);

	for (i=0; i<ISIZE; i++)
		for (j=0; j<JSIZE; j++)
			b[i][j] = 0;

	if(rank == 0){
		printf("%d %d\n", k, k_first);
		for (i=0; i<ISIZE; i++)
			for (j=0; j<JSIZE; j++)
				a[i][j] = 10*i +j;
//		for(i=0; i < ISIZE; i++){
//			for (j=0; j < JSIZE; j++){
//				printf("%f ",a[i][j]);
//			}
//			printf("\n");
//		}
		printf("\n");
		for(int i = 1; i < size; i++)
			MPI_Send((double*)(a), JSIZE*ISIZE, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
		int i_end = k_first;
		for(int i = 0; i < i_end; i++)
			for(int j = 0; j < JSIZE; j++)
				if(i >= ISIZE - 3 || j < 4)
					b[i][j] = a[i][j];
				else
					b[i][j] += sin(0.00001*a[i+3][j-4]);
		MPI_Status Status;
		for(int i = 1; i < size; i++){
			MPI_Recv((double*)(b_recv), JSIZE*ISIZE, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			for(int i = 0; i < ISIZE; i++)
				for(int j = 0; j < JSIZE; j++)
					b[i][j] += b_recv[i][j];
		}
	}
	if(rank != 0){
		MPI_Status Status;
		MPI_Recv((double*)a, JSIZE*ISIZE , MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
		int i_start = k_first+(rank-1)*k;
		int i_end = k_first+rank*k;
		for(int i = i_start; i < i_end; i++)
			for(int j = 0; j < JSIZE; j++)
				if(i >= ISIZE - 3 || j < 4)
					b[i][j] = a[i][j];
				else
					b[i][j] += sin(0.00001*a[i+3][j-4]);
		MPI_Send((double*)b, JSIZE*ISIZE, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	}

	if(rank == 0){
		for(i=0; i < ISIZE; i++){
			for (j=0; j < JSIZE; j++){
				printf("%f ",b[i][j]);
			}
			printf("\n");
		}
	}
//	ff = fopen("result_1.txt","w");
//	for(i=0; i < ISIZE; i++){
//		for (j=0; j < JSIZE; j++){
//			fprintf(ff,"%f ",a[i][j]);
//		}
//		fprintf(ff,"\n");
//	}
//	fclose(ff);
	MPI_Finalize();
}
