#! /bin/bash
mpicc -fopenmp pi_mpi_omp.c -o pi_mpi_omp
a="2 4 6 8"
for i in ${a[*]}
do
export OMP_NUM_THREADS=2
echo -e "proc=$i threads=2"
mpirun --bind-to core -np $i ./pi_mpi_omp
done
