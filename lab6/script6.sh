#!/bin/bash

thread_amounts=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)

for thread_amount in ${thread_amounts[*]}
do
    echo "======================="
    printf "Thread amount: "
    printf "%d\n" $thread_amount
    
    mpirun -np $thread_amount ./lab6
    echo "======================="
done