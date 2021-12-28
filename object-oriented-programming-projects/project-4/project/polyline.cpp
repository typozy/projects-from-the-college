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

#include "polyline.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;

namespace {
	const double PI = 3.14159265358979;
}

namespace SpacePolyline
{
Polyline::Point2D::Point2D():Point2D(0.0,0.0){}
Polyline::Point2D::Point2D(int myX, int myY):x(myX),y(myY){isXvalid(); isYvalid();}

double Polyline::Point2D::getX() const{return x;}
double Polyline::Point2D::getY() const{return y;}
void Polyline::Point2D::setX(double ix){x = ix; isXvalid();}
void Polyline::Point2D::setY(double iy){y = iy; isYvalid();}

double Polyline::getSize() const{return size;}

const Polyline::Point2D & Polyline::operator [] (int index) const{
	return ((index < size && index > -1) ? points[index] : noPoint);
}
Polyline::Point2D & Polyline::operator [] (int index){
	return ((index < size && index > -1) ? points[index] : noPoint);
}

bool Polyline::operator == (const Polyline & other) const{
	if (size != other.size) return false;
	for(int i=0; i<size; ++i)
		if (abs(points[i].getX()-other.points[i].getX()) > 0.001 || abs(points[i].getY()-other.points[i].getY()) > 0.001)
			return false;
	return true;
}
bool Polyline::operator != (const Polyline & other) const{
	return !(*this == other);
}

const Polyline Polyline::operator + (const Polyline & other) const{
	Polyline temp;
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

Polyline::Polyline()
	:size(0),points(nullptr){}
Polyline::Polyline(const Rectangle & rect)
	:size(5){
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
		points[4].setX(rx);
		points[4].setY(ry);
	}
Polyline::Polyline(const Circle & circ)
	:size(101){
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
		points[100].setX(points[0].getX());
		points[100].setY(points[0].getY());
	}
Polyline::Polyline(const Triangle & tria)
	:size(4){
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
		points[3].setX(tria.getX1()-tempX);
		points[3].setY(tria.getY1()-tempY);
	}
Polyline::Polyline(const vector<Point2D> & vec2d){
	size = vec2d.size();
	points = new Point2D[size];
	for(int i=0; i<size; ++i){
		points[i].setX(vec2d[i].getX());
		points[i].setY(vec2d[i].getY());
	}
}
Polyline::Polyline(const Point2D & p2d):size(1){
	points = new Point2D[size];
	points[0].setX(p2d.getX());
	points[0].setY(p2d.getY());
}
Polyline::Polyline(const Polyline & pl){
	size = pl.size;
	points = new Point2D[size];
	for (int i=0; i<size; ++i){
		points[i].setX(pl.points[i].getX());
		points[i].setY(pl.points[i].getY());
	}
}
Polyline & Polyline::operator = (const Polyline & pl){
	if(points != nullptr) delete [] points;
	size = pl.size;
	points = new Point2D[size];
	for (int i=0; i<size; ++i){
		points[i].setX(pl.points[i].getX());
		points[i].setY(pl.points[i].getY());
	}
	return *this;
}
Polyline::~Polyline(){
	if(points != nullptr) delete [] points;
}
ofstream & operator << (ofstream & file, const Polyline & pl){
	if (pl.size < 2){
		cout << "This polyline has no line to draw." << endl;
		return file;
	}
	double maxX=0.0,minX=0.0,maxY=0.0,minY=0.0;
	for(int i=0; i<pl.size; ++i){
		if(pl.points[i].getX() > maxX) maxX=pl.points[i].getX();
		if(pl.points[i].getY() > maxY) maxY=pl.points[i].getY();
	}
	minX=maxX;
	minY=maxY;
	for(int i=0; i<pl.size; ++i){
		if(pl.points[i].getX() < minX) minX=pl.points[i].getX();
		if(pl.points[i].getY() < minY) minY=pl.points[i].getY();
	}
	if (pl.size == 5) file.open("polylinerectangle.svg");
	else if (pl.size == 101) file.open("polylinecircle.svg");
	else if (pl.size == 4) file.open("polylinetriangle.svg");
	else file.open("polyline.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << maxX-minX << R"(" height=")" << maxY-minY << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="cyan" />)" << endl;
	file << '\t' << R"(<polyline points = ")";
	for(int i=0; i<pl.size; ++i){
		file << pl.points[i].getX()-minX << ',' << pl.points[i].getY()-minY;
		if (i<pl.size-1) file << ' ';
	}
	file << R"(" fill = "none" stroke = "magenta" stroke-width = "3" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

void Polyline::Point2D::isXvalid(){
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

void Polyline::Point2D::isYvalid(){
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