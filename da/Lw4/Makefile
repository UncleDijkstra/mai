Lw4 : main.o bm.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -O2 -lm -o Lw4 main.o bm.o
main.o : main.cpp bm.h
	g++ -Wall -O2 -c -g main.cpp
bm.o : bm.cpp bm.h
	g++ -Wall -O2 -c -g bm.cpp
clear :
	rm *.o Lw4