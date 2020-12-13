#!/bin/bash
a=(1 2 4 6 8 10 20 40)
echo -e "NUM_THREADS\tTIME\tpi\n"
for i in ${a[*]}
do
export OMP_NUM_THREADS=$i
./pi_for
done
