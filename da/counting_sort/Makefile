Lw1 : main.o vector.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o Lw1 main.o vector.o
main.o : main.cpp vector.h
	g++ -std=c++14 -c main.cpp
vector.o : vector.cpp vector.h struct.h
	g++ -std=c++14 -c vector.cpp
clear :
	rm *.o Lw1
