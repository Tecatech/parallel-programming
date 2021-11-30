#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ret = -1;                          ///< Return value of MPI call
    int size = -1;                         ///< Total number of processors to use
    int rank = -1;                         ///< The processor rank
    
    const int count = 10000000;            ///< Number of array elements
    const int random_seed = atoi(argv[1]); ///< RNG seed (random number generator)
    
    int *array = 0;                        ///< The array we need to find the max in
    int lmax = -1;                         ///< The local maximum
    int max = -1;                          ///< The maximal element
    
    double start_time, end_time;           ///< The starting and the ending timepoints
    
    /* Initialize the MPI */
    ret = MPI_Init(&argc, &argv);
    if (!rank) {
        printf("MPI_Init return value: %d\n", ret);
        exit(0);
    }
    
    /* Determine the processor count */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    /* Determine the rank count */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    /* Allocate the array */
    array = (int *)malloc(count * sizeof(int));
    
    /* Generate the array from master thread */
    if (!rank) {
        /* Initialize the RNG */
        srand(random_seed);
        
        /* Generate the random array */
        for (int i = 0; i < count; i++) {
            array[i] = rand();
        }
    }
    
    /* Send the array to all other processors */
    MPI_Bcast(array, count, MPI_INTEGER, 0, MPI_COMM_WORLD);
    
    const int wstart = rank * count / size;
    const int wend = (rank + 1) * count / size;
    
    /* Find the maximal element */
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