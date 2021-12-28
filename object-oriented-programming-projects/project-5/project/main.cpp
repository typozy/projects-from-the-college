#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

#include "myerrors.h"

using std::ostream;
using std::ofstream;
using std::vector;

#include "shape.h"

using SpaceShape::Shape;

#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "polygon.h"

using SpaceRectangle::Rectangle;
using SpaceCircle::Circle;
using SpaceTriangle::Triangle;
using SpacePolygon::Polygon;

#include "polygondyn.h"
#include "polygonvect.h"

using SpacePolygonDyn::PolygonDyn;
using SpacePolygonVect::PolygonVect;

#include "composedshape.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
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
	Shape * rp1 = &r1;
	++(++(*rp1));
	cout << "After double pre incrementation, coordinates of r1 are " << r1.getX() << ',' << r1.getY() << ".\n";
	Rectangle r6;
	r6 = r1++;
	cout << "After post incrementation, coordinates of r1 are " << r1.getX() << ',' << r1.getY() << ".\n";
	cout << "After post incrementation, coordinates of r6 are " << r6.getX() << ',' << r6.getY() << ".\n";
	cout << "r2 has a width of " << r2.getWidth() << " and has a height of " << r2.getHeight() <<".\n";
	Rectangle r4;
	r4 = 15.0 + r2;
	cout << "After double addition, r4 has a width of " << r4.getWidth() << " and has a height of " << r4.getHeight() <<".\n";
	Rectangle r5(300,200);
	cout << "Area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	r5.setWidth(50);
	r5.setHeight(80);
	cout << "Now, area and perimeter of the total rectangles are " << Rectangle::getTotalArea() << " and " << Rectangle::getTotalPerimeter() <<".\n";
	//Triangle and Circle objects also work this way.
	ComposedShape c1(Rectangle(300,75),Rectangle(75,25)), c2(Rectangle(200,150),Rectangle(75,25)),
		 c3(Rectangle(200,150),Circle(35)), c4(Rectangle(150,200),Triangle(60)),
		 c5(Circle(100),Rectangle(30,40)), c6(Circle(3000),Circle(1000)),
		 c7(Circle(200),Triangle(50)), c8(Triangle(140),Rectangle(20,30)),
		 c9(Triangle(120),Circle(30));
		 Shape * cp1 = &c1; Shape * cp2 = &c2; Shape * cp3 = &c3; Shape * cp4 = &c4; Shape * cp5 = &c5;
		 Shape * cp6 = &c6; Shape * cp7 = &c7; Shape * cp8 = &c8; Shape * cp9 = &c9;
	cout << *cp1 << c2 << c3 << c4 << c5 << c6 << c7 << c8 << c9; 
	ofstream printfile;
	printfile << *cp1 << *cp2 << *cp3 << *cp4 << *cp5 << *cp6 << *cp7 << *cp8 << *cp9; 
	ComposedShape cs;
	PolygonDyn * p1 = new PolygonDyn(Rectangle(200,100,50,50));
	PolygonDyn * p2 = new PolygonDyn(Circle(50,800,100));
	PolygonDyn * p3 = new PolygonDyn(Triangle(230,1100,50,1215,250,985,250));
	PolygonDyn * p4 = new PolygonDyn(Circle(400,500,600));
	PolygonDyn * p5 = new PolygonDyn(Rectangle(300,900,1600,100));
	PolygonDyn * p6 = new PolygonDyn(Triangle(460,985,550,1215,950,1445,550));
	cout << cs;
	cs += p1; cs += p2; cs += p3; cs += p4; cs += p5; cs += p6; 
	printfile << cs << *(cs[1]) << *(cs[5]);
	try{
		printfile << *(cs[8]);
	}
	catch (MyErrors me){
		me.what();
	}
	c1.optimalFit(Triangle(120),Circle(30));
	printfile << cs << PolygonDyn(Triangle(170)) << PolygonDyn(Circle(85)) << PolygonDyn(Triangle(150)) << PolygonDyn(Rectangle(300,120));
	try{
		Rectangle rtest(-1,-1);
	}
	catch (MyErrors me){
		me.what();
	}
	try{
		Rectangle rtest2(1,-1);
	}
	catch (MyErrors me){
		me.what();
	}
	try{
		Circle ctest(-1);
	}
	catch (MyErrors me){
		me.what();
	}
	try{
		Triangle ttest(-1);
	}
	catch (MyErrors me){
		me.what();
	}
	try{
		PolygonDyn::Point2D p2dtest(-1,-1);
	}
	catch (MyErrors me){
		me.what();
	}
	Rectangle rc1(100,200,0,1200), rc2(400,500,100,1200), rc3(1000,700,500,1200);
	Triangle tr1(200,0,1900), tr2(400,200,1900), tr3(800,600,1900);
	Circle cr1(300,300,3000), cr2(900,1500,3600), cr3(1200,3600,3900);
	PolygonDyn pd1(Circle(600,600,600)), pd2(Rectangle(600,800,1200,0)), pd3(Triangle(1000,1800,0));
	vector<Shape *> vec;
	vec.push_back(&rc1); vec.push_back(&rc2); vec.push_back(&rc3); vec.push_back(&tr1); vec.push_back(&tr2); vec.push_back(&tr3);
	vec.push_back(&cr1); vec.push_back(&cr2); vec.push_back(&cr3); vec.push_back(&pd1); vec.push_back(&pd2); vec.push_back(&pd3);
	cout << "Area of the shapes with their index order:" << endl;
	for (int i = 0; i < vec.size(); ++i){
		cout << vec[i]->getArea() << ' ';
	}
	cout << endl;
	sortShapes(vec);
	cout << "Now, area of the shapes with their index order after sorting:" << endl;
	for (int i = 0; i < vec.size(); ++i){
		cout << vec[i]->getArea() << ' ';
	}
	cout << endl;
	printAll(vec);
	vector<Shape *> vec2 = convertAll(vec);
	printPoly(vec2);
}