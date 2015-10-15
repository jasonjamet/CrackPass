all:
	clear
	#g++ -std=c++11 *.cpp QT/Crack/Functions.cpp -Wall  -lcrypt  -fopenmp -I/usr/lib/openmpi/include -I/usr/lib/openmpi/include/openmpi -pthread -L/usr//lib -L/usr/lib/openmpi/lib -lmpi_cxx -lmpi -ldl -lhwloc -o Prog
	#cd QT/build-Crack-Desktop-Debug/ && $(MAKE)
	#QT/build-Crack-Desktop-Debug/Crack
	mpic++ -o CrackPass main.cpp Functions.cpp Functions.h -std=c++11 -Wall -lcrypt -fopenmp
	mpirun -np 3 CrackPass jason 1


clean:
	rm -rf *.o CrackPass
	#cd QT/build-Crack-Desktop-Debug/ && $(MAKE) clean
