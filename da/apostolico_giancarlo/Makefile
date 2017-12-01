Lw4 : main.o bm.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o Lw4 main.o bm.o
main.o : main.cpp bm.h
	g++ -std=c++14 -c main.cpp
bm.o : bm.cpp bm.h
	g++ -std=c++14 -c bm.cpp
clear :
	rm *.o Lw4
