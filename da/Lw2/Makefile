Lw2 : main.o btree.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o Lw2 main.o btree.o
main.o : main.cpp btree.h
	g++ -Wall -c main.cpp
btree.o : btree.cpp btree.h
	g++ -Wall -c btree.cpp
clear :
	rm *.o Lw2