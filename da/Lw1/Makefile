Lw1 : main.o vector.o mystring.o sort.o
	gcc -pedantic -Wall -std=c99 -Werror -Wno-sign-compare -lm -o Lw1 main.o vector.o mystring.o sort.o
main.o : main.c vector.h struct.h mystring.h sort.h
	gcc -c main.c
# quick.o : quick.c vector.h struct.h mystring.h sort.h
# 	gcc -c quick.c
vector.o : vector.c vector.h mystring.h struct.h
	gcc -c vector.c
mystring.o : mystring.h mystring.c
	gcc -c mystring.c
sort.o : sort.h sort.c mystring.h struct.h
	gcc -c sort.c
clear :
	rm *.o Lw1