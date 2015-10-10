all:
	clear && g++ -std=c++11 *.cpp -lcrypt -O3 -o Prog && ./Prog