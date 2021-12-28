#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using std::ostream;
using std::ofstream;

#include "rectangle.h"
#include "triangle.h"
#include "circle.h"

using std::vector;
using SpaceRectangle::Rectangle;
using SpaceCircle::Circle;
using SpaceTriangle::Triangle;

#include "polygon.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;

namespace {
	const double PI = 3.14159265358979;
}

namespace SpacePolygon
{
Polygon::Point2D::Point2D():Point2D(0.0,0.0){}
Polygon::Point2D::Point2D(int myX, int myY):x(myX),y(myY){isXvalid(); isYvalid();}

double Polygon::Point2D::getX() const{return x;}
double Polygon::Point2D::getY() const{return y;}
void Polygon::Point2D::setX(double ix){x = ix; isXvalid();}
void Polygon::Point2D::setY(double iy){y = iy; isYvalid();}

double Polygon::getSize() const{return size;}
double Polygon::getArea() const{return area;}
double Polygon::getPerimeter() const{return perimeter;}

const Polygon::Point2D & Polygon::operator [] (int index) const{
	return ((index < size && index > -1) ? points[index] : noPoint);
}
Polygon::Point2D & Polygon::operator [] (int index){
	return ((index < size && index > -1) ? points[index] : noPoint);
}

bool Polygon::operator == (const Polygon & other) const{
	if (size != other.size) return false;
	for(int i=0; i<size; ++i)
		if (abs(points[i].getX()-other.points[i].getX()) > 0.001 || abs(points[i].getY()-other.points[i].getY()) > 0.001)
			return false;
	return true;
}
bool Polygon::operator != (const Polygon & other) const{
	return !(*this == other);
}

const Polygon Polygon::operator + (const Polygon & other) const{
	Polygon temp;
	temp.size = size + other.size;
	temp.points = new Point2D[temp.size];
	for (int i=0; i<size; ++i){
		temp.points[i].setX(points[i].getX());
		temp.points[i].setY(points[i].getY());
	}
	for (int i=0; i<other.size; ++i){
		temp.points[i+size].setX(other.points[i].getX());
		temp.points[i+size].setY(other.points[i].getY());
	}
	return temp;
}

Polygon::Polygon()
	:size(0),points(nullptr){}
Polygon::Polygon(int pg)
	:size(4){
		points = new Point2D[size];
		points[0].setX(0);
		points[0].setY(0);
		points[1].setX(1920);
		points[1].setY(0);
		points[2].setX(1920);
		points[2].setY(1080);
		points[3].setX(0);
		points[3].setY(1080);
		area = 1920*1080;
		perimeter = 2*(1920+1080);
	}
Polygon::Polygon(const Rectangle & rect)
	:size(4){
		points = new Point2D[size];
		double rx = rect.getX();
		double ry = rect.getY();
		if (rx < 0.0) rx = 0.0;
		if (ry < 0.0) ry = 0.0;
		points[0].setX(rx);
		points[0].setY(ry);
		points[1].setX(rx+rect.getWidth());
		points[1].setY(ry);
		points[2].setX(rx+rect.getWidth());
		points[2].setY(ry+rect.getHeight());
		points[3].setX(rx);
		points[3].setY(ry+rect.getHeight());
		area = rect.getArea();
		perimeter = rect.getPerimeter();
	}
Polygon::Polygon(const Circle & circ)
	:size(100){
		points = new Point2D[size];
		double cx = circ.getX();
		double cy = circ.getY();
		double r = circ.getRadius();
		if (cx < r) cx = r;
		if (cy < r) cy = r;
		for (int i=0; i<100; ++i){
			points[i].setX(cx+r*cos(i*2.0*PI/100.0));
			points[i].setY(cy-r*sin(i*2.0*PI/100.0));
		}
		area = circ.getArea();
		perimeter = circ.getPerimeter();
	}
Polygon::Polygon(const Triangle & tria)
	:size(3){
		points = new Point2D[size];
		double tempX = 0.0;
		if (tempX > tria.getX1()) tempX = tria.getX1();
		if (tempX > tria.getX2()) tempX = tria.getX2();
		if (tempX > tria.getX3()) tempX = tria.getX3();
		double tempY = 0.0;
		if (tempY > tria.getY1()) tempX = tria.getY1();
		if (tempY > tria.getY2()) tempX = tria.getY2();
		if (tempY > tria.getY3()) tempX = tria.getY3();
		points[0].setX(tria.getX1()-tempX);
		points[0].setY(tria.getY1()-tempY);
		points[1].setX(tria.getX2()-tempX);
		points[1].setY(tria.getY2()-tempY);
		points[2].setX(tria.getX3()-tempX);
		points[2].setY(tria.getY3()-tempY);
		area = tria.getArea();
		perimeter = tria.getPerimeter();
	}
Polygon::Polygon(const vector<Point2D> & vec2d):area(0.0),perimeter(0.0){
	size = vec2d.size();
	points = new Point2D[size];
	for(int i=0; i<size; ++i){
		points[i].setX(vec2d[i].getX());
		points[i].setY(vec2d[i].getY());
	}
}
Polygon::Polygon(const Point2D & p2d):size(1),area(0.0),perimeter(0.0){
	points = new Point2D[size];
	points[0].setX(p2d.getX());
	points[0].setY(p2d.getY());
}
Polygon::Polygon(const Polygon & pg){
	size = pg.size;
	area = pg.area;
	perimeter = pg.perimeter;
	points = new Point2D[size];
	for (int i=0; i<size; ++i){
		points[i].setX(pg.points[i].getX());
		points[i].setY(pg.points[i].getY());
	}
}
Polygon & Polygon::operator = (const Polygon & pg){
	if(points != nullptr) delete [] points;
	size = pg.size;
	area = pg.area;
	perimeter = pg.perimeter;
	points = new Point2D[size];
	for (int i=0; i<size; ++i){
		points[i].setX(pg.points[i].getX());
		points[i].setY(pg.points[i].getY());
	}
	return *this;
}
Polygon::~Polygon(){
	if(points != nullptr) delete [] points;
}
ofstream & operator << (ofstream & file, const Polygon & pg){
	if (pg.size < 3){
		cout << "This polygon has no shape to draw." << endl;
		return file;
	}
	double maxX=0.0,minX=0.0,maxY=0.0,minY=0.0;
	for(int i=0; i<pg.size; ++i){
		if(pg.points[i].getX() > maxX) maxX=pg.points[i].getX();
		if(pg.points[i].getY() > maxY) maxY=pg.points[i].getY();
	}
	minX=maxX;
	minY=maxY;
	for(int i=0; i<pg.size; ++i){
		if(pg.points[i].getX() < minX) minX=pg.points[i].getX();
		if(pg.points[i].getY() < minY) minY=pg.points[i].getY();
	}
	if (pg.size == 4) file.open("polygonrectangle.svg");
	else if (pg.size == 100) file.open("polygoncircle.svg");
	else if (pg.size == 3) file.open("polygontriangle.svg");
	else file.open("polygon.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << maxX-minX << R"(" height=")" << maxY-minY << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<pg.size; ++i){
		file << pg.points[i].getX()-minX << ',' << pg.points[i].getY()-minY;
		if (i<pg.size-1) file << ' ';
	}
	file << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

ofstream & Polygon::drawContainer(ofstream & file) const{
	double maxX=0.0,minX=0.0,maxY=0.0,minY=0.0;
	for(int i=0; i<size; ++i){
		if(points[i].getX() > maxX) maxX=points[i].getX();
		if(points[i].getY() > maxY) maxY=points[i].getY();
	}
	minX=maxX;
	minY=maxY;
	for(int i=0; i<size; ++i){
		if(points[i].getX() < minX) minX=points[i].getX();
		if(points[i].getY() < minY) minY=points[i].getY();
	}
	file << R"(<svg version="1.1" baseProfile="full" width=")" << maxX-minX << R"(" height=")" << maxY-minY << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<size; ++i){
		file << points[i].getX()-minX << ',' << points[i].getY()-minY;
		if (i<size-1) file << ' ';
	}
	file << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

ofstream & Polygon::drawSmall(ofstream & file) const{
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<size; ++i){
		file << points[i].getX() << ',' << points[i].getY();
		if (i<size-1) file << ' ';
	}
	file << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

void Polygon::Point2D::isXvalid(){
	if (getX() < 0.0){
		cout << "Please enter a valid input for X coordinate" << endl;
		string str;
		getline(cin,str,'\n');
		int size = str.size();
		if(size == 0){
			setX(-1);
			return;
		}
		if(size == 1 && (str[0] > '9' || str[0] < '0')){
			setX(-1);
			return;
		}
		for (int i = 0; i < size; ++i){
			if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
				setX(-1);
				return;
			}
		}
		int count = 0;
		for (int i = 0; i < size; ++i){
			if(str[i] == '.')
				++count;
			if(count > 1){
				setX(-1);
				return;
			}
		}
		double tempX = stod(str);
		if (tempX < 0.0){
			setX(-1);
			return;
		}
		setX(tempX);
	}
}

void Polygon::Point2D::isYvalid(){
	if (getY() < 0.0){
		cout << "Please enter a valid input for Y coordinate" << endl;
		string str;
		getline(cin,str,'\n');
		int size = str.size();
		if(size == 0){
			setY(-1);
			return;
		}
		if(size == 1 && (str[0] > '9' || str[0] < '0')){
			setY(-1);
			return;
		}
		for (int i = 0; i < size; ++i){
			if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
				setY(-1);
				return;
			}
		}
		int count = 0;
		for (int i = 0; i < size; ++i){
			if(str[i] == '.')
				++count;
			if(count > 1){
				setY(-1);
				return;
			}
		}
		double tempY = stod(str);
		if (tempY < 0.0){
			setY(-1);
			return;
		}
		setY(tempY);
	}
}
}