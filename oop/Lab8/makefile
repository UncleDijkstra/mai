Lw6 : main.o Triangle.o Rectangle.o Foursquare.o TAllocationBlock.o
	g++ main.o Triangle.o Rectangle.o Foursquare.o TAllocationBlock.o -o Lw6
main.o : main.cpp Vector.h Foursquare.h Rectangle.h Triangle.h Figure.h
	g++ -std=c++11 -c main.cpp
Triangle.o : Triangle.cpp Triangle.h Figure.h
	g++ -std=c++11 -c Triangle.cpp
Rectangle.o : Rectangle.cpp Rectangle.h Figure.h
	g++ -std=c++11 -c Rectangle.cpp
Foursquare.o : Foursquare.cpp Foursquare.h Figure.h
	g++ -std=c++11 -c Foursquare.cpp
TAllocationBlock.o : TAllocationBlock.cpp TAllocationBlock.h
	g++ -std=c++11 -c TAllocationBlock.cpp
clear :
	rm *.o Lw6