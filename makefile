all:
	clear
	#g++ -std=c++11 *.cpp QT/Crack/Functions.cpp -Wall  -lcrypt  -fopenmp -I/usr/lib/openmpi/include -I/usr/lib/openmpi/include/openmpi -pthread -L/usr//lib -L/usr/lib/openmpi/lib -lmpi_cxx -lmpi -ldl -lhwloc -o Prog
	#cd QT/build-Crack-Desktop-Debug/ && $(MAKE)
	#QT/build-Crack-Desktop-Debug/Crack
	mpic++ -o Prog main.cpp
	mpirun -np 3 Prog


clean:
	rm -rf *.o Prog Crack
	cd QT/build-Crack-Desktop-Debug/ && $(MAKE) clean
