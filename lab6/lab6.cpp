#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *array, int count, int gap, int i) {
    for (int j = gap + i; j < count; j += gap) {
        while (j > i && array[j - gap] > array[j]) {
            int temp = array[j];
            array[j] = array[j - gap];
            array[j - gap] = temp;
            j -= gap;
        }
    }
}

void shellSort(int *array, int count) {
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = 0; i < gap; i++) {
            insertionSort(array, count, gap, i);
        }
    }
}

int main(int argc, char **argv) {
    int ret = -1;
    int size = -1;
    int rank = -1;
    
    const int count = 100000;
    const int amount = 100;
    const int random_seed = 9202;
    
    int *array = 0;
    int *rArray = 0;
    int *subArray = 0;
    
    int array_size = -1;
    int array_width = -1;
    
    double start_time, end_time;
    
    MPI_Status status;
    
    ret = MPI_Init(&argc, &argv);
    if (!rank) {
        printf("MPI_Init return value: %d\n", ret);
        exit(0);
    }
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    array = (int *)malloc(count * sizeof(int));
    
    if (!rank) {
        srand(random_seed);
        
        for (int i = 0; i < count; i++) {
            array[i] = rand();
        }
    }
    
    array_width = size > 1 ? count / (size - 1) : count;
    
    if (!rank) {
        start_time = MPI_Wtime();
        
        for (int i = 1; i < size; i++) {
            MPI_Send(array + array_width * (i - 1), array_width, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
        array_size = count - array_width * (size - 1);
        subArray = (int *)malloc(array_size * sizeof(int));
        
        for (int i = array_width * (size - 1); i < count; i++) {
            subArray[i - array_width * (size - 1)] = array[i];
        }
        
        shellSort(subArray, array_size);
        
        rArray = (int *)malloc(count * sizeof(int));
        
        for (int i = 0; i < array_size; i++) {
            rArray[i] = subArray[i];
        }
        
        for (int i = 1; i < size; i++) {
            MPI_Recv(rArray + array_width * (i - 1) + array_size, array_width, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        }
        
        shellSort(rArray, count);
        end_time = MPI_Wtime();
        
        printf("Time elapsed: %0.7lf\n", end_time - start_time);
    }
    else {
        subArray = (int *)malloc(array_width * sizeof(int));
        
        MPI_Recv(subArray, array_width, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        shellSort(subArray, array_width);
        MPI_Send(subArray, array_width, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    
    ret = MPI_Finalize();
    return 0;
}