Lw3 : main.o Triangle.o Rectangle.o Foursquare.o Vector.o
	g++ main.o Triangle.o Rectangle.o Foursquare.o Vector.o -o Lw3 -std=c++11
main.o : main.cpp Vector.h Foursquare.h Rectangle.h Triangle.h Figure.h
	g++ -std=c++11 -c main.cpp
Triangle.o : Triangle.cpp Triangle.h Figure.h
	g++ -std=c++11 -c Triangle.cpp
Rectangle.o : Rectangle.cpp Rectangle.h Figure.h
	g++ -std=c++11 -c Rectangle.cpp
Foursquare.o : Foursquare.cpp Foursquare.h Figure.h
	g++ -std=c++11 -c Foursquare.cpp
Vector.o : Vector.cpp Vector.h Foursquare.h Rectangle.h Triangle.h Figure.h
	g++ -std=c++11 -c Vector.cpp
clear :
	rm *.o Lw3