#!/bin/bash
a=(1 2 4 6 8 10 20 40)
echo -e "NUM_THREADS\tpi\tpi_pad\tpi_atom\tpi_crit\tpi_for">a
for i in ${a[*]}
do
export OMP_NUM_THREADS=$i
./pi_1>>a
./pi_2>>a
./pi_atom>>a
./pi_crit>>a
./pi_for>>a
done
