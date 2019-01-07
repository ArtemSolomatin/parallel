#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 10000
#define JSIZE 10000
#define IN 1
#define JN 1

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

    for (i = rank + IN; i < ISIZE; i += size) {
        for (j = JN; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
        for (j = 0; j < JN; j++) {
            a[i - IN][j] = 10 * (i - IN) + j;
        }
    }

    double t_start = MPI_Wtime();
    
    for (i = rank; i < ISIZE - IN; i += size) {
        for (j = 1; j < JSIZE; j++) {
            a[i][j] = sin(0.00001 * a[i + IN][j - JN]);
        }
    }

    if (rank == 0) {
        double t_end = MPI_Wtime();
        printf("%d\t%lf\n", size, t_end - t_start);
    }

    for (i = rank ; i < ISIZE; i += size) {
 	   MPI_Reduce(a[i], b[i], JSIZE, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	}

    MPI_Finalize();

    //for (i = 0; i < ISIZE; i++) {
      //  for (j = 0; j < JSIZE; j++) {
        //    printf("%f ", b[i][j]);
        //}
        //printf("\n");
    //}
        
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
