a=(1 2 4 8 10 20 40)
echo -e "np\tpi\ttime\t" > A
for i in ${a[*]}
do
mpirun -np $i mpi_pi_1 >>A

done
echo -e "speed_ratio\n1" >a 
cut -f 3 A >A1	
awk 'NR==2{tmp=$1}NR>2{print tmp/$1 }' A1 >>a
paste A a
rm ./A1
rm ./a
##cat A
