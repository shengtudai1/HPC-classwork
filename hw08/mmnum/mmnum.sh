#! /bin/bash

a="1 2 4 8 10 20"
for i in ${a[*]}
do
mpirun -np $i max_min_num 1000000000
done
