Lw2 : main.o rb.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o Lw2 main.o rb.o
main.o : main.cpp rb.h
	g++ -std=c++14 -c main.cpp
rb.o : rb.cpp rb.h
	g++ -std=c++14 -c rb.cpp
clear :
	rm *.o Lw2
