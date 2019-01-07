#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 10000
#define JSIZE 10000
#define IN 2
#define JN 3

int main(int argc, char **argv) {
    int rank;
    int size;
    int t;
    
    double** b = (double**) malloc(ISIZE * sizeof(double*));
    double** a = (double**) malloc(ISIZE * sizeof(double*));
    for (t=0; t < ISIZE; t++) {
        a[t] = (double*) malloc(JSIZE * sizeof(double));
    }

    for (t=0; t < ISIZE; t++) {
        b[t] = (double*) malloc(JSIZE * sizeof(double));
    }

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Status status;

    int i, j;

    double t_start = MPI_Wtime();
    

    int num_diag = (ISIZE - IN) * JN + (JSIZE - JN) * IN - IN * JN;
    int c_diag, iter_i, iter_j;
    
    for (c_diag = rank; c_diag < num_diag; c_diag += size) {
    	if (c_diag <= (ISIZE - IN) * JN) {
    		iter_i = IN + c_diag % (ISIZE - IN);
    		iter_j = JN + c_diag / (ISIZE - IN);
    	} else {
    		iter_i = IN;
    		iter_j = 2 * JN + c_diag - (ISIZE - IN) * JN;
    	}
    	a[iter_i - IN][iter_j - JN] = 10 * (iter_i - IN) + iter_j - JN;
    	while(iter_i < ISIZE && iter_j < JSIZE) {
    		a[iter_i][iter_j] = sin(0.00001 * a[iter_i - IN][iter_j - JN]);
    		iter_i += IN;
    		iter_j += JN;
    	}
    }


    if (rank == 0) {
        double t_end = MPI_Wtime();
        printf("%d\t%lf\n", size, t_end - t_start);
    }
    for (i=0 ; i < ISIZE; i++) {
 	   MPI_Reduce(a[i], b[i], JSIZE, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	}

    MPI_Finalize();

    // FILE *ff;
    // ff = fopen("result.parallel.txt", "w");
    // for (i = 0; i < ISIZE; i++) {
    //     for (j = 0; j < JSIZE; j++) {
    //         fprintf(ff, "%f ", b[i][j]);
    //     }
    //     fprintf(ff, "\n");
    // }
    // fclose(ff);

    for (t=0; t < ISIZE; t++) {
        free(a[t]);
    }
    for (t=0; t < ISIZE; t++) {
        free(b[t]);
    }
    free(a);
    free(b);


    return 0;
}
