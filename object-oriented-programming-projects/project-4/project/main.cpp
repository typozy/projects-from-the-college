#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using std::ostream;
using std::ofstream;

#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

using std::vector;
using SpaceRectangle::Rectangle;
using SpaceCircle::Circle;
using SpaceTriangle::Triangle;

#include "polygon.h"
#include "polyline.h"

using SpacePolygon::Polygon;
using SpacePolyline::Polyline;

#include "composedshape.h"

using std::cout;
using std::endl;
using SpaceComposedShape::ComposedShape;

double Rectangle::totalArea = 0.0;
double Rectangle::totalPerimeter = 0.0;
double Circle::totalArea = 0.0;
double Circle::totalPerimeter = 0.0;
double Triangle::totalArea = 0.0;
double Triangle::totalPerimeter = 0.0;

void driver();

int main(){
	driver();
	return 0;
}

void driver(){
	cout << "Now, area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	Rectangle r1(30,40,3.0,4.0),r2(50,60);
	cout << "Area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	Rectangle r3(10,20);
	cout << "Now, area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	cout << "Coordinates of r1 are " << r1.getX() << ',' << r1.getY() << ".\n";
	++r1;
	cout << "After pre incrementation, coordinates of r1 are " << r1.getX() << ',' << r1.getY() << ".\n";
	Rectangle r6 = (r1++);
	cout << "After post incrementation, coordinates of r1 are " << r1.getX() << ',' << r1.getY() << ".\n";
	cout << "After post incrementation, coordinates of r6 are " << r6.getX() << ',' << r6.getY() << ".\n";
	cout << "r2 has a width of " << r2.getWidth() << " and has a height of " << r2.getHeight() <<".\n";
	Rectangle r4 = 15.0 + r2;
	cout << "After double addition, r4 has a width of " << r4.getWidth() << " and has a height of " << r4.getHeight() <<".\n";
	Rectangle r5(300,200);
	cout << "Area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	r5.setWidth(50);
	r5.setHeight(80);
	cout << "Now, area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	//Triangle and Circle objects also work this way.
	cout << ComposedShape(Rectangle(300,75),Rectangle(75,25)) << ComposedShape(Rectangle(200,150),Rectangle(75,25))
		 << ComposedShape(Rectangle(200,150),Circle(35)) << ComposedShape(Rectangle(150,200),Triangle(60))
		 << ComposedShape(Circle(100),Rectangle(30,40)) << ComposedShape(Circle(3000),Circle(1000))
		 << ComposedShape(Circle(200),Triangle(50)) << ComposedShape(Triangle(140),Rectangle(20,30))
		 << ComposedShape(Triangle(120),Circle(30));
	ofstream printfile;
	printfile << ComposedShape(Rectangle(300,75),Rectangle(75,25)) << ComposedShape(Rectangle(200,150),Rectangle(75,25))
		 << ComposedShape(Rectangle(200,150),Circle(35)) << ComposedShape(Rectangle(150,200),Triangle(60))
		 << ComposedShape(Circle(100),Rectangle(30,40)) << ComposedShape(Circle(3000),Circle(1000))
		 << ComposedShape(Circle(200),Triangle(50)) << ComposedShape(Triangle(140),Rectangle(20,30))
		 << ComposedShape(Triangle(120),Circle(30));
	ComposedShape cs;
	cs += Polygon(Rectangle(200,100,50,50)); cs += Polygon(Circle(50,800,100)); cs += Polygon(Triangle(230,1100,50,1215,250,985,250));
	cs += Polygon(Circle(400,500,600)); cs += Polygon(Rectangle(300,900,1600,100)); cs += Polygon(Triangle(460,985,550,1215,950,1445,550));
	cout << cs;
	printfile << cs << cs[1] << cs[5] << cs[7];
	cs.optimalFit(Triangle(120),Circle(30));
	printfile << cs << Polygon(Triangle(170)) << Polyline(Circle(85)) << Polyline(Triangle(150)) << Polyline(Rectangle(300,120));
	vector <Polyline::Point2D> v = {Polyline::Point2D(0,300),Polyline::Point2D(250,150),Polyline::Point2D(250,100),
									Polyline::Point2D(500,0),Polyline::Point2D(250,200),Polyline::Point2D(250,150)};
	Polyline x = Polyline(Circle(150,250,150)) + Polyline(v);
	printfile << x;
	vector <Polyline::Point2D> m = {Polyline::Point2D(0,0),Polyline::Point2D(0,300),
									Polyline::Point2D(50,300),Polyline::Point2D(50,100),Polyline::Point2D(50,200),
									Polyline::Point2D(150,200),Polyline::Point2D(150,100),Polyline::Point2D(150,300),
									Polyline::Point2D(200,300),Polyline::Point2D(200,100),Polyline::Point2D(300,100),
									Polyline::Point2D(300,200),Polyline::Point2D(200,200),Polyline::Point2D(300,200),
									Polyline::Point2D(300,300),Polyline::Point2D(350,300),Polyline::Point2D(350,100),
									Polyline::Point2D(350,300),Polyline::Point2D(450,300),Polyline::Point2D(450,275),
									Polyline::Point2D(450,300),Polyline::Point2D(500,300),Polyline::Point2D(500,100),
									Polyline::Point2D(600,100),Polyline::Point2D(600,200),Polyline::Point2D(500,200),
									Polyline::Point2D(600,200),Polyline::Point2D(600,300),Polyline::Point2D(750,300),
									Polyline::Point2D(750,100),Polyline::Point2D(825,300),Polyline::Point2D(900,100),
									Polyline::Point2D(900,300),Polyline::Point2D(950,300),Polyline::Point2D(950,100),
									Polyline::Point2D(1050,100),Polyline::Point2D(1050,200),Polyline::Point2D(950,200),
									Polyline::Point2D(1050,200),Polyline::Point2D(1050,300),Polyline::Point2D(1100,300),
									Polyline::Point2D(1100,100),Polyline::Point2D(1200,300),Polyline::Point2D(1100,300),
									Polyline::Point2D(1250,300),Polyline::Point2D(1250,100),Polyline::Point2D(1350,100),
									Polyline::Point2D(1350,200),Polyline::Point2D(1250,200),Polyline::Point2D(1350,300),
									Polyline::Point2D(1400,300),Polyline::Point2D(1400,100),Polyline::Point2D(1400,300),
									Polyline::Point2D(1450,300),Polyline::Point2D(1450,100),Polyline::Point2D(1550,300),
									Polyline::Point2D(1450,300),Polyline::Point2D(1625,300),Polyline::Point2D(1600,300),
									Polyline::Point2D(1600,325),Polyline::Point2D(1625,325),Polyline::Point2D(1625,100),
									Polyline::Point2D(1600,100),Polyline::Point2D(1600,300)};
	Polyline hm = Polyline(Rectangle(1700,400)) + Polyline(m);
	printfile << hm;
	Rectangle rtest(-1,-1);	/*	these three wait for integer/double equal to	*/
	Circle ctest(-1);		/*	or greater than 1 cast it to an integer as  	*/
	Triangle ttest(-1);		/*	width/height/radius/edge						*/
	Polygon::Point2D p2dtest(-1,-1);	// 	this point2d object waits for nonnegative double as x/y coordinate
}