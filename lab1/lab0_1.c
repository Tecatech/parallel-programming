#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    const int count = 10000000;  ///< Number of array elements
    
    int *array = 0;              ///< Target array
    int max = -1;                ///< Maximum element
    
    double start_time, end_time; ///< Starting and ending time points
    
    /* Initialize RNG */
    srand(time(NULL));
    
    /* Determine OpenMP support */
    printf("====================================================\nOpenMP: %d\n", _OPENMP);
    
    /* Generate random array */
    array = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        array[i] = rand();
    }
    
    /* Find maximum element */
    start_time = omp_get_wtime();
    for (int i = 0; i < count; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    end_time = omp_get_wtime();
    
    printf("total maximum: %d || time elapsed: %0.7lf\n====================================================\n", max, end_time - start_time);
    
    return 0;
}