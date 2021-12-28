all: rectangle.o circle.o triangle.o composedshape.o main.o
	g++ -o exe main.o composedshape.o triangle.o circle.o rectangle.o
rectangle.o: rectangle.cpp
	g++ -c -std=c++11 -Wall rectangle.cpp
circle.o: circle.cpp
	g++ -c -std=c++11 -Wall circle.cpp
triangle.o: triangle.cpp
	g++ -c -std=c++11 -Wall triangle.cpp
composedshape.o: composedshape.cpp
	g++ -c -std=c++11 -Wall composedshape.cpp
main.o: main.cpp
	g++ -c -std=c++11 -Wall main.cpp
clean:
	rm *.o exe
clear:
	rm *.o exe
