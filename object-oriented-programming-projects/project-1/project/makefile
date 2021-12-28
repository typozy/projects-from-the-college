all: source1.o main.o
	g++ -o exe main.o source1.o

source1.o: source1.cpp
	g++ -c -std=c++11 -Wall source1.cpp

main.o: main.cpp
	g++ -c -std=c++11 -Wall main.cpp

clean:
	rm *.o exe

clear:
	rm *.o exe
