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
#include "triangle.h"
#include "circle.h"
#include "polygon.h"

using SpaceRectangle::Rectangle;
using SpaceCircle::Circle;
using SpaceTriangle::Triangle;
using SpacePolygon::Polygon;

#include "polygondyn.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;

namespace {
	const double PI = 3.14159265358979;
}

namespace SpacePolygonDyn
{
double PolygonDyn::getSize() const{return size;}

const PolygonDyn::Point2D & PolygonDyn::operator [] (int index) const{
	if (index < 0 || index >= size) throw MyErrors(-1);
	return points[index];
}
PolygonDyn::Point2D & PolygonDyn::operator [] (int index){
	if (index < 0 || index >= size) throw MyErrors(-1);
	return points[index];
}

const PolygonDyn PolygonDyn::operator + (const PolygonDyn & other) const{
	PolygonDyn temp;
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

PolygonDyn & PolygonDyn::operator ++ (){
	for (int i = 0; i < size; ++i){
		points[i].setX(points[i].getX()+1.0);
		points[i].setX(points[i].getX()+1.0);
	}
	return *this;
}
PolygonDyn & PolygonDyn::operator ++ (int ignoreMe){
	PolygonDyn * pdp = new PolygonDyn(*this);
	for (int i = 0; i < size; ++i){
		points[i].setX(points[i].getX()+1.0);
		points[i].setX(points[i].getX()+1.0);
	}
	return *pdp;
}
PolygonDyn & PolygonDyn::operator -- (){
	for (int i = 0; i < size; ++i){
		if (points[i].getX() > 1.0) points[i].setX(points[i].getX()-1.0); else points[i].setX(0.0);
		if (points[i].getY() > 1.0) points[i].setY(points[i].getY()-1.0); else points[i].setY(0.0);
	}
	return *this;
}
PolygonDyn & PolygonDyn::operator -- (int ignoreMe){
	PolygonDyn * pdp = new PolygonDyn(*this);
	for (int i = 0; i < size; ++i){
		if (points[i].getX() > 1.0) points[i].setX(points[i].getX()-1.0); else points[i].setX(0.0);
		if (points[i].getY() > 1.0) points[i].setY(points[i].getY()-1.0); else points[i].setY(0.0);
	}
	return *pdp;
}

PolygonDyn::PolygonDyn()
	:points(nullptr),size(0){}
PolygonDyn::PolygonDyn(int pg)
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
PolygonDyn::PolygonDyn(const Rectangle & rect)
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
PolygonDyn::PolygonDyn(const Circle & circ)
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
PolygonDyn::PolygonDyn(const Triangle & tria)
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
PolygonDyn::PolygonDyn(const vector<Point2D> & vec2d){
	size = vec2d.size();
	area = 0.0;
	perimeter = 0.0;
	points = new Point2D[size];
	for(int i=0; i<size; ++i){
		points[i].setX(vec2d[i].getX());
		points[i].setY(vec2d[i].getY());
	}
}
PolygonDyn::PolygonDyn(const Point2D & p2d):size(1){
	area = 0.0;
	perimeter = 0.0;
	points = new Point2D[size];
	points[0].setX(p2d.getX());
	points[0].setY(p2d.getY());
}
PolygonDyn::PolygonDyn(const PolygonDyn & pg){
	if (this != &pg){
		size = pg.size;
		area = pg.area;
		perimeter = pg.perimeter;
		points = new Point2D[size];
		for (int i=0; i<size; ++i){
			points[i].setX(pg.points[i].getX());
			points[i].setY(pg.points[i].getY());
		}
	}
}
PolygonDyn & PolygonDyn::operator = (const PolygonDyn & pg){
	if (this != &pg){
		if(points != nullptr) delete [] points;
		size = pg.size;
		area = pg.area;
		perimeter = pg.perimeter;
		points = new Point2D[size];
		for (int i=0; i<size; ++i){
			points[i].setX(pg.points[i].getX());
			points[i].setY(pg.points[i].getY());
		}
	}
	return *this;
}
PolygonDyn::~PolygonDyn(){
	if(points != nullptr) delete [] points;
}
ofstream & PolygonDyn::draw(ofstream & file) const{
	if (size < 3){
		cout << "This polygon has no shape to draw." << endl;
		return file;
	}
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
	if (size == 4) file.open("polygonrectangle.svg");
	else if (size == 100) file.open("polygoncircle.svg");
	else if (size == 3) file.open("polygontriangle.svg");
	else file.open("polygon.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << maxX-minX << R"(" height=")" << maxY-minY << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<size; ++i){
		file << points[i].getX()-minX << ',' << points[i].getY()-minY;
		if (i<size-1) file << ' ';
	}
	file << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

ofstream & PolygonDyn::drawContainer(ofstream & file) const{
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
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<size; ++i){
		file << points[i].getX()-minX << ',' << points[i].getY()-minY;
		if (i<size-1) file << ' ';
	}
	file << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

ofstream & PolygonDyn::drawSmall(ofstream & file) const{
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<size; ++i){
		file << points[i].getX() << ',' << points[i].getY();
		if (i<size-1) file << ' ';
	}
	file << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}
}