#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ret = -1;                          ///< Return value of MPI call
    int size = -1;                         ///< Total number of processors
    int rank = -1;                         ///< Processor rank
    
    const int count = 10000000;            ///< Number of array elements
    const int random_seed = atoi(argv[1]); ///< RNG seed (Random Number Generator)
    
    int *array = 0;                        ///< Target array
    int lmax = -1;                         ///< Local maximum
    int max = -1;                          ///< Maximum element
    
    double start_time, end_time;           ///< Starting and ending time points
    
    /* Initialize MPI */
    ret = MPI_Init(&argc, &argv);
    if (!rank) {
        printf("MPI_Init return value: %d\n", ret);
        exit(0);
    }
    
    /* Determine processor count */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    /* Determine rank count */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    /* Allocate array */
    array = (int *)malloc(count * sizeof(int));
    
    /* Generate array from master thread */
    if (!rank) {
        /* Initialize RNG */
        srand(random_seed);
        
        /* Generate random array */
        for (int i = 0; i < count; i++) {
            array[i] = rand();
        }
    }
    
    /* Send array to all other processors */
    MPI_Bcast(array, count, MPI_INTEGER, 0, MPI_COMM_WORLD);
    
    const int wstart = rank * count / size;
    const int wend = (rank + 1) * count / size;
    
    /* Find maximum element */
    start_time = MPI_Wtime();
    for (int i = wstart; i < wend; i++) {
        if (array[i] > lmax) {
            lmax = array[i];
        }
    }
    end_time = MPI_Wtime();
    
    printf("local maximum: %d || time elapsed: %0.7lf\n", lmax, end_time - start_time);
    
    MPI_Reduce(&lmax, &max, 1, MPI_INTEGER, MPI_MAX, 0, MPI_COMM_WORLD);
    
    ret = MPI_Finalize();
    if (!rank) {
        printf("total maximum: %d\n", lmax);
    }
    
    return 0;
}