prog : main.o training.o classifier.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o prog main.o training.o classifier.o
main.o : main.cpp tags.hpp training.hpp classifier.hpp
	g++ -Wall -O2 -c -g -std=c++11 main.cpp
training.o : training.cpp tags.hpp
	g++ -Wall -O2 -c -g -std=c++11 training.cpp
classifier.o : classifier.cpp tags.hpp
	g++ -Wall -O2 -c -g -std=c++11 classifier.cpp
clear :
	rm *.o prog