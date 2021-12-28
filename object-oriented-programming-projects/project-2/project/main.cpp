#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "composedshape.h"

void driver();

int main(){
	driver();	/* just work this function to see the svg files with manuel parameters 
					(that i wrote) which are inside driver function */
	return 0;
}

void driver(){
	ofstream sOut;
	ComposedShape composed(Rectangle(300,75),Rectangle(75,25));
	composed.draw(sOut);
	composed.optimalFit(Rectangle(200,150),Circle(35));
	composed.draw(sOut);
	composed.optimalFit(Rectangle(150,200),Triangle(60));
	composed.draw(sOut);
	composed.optimalFit(Circle(100),Rectangle(30,40));
	composed.draw(sOut);
	composed.optimalFit(Circle(151),Circle(50));
	composed.draw(sOut);
	composed.optimalFit(Circle(120),Triangle(75));
	composed.draw(sOut);
	composed.optimalFit(Triangle(140),Rectangle(20,30));
	composed.draw(sOut);
	composed.optimalFit(Triangle(120),Circle(30));
	composed.draw(sOut);
	composed.optimalFit(Triangle(151),Triangle(50));
	composed.draw(sOut);
}