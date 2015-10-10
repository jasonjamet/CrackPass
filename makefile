all:
	#g++ -std=c++11 *.cpp -lcrypt -O3 -fopenmp -I/usr/lib/openmpi/include -I/usr/lib/openmpi/include/openmpi -pthread -L/usr//lib -L/usr/lib/openmpi/lib -lmpi_cxx -lmpi -ldl -lhwloc -o Prog && ./Prog &&
	cd QT/build-Crack-Desktop-Debug/ && $(MAKE)
clean:
	rm -rf *.o Prog Crack
	cd QT/build-Crack-Desktop-Debug/ && $(MAKE) clean
