#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const int count = 10000000;            ///< Number of array elements
    const int threads = atoi(argv[1]);     ///< Number of parallel threads to use
    const int random_seed = atoi(argv[2]); ///< RNG seed (random number generator)
    
    int *array = 0;                        ///< The array we need to find the max in
    int max = -1;                          ///< The maximal element
    
    int iterations;                        ///< Number of iterations to perform
    
    /* Initialize the RNG */
    srand(random_seed);
    
    /* Determine the OpenMP support */
    printf("===========================================================\nOpenMP: %d\n", _OPENMP);
    
    /* Generate the random array */
    array = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        array[i] = rand();
    }
    
    /* Find the maximal element */
    #pragma omp parallel num_threads(threads) private(iterations) shared(array, count) reduction(max: max) default(none)
    {
        iterations = 0;
        #pragma omp for
        for (int i = 0; i < count; i++) {
            if (array[i] > max) {
                max = array[i];
            }
            iterations++;
        }
        printf("local maximum: %d || iterations performed: %d\n", max, iterations);
    }
    
    printf("total maximum: %d\n===========================================================\n", max);
    
    return 0;
}