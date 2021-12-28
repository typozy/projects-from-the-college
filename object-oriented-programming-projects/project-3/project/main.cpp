#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "attribute.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "composedshape.h"

void driver();

double Rectangle::totalArea = 0.0;
double Rectangle::totalPerimeter = 0.0;
double Circle::totalArea = 0.0;
double Circle::totalPerimeter = 0.0;
double Triangle::totalArea = 0.0;
double Triangle::totalPerimeter = 0.0;

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
	//Triangle and Circle objects are also works this way.
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
	ComposedShape::ShapeElem a,b,c,d,e,f;
	a.setShapeObject(static_cast <void *> (new Rectangle(200,100,50,50)));
	a.setObjectType(Shape::Rectangle);
	b.setShapeObject(static_cast <void *> (new Circle(50,800,100)));
	b.setObjectType(Shape::Circle);
	c.setShapeObject(static_cast <void *> (new Triangle(230,1100,50,1215,250,985,250)));
	c.setObjectType(Shape::Triangle);
	d.setShapeObject(static_cast <void *> (new Circle(400,500,600)));
	d.setObjectType(Shape::Circle);
	e.setShapeObject(static_cast <void *> (new Rectangle(300,900,1600,100)));
	e.setObjectType(Shape::Rectangle);
	f.setShapeObject(static_cast <void *> (new Triangle(460,985,550,1215,950,1445,550)));
	f.setObjectType(Shape::Triangle);
	cs += a; cs += b; cs += c; cs += d; cs += e; cs += f;
	cout << cs;
	printfile << cs << a << b << f;
	cout << cs[2] << cs[4] << cs[7];
}
