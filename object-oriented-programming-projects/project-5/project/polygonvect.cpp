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

#include "polygonvect.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;

namespace {
	const double PI = 3.14159265358979;
}

namespace SpacePolygonVect
{
double PolygonVect::getSize() const{return points.size();}

const PolygonVect::Point2D & PolygonVect::operator [] (int index) const{
	if (index < 0 || index >= points.size()) throw MyErrors(-1);
	return points[index];
}
PolygonVect::Point2D & PolygonVect::operator [] (int index){
	if (index < 0 || index >= points.size()) throw MyErrors(-1);
	return points[index];
}

const PolygonVect PolygonVect::operator + (const PolygonVect & other) const{
	PolygonVect temp;
	for (int i=0; i<points.size(); ++i){
		temp.points.push_back(points[i]);
	}
	for (int i=0; i<other.points.size(); ++i){
		temp.points.push_back(other[i]);
	}
	return temp;
}

PolygonVect & PolygonVect::operator ++ (){
	for (int i = 0; i < points.size(); ++i){
		points[i].setX(points[i].getX()+1.0);
		points[i].setX(points[i].getX()+1.0);
	}
	return *this;
}
PolygonVect & PolygonVect::operator ++ (int ignoreMe){
	PolygonVect * pvp = new PolygonVect;
	*pvp = *this;
	for (int i = 0; i < points.size(); ++i){
		points[i].setX(points[i].getX()+1.0);
		points[i].setX(points[i].getX()+1.0);
	}
	return *pvp;
}
PolygonVect & PolygonVect::operator -- (){
	for (int i = 0; i < points.size(); ++i){
		if (points[i].getX() > 1.0) points[i].setX(points[i].getX()-1.0); else points[i].setX(0.0);
		if (points[i].getY() > 1.0) points[i].setY(points[i].getY()-1.0); else points[i].setY(0.0);
	}
	return *this;
}
PolygonVect & PolygonVect::operator -- (int ignoreMe){
	PolygonVect * pvp = new PolygonVect;
	*pvp = *this;
	for (int i = 0; i < points.size(); ++i){
		if (points[i].getX() > 1.0) points[i].setX(points[i].getX()-1.0); else points[i].setX(0.0);
		if (points[i].getY() > 1.0) points[i].setY(points[i].getY()-1.0); else points[i].setY(0.0);
	}
	return *pvp;
}

PolygonVect::PolygonVect(){}
PolygonVect::PolygonVect(int pg){
		Point2D p2d;
		p2d.setX(0);
		p2d.setY(0);
		points.push_back(p2d);
		p2d.setX(1920);
		p2d.setY(0);
		points.push_back(p2d);
		p2d.setX(1920);
		p2d.setY(1080);
		points.push_back(p2d);
		p2d.setX(0);
		p2d.setY(1080);
		points.push_back(p2d);
		area = 1920*1080;
		perimeter = 2*(1920+1080);
	}
PolygonVect::PolygonVect(const Rectangle & rect){
		Point2D p2d;
		double rx = rect.getX();
		double ry = rect.getY();
		if (rx < 0.0) rx = 0.0;
		if (ry < 0.0) ry = 0.0;
		p2d.setX(rx);
		p2d.setY(ry);
		points.push_back(p2d);
		p2d.setX(rx+rect.getWidth());
		p2d.setY(ry);
		points.push_back(p2d);
		p2d.setX(rx+rect.getWidth());
		p2d.setY(ry+rect.getHeight());
		points.push_back(p2d);
		p2d.setX(rx);
		p2d.setY(ry+rect.getHeight());
		points.push_back(p2d);
		area = rect.getArea();
		perimeter = rect.getPerimeter();
	}
PolygonVect::PolygonVect(const Circle & circ){
		Point2D p2d;
		double cx = circ.getX();
		double cy = circ.getY();
		double r = circ.getRadius();
		if (cx < r) cx = r;
		if (cy < r) cy = r;
		for (int i=0; i<100; ++i){
			p2d.setX(cx+r*cos(i*2.0*PI/100.0));
			p2d.setY(cy-r*sin(i*2.0*PI/100.0));
			points.push_back(p2d);
		}
		area = circ.getArea();
		perimeter = circ.getPerimeter();
	}
PolygonVect::PolygonVect(const Triangle & tria){
		Point2D p2d;
		double tempX = 0.0;
		if (tempX > tria.getX1()) tempX = tria.getX1();
		if (tempX > tria.getX2()) tempX = tria.getX2();
		if (tempX > tria.getX3()) tempX = tria.getX3();
		double tempY = 0.0;
		if (tempY > tria.getY1()) tempX = tria.getY1();
		if (tempY > tria.getY2()) tempX = tria.getY2();
		if (tempY > tria.getY3()) tempX = tria.getY3();
		p2d.setX(tria.getX1()-tempX);
		p2d.setY(tria.getY1()-tempY);
		points.push_back(p2d);
		p2d.setX(tria.getX2()-tempX);
		p2d.setY(tria.getY2()-tempY);
		points.push_back(p2d);
		p2d.setX(tria.getX3()-tempX);
		p2d.setY(tria.getY3()-tempY);
		points.push_back(p2d);
		area = tria.getArea();
		perimeter = tria.getPerimeter();
	}
PolygonVect::PolygonVect(const vector<PolygonVect::Point2D> & vec2d){
	area = 0.0;
	perimeter = 0.0;
	points = vec2d;
}
PolygonVect::PolygonVect(const Point2D & p2d){
	area = 0.0;
	perimeter = 0.0;
	points.push_back(p2d);
}
ofstream & PolygonVect::draw(ofstream & file) const{
	if (points.size() < 3){
		cout << "This polygon has no shape to draw." << endl;
		return file;
	}
	double maxX=0.0,minX=0.0,maxY=0.0,minY=0.0;
	for(int i=0; i<points.size(); ++i){
		if(points[i].getX() > maxX) maxX=points[i].getX();
		if(points[i].getY() > maxY) maxY=points[i].getY();
	}
	minX=maxX;
	minY=maxY;
	for(int i=0; i<points.size(); ++i){
		if(points[i].getX() < minX) minX=points[i].getX();
		if(points[i].getY() < minY) minY=points[i].getY();
	}
	if (points.size() == 4) file.open("polygonrectangle.svg");
	else if (points.size() == 100) file.open("polygoncircle.svg");
	else if (points.size() == 3) file.open("polygontriangle.svg");
	else file.open("polygon.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << maxX-minX << R"(" height=")" << maxY-minY << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<points.size(); ++i){
		file << points[i].getX()-minX << ',' << points[i].getY()-minY;
		if (i<points.size()-1) file << ' ';
	}
	file << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

ofstream & PolygonVect::drawContainer(ofstream & file) const{
	double maxX=0.0,minX=0.0,maxY=0.0,minY=0.0;
	for(int i=0; i<points.size(); ++i){
		if(points[i].getX() > maxX) maxX=points[i].getX();
		if(points[i].getY() > maxY) maxY=points[i].getY();
	}
	minX=maxX;
	minY=maxY;
	for(int i=0; i<points.size(); ++i){
		if(points[i].getX() < minX) minX=points[i].getX();
		if(points[i].getY() < minY) minY=points[i].getY();
	}
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<points.size(); ++i){
		file << points[i].getX()-minX << ',' << points[i].getY()-minY;
		if (i<points.size()-1) file << ' ';
	}
	file << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

ofstream & PolygonVect::drawSmall(ofstream & file) const{
	file << '\t' << R"(<polygon points = ")";
	for(int i=0; i<points.size(); ++i){
		file << points[i].getX() << ',' << points[i].getY();
		if (i<points.size()-1) file << ' ';
	}
	file << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}
}