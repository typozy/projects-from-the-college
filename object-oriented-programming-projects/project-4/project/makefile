all: rectangle.o circle.o triangle.o polygon.o polyline.o composedshape.o main.o
	g++ -o exe rectangle.o circle.o triangle.o polygon.o polyline.o composedshape.o main.o
rectangle.o: rectangle.cpp
	g++ -c -std=c++11 -Wall rectangle.cpp
circle.o: circle.cpp
	g++ -c -std=c++11 -Wall circle.cpp
triangle.o: triangle.cpp
	g++ -c -std=c++11 -Wall triangle.cpp
polygon.o: polygon.cpp
	g++ -c -std=c++11 -Wall polygon.cpp
polyline.o: polyline.cpp
	g++ -c -std=c++11 -Wall polyline.cpp
composedshape.o: composedshape.cpp
	g++ -c -std=c++11 -Wall composedshape.cpp
main.o: main.cpp
	g++ -c -std=c++11 -Wall main.cpp
clear:
	rm *.o exe *.svg
clean:
	rm *.o exe *.svg
