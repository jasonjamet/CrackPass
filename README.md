# CrackPass
A "C" program optimized (OpenMP, MPI) to bruteforce a password.

###Usage :
```
Usage : mpirun -np "number of core to use" Crackpass "parallelization method" "user name" "bruteForce method"
```
number of core to use : integer 1 to X

parallelization method : openMP or MPI

user name: name of the user (need to be in the shadow file)

bruteForce method: 0 for dictionary, 1 for classical method


Compilation:
```
make
```
Clean the project
```
make clean
```
###Exemples :
Use only openMP to crack jason's user password with dictionary bruteforce
```
mpirun -np 1  CrackPass openmp jason 0
```
Use only MPI with openMP to crack jason's user password with dictionary bruteforce
```
mpirun -np 4  CrackPass MPI jason 0
```
