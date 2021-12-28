#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <typeinfo>

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

using std::endl;
using std::string;
using SpaceComposedShape::ComposedShape;

namespace SpaceShape
{
void printAll(const vector<Shape *> & shapeVec){
	ofstream file;
	file.open("allshapes.svg");
	file << R"(<svg version="1.1" baseProfile="full" width="100%" height="100%" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	for (int i = 0; i < shapeVec.size(); ++i)
		shapeVec[i]->drawSmall(file);
	file << "</svg>";
	file.close();
}
void printPoly(const vector<Shape *> & shapeVec){
	ofstream file;
	string s;
	file.open("polyshapes.svg");
	file << R"(<svg version="1.1" baseProfile="full" width="100%" height="100%" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	for (int i = 0; i < shapeVec.size(); ++i){
		s = typeid(*(shapeVec[i])).name();
		if (s == "N15SpacePolygonDyn10PolygonDynE" || s == "N16SpacePolygonVect11PolygonVectE")
			shapeVec[i]->drawSmall(file);
	}
	file << "</svg>";
	file.close();
}
vector<Shape *> convertAll(const vector<Shape *> & shapeVec){
	string s;
	vector<Shape *> polyVec;
	Shape * sp;
	for (int i = 0; i < shapeVec.size(); ++i){
		s = typeid(*(shapeVec[i])).name();
		if (s == "N14SpaceRectangle9RectangleE"){
			Rectangle * rp = dynamic_cast <Rectangle *> (shapeVec[i]);
			sp = new PolygonDyn(*rp);
			polyVec.push_back(sp);
		}
		else if (s == "N11SpaceCircle6CircleE"){
			Circle * cp = dynamic_cast <Circle *> (shapeVec[i]);
			sp = new PolygonDyn(*cp);
			polyVec.push_back(sp);
		}
		else if (s == "N13SpaceTriangle8TriangleE"){
			Triangle * tp = dynamic_cast <Triangle *> (shapeVec[i]);
			sp = new PolygonDyn(*tp);
			polyVec.push_back(sp);
		}
		else if (s == "N15SpacePolygonDyn10PolygonDynE"){
			PolygonDyn * pdp = dynamic_cast <PolygonDyn *> (shapeVec[i]);
			sp = new PolygonDyn(*pdp);
			polyVec.push_back(sp);
		}
		else if (s == "N16SpacePolygonVect11PolygonVectE"){
			PolygonVect * pvp = dynamic_cast <PolygonVect *> (shapeVec[i]);
			sp = new PolygonVect(*pvp);
			polyVec.push_back(sp);
		}
	}
	return polyVec;
}
void sortShapes(vector<Shape *> & shapeVec){
	for (int i = 0; i < shapeVec.size()-1; ++i){
		for (int j = i+1; j < shapeVec.size(); ++j){
			if (shapeVec[i]->getArea() > shapeVec[j]->getArea()){
				Shape * sp;
				sp = shapeVec[i];
				shapeVec[i] = shapeVec[j];
				shapeVec[j] = sp;
			}
		}
	}
}

bool Shape::operator == (const Shape & other) const{return (abs(getArea()-other.getArea()) <= 0.001);}
bool Shape::operator != (const Shape & other) const{return (abs(getArea()-other.getArea()) > 0.001);}
bool Shape::operator < (const Shape & other) const{return (getArea() < other.getArea());}
bool Shape::operator > (const Shape & other) const{return (getArea() > other.getArea());}
bool Shape::operator <= (const Shape & other) const{return (getArea() <= other.getArea());}
bool Shape::operator >= (const Shape & other) const{return (getArea() >= other.getArea());}

//Shape::~Shape(){}

ofstream & operator << (ofstream & file, const Shape & sh){
	sh.draw(file);
	return file;
}

ostream & operator << (ostream & print, const Shape & sh){
	sh.printOut(print);
	return print;
}
}