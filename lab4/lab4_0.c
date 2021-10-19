#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv) {
    double start_time, end_time, tick;
    
    omp_sched_t type;
    int chunk;
    
    printf("=======================================\nOpenMP: %d\n=======================================\n", _OPENMP);
    
    printf("=======================================\nAvailable processors amount: %d\n", omp_get_num_procs());
    printf("Available threads amount: %d\n=======================================\n", omp_get_max_threads());
    
    printf("=======================================\nOMP_DYNAMIC value: %d\n=======================================\n", omp_get_dynamic());
    
    tick = omp_get_wtick();
    printf("=======================================\nTimer resolution: %lf seconds\n=======================================\n", tick);
    
    printf("=======================================\nOMP_NESTED value: %d\n", omp_get_nested());
    printf("OMP_MAX_ACTIVE_LEVELS value: %d\n=======================================\n", omp_get_max_active_levels());
    
    omp_get_schedule(&type, &chunk);
    printf("=======================================\nOMP_SCHEDULE value: ");
    
    switch (type) {
    case omp_sched_static:
        printf("static\n=======================================\n");
        break;
    case omp_sched_dynamic:
        printf("dynamic\n=======================================\n");
        break;
    case omp_sched_guided:
        printf("guided\n=======================================\n");
        break;
    case omp_sched_auto:
        printf("auto\n=======================================\n");
        break;
    default:
        printf("specific\n=======================================\n");
        break;
    }
    
    return 0;
}