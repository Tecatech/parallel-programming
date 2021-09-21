#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    const int count = 10000000; ///< Number of array elements
    
    int *array = 0;             ///< The array we need to find the max in
    int max = -1;               ///< The maximal element
    
    int iterations = 0;         ///< Number of iterations to perform
    
    /* Initialize the RNG */
    srand(time(NULL));
    
    /* Determine the OpenMP support */
    printf("===========================================================\nOpenMP: %d\n", _OPENMP);
    
    /* Generate the random array */
    array = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        array[i] = rand();
    }
    
    /* Find the maximal element */
    for (int i = 0; i < count; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        iterations++;
    }
    
    printf("total maximum: %d || iterations performed: %d\n===========================================================\n", max, iterations);
    
    return 0;
}