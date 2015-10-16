all:
	clear
	mpic++ -o CrackPass main.cpp Functions.cpp cpu_timer.cpp Functions.h -std=c++11 -Wall -lcrypt -fopenmp
	mpirun -np 3 CrackPass jason BF


clean:
	rm -rf *.o CrackPass
	#cd QT/build-Crack-Desktop-Debug/ && $(MAKE) clean
