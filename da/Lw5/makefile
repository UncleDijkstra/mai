Lw5 : main.o SuffTree.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o Lw5 main.o SuffTree.o
main.o : main.cpp SuffTree.h
	g++ -std=c++11 -Wall -c -g main.cpp
SuffTree.o : SuffTree.cpp SuffTree.h
	g++ -std=c++11 -Wall -c -g SuffTree.cpp
clear :
	rm *.o Lw5