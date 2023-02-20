#!/bin/bash

thread_amounts=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)
random_seeds=(803018 116209 147462 265244 235363 503444 311586 973302 883964 660397)

for thread_amount in ${thread_amounts[*]}
do
    echo "++++++++++++++++++++++++++++++++++++++++++++++++++++"
    printf "Thread amount: "
    printf "%d\n" $thread_amount
    
    for random_seed in ${random_seeds[*]}
    do
        echo "++++++++++++++++++++++++++++++++++++++++++++++++++++"
        printf "Random seed: "
        printf "%d\n" $random_seed
        
        echo "===================================================="
        mpirun -np $thread_amount ./lab5 $random_seed
        echo "===================================================="
    done
done
