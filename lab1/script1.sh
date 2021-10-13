#!/bin/bash

threads_amounts=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)
random_seeds=(803018 116209 147462 265244 235363 503444 311586 973302 883964 660397)

for threads_amount in ${threads_amounts[*]}
do
    echo "++++++++++++++++++++++++++++++++++++++++++++++++++++"
    printf "Threads amount: "
    printf "%d\n" $threads_amount
    
    for random_seed in ${random_seeds[*]}
    do
        echo "++++++++++++++++++++++++++++++++++++++++++++++++++++"
        printf "Random seed: "
        printf "%d\n" $random_seed
        
        ./lab1_1 $threads_amount $random_seed
    done
done
