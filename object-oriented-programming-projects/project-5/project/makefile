all: shape.o rectangle.o circle.o triangle.o polygon.o polygondyn.o polygonvect.o composedshape.o main.o
	g++ -o exe shape.o rectangle.o circle.o triangle.o polygon.o polygondyn.o polygonvect.o composedshape.o main.o
shape.o: shape.cpp
	g++ -c -std=c++11 -Wall shape.cpp
rectangle.o: rectangle.cpp
	g++ -c -std=c++11 -Wall rectangle.cpp
circle.o: circle.cpp
	g++ -c -std=c++11 -Wall circle.cpp
triangle.o: triangle.cpp
	g++ -c -std=c++11 -Wall triangle.cpp
polygon.o: polygon.cpp
	g++ -c -std=c++11 -Wall polygon.cpp
polygondyn.o: polygondyn.cpp
	g++ -c -std=c++11 -Wall polygondyn.cpp
polygonvect.o: polygonvect.cpp
	g++ -c -std=c++11 -Wall polygonvect.cpp
composedshape.o: composedshape.cpp
	g++ -c -std=c++11 -Wall composedshape.cpp
main.o: main.cpp
	g++ -c -std=c++11 -Wall main.cpp
clear:
	rm *.o exe *.svg
clean:
	rm *.o exe *.svg
