#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using std::ostream;
using std::ofstream;

#include "triangle.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;
using std::fixed;
using std::setprecision;

namespace SpaceTriangle
{
Triangle::Triangle():Triangle(5){}
Triangle::Triangle(int myEdge)
	:edge(myEdge),x1(0.0),y1(myEdge*sqrt(3.0)/2.0),x2(myEdge/2.0),y2(0.0),x3(myEdge),y3(myEdge*sqrt(3.0)/2.0){
		isEdgeValid();
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Triangle::Triangle(int myEdge, double myX1, double myY1, double myX2, double myY2, double myX3, double myY3)
	:edge(myEdge),x1(myX1),y1(myY1),x2(myX2),y2(myY2),x3(myX3),y3(myY3){
		isEdgeValid();
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Triangle::Triangle(const Triangle & other){
	edge = other.edge;
	x1 = other.x1;
	y1 = other.y1;
	x2 = other.x2;
	y2 = other.y2;
	x3 = other.x3;
	y3 = other.y3;
	totalArea += getArea();
	totalPerimeter += getPerimeter();
}
Triangle & Triangle::operator = (const Triangle & other){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	edge = other.edge;
	x1 = other.x1;
	y1 = other.y1;
	x2 = other.x2;
	y2 = other.y2;
	x3 = other.x3;
	y3 = other.y3;
	totalArea += getArea();
	totalPerimeter += getPerimeter();
	return *this;
}
Triangle::~Triangle(){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
}
void Triangle::setEdge(int myEdge){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	edge = myEdge;
	isEdgeValid();
	totalArea += getArea();
	totalPerimeter = getPerimeter();
}
void Triangle::setX1(double myX1){x1 = myX1;}
void Triangle::setY1(double myY1){y1 = myY1;}
void Triangle::setX2(double myX2){x2 = myX2;}
void Triangle::setY2(double myY2){y2 = myY2;}
void Triangle::setX3(double myX3){x3 = myX3;}
void Triangle::setY3(double myY3){y3 = myY3;}
int Triangle::getEdge() const{return edge;}
double Triangle::Triangle::getPerimeter() const{return edge*3.0;}
double Triangle::getArea() const{return edge*edge*sqrt(3.0)/4.0;}
double Triangle::getX1() const{return x1;}
double Triangle::getY1() const{return y1;}
double Triangle::getX2() const{return x2;}
double Triangle::getY2() const{return y2;}
double Triangle::getX3() const{return x3;}
double Triangle::getY3() const{return y3;}
double Triangle::getTotalArea(){return totalArea;}
double Triangle::getTotalPerimeter(){return totalPerimeter;}

Triangle Triangle::operator ++ (){
	++x1;
	++y1;
	++x2;
	++y2;
	++x3;
	++y3;
	return *this;
}

Triangle Triangle::operator ++ (int ignoreMe){
	Triangle temp = *this;
	++x1;
	++y1;
	++x2;
	++y2;
	++x3;
	++y3;
	return temp;
}

Triangle Triangle::operator -- (){
	--x1;
	--y1;
	--x2;
	--y2;
	--x3;
	--y3;
	return *this;
}

Triangle Triangle::operator -- (int ignoreMe){
	Triangle temp = *this;
	--x1;
	--y1;
	--x2;
	--y2;
	--x3;
	--y3;
	return temp;
}

const Triangle Triangle::operator + (double mySize) const{
	Triangle temp = *this;
	temp.edge = ((temp.edge+mySize < 1) ? 1 : temp.edge+mySize);
	return temp;
}

const Triangle Triangle::operator - (double mySize) const{
	Triangle temp = *this;
	temp.edge = ((temp.edge-mySize < 1) ? 1 : temp.edge-mySize);
	return temp;
}

const Triangle operator + (double mySize, const Triangle & myTriangle){
	Triangle temp = myTriangle;
	temp.edge = ((temp.edge+mySize < 1) ? 1 : temp.edge+mySize);
	return temp;
}

const Triangle operator - (double mySize, const Triangle & myTriangle){
	Triangle temp = myTriangle;
	temp.edge = ((temp.edge-mySize < 1) ? 1 : temp.edge-mySize);
	return temp;	
}

bool Triangle::operator == (const Triangle & other) const{return (getEdge() == other.getEdge());}
bool Triangle::operator != (const Triangle & other) const{return (getArea() != other.getArea());}
bool Triangle::operator < (const Triangle & other) const{return (getArea() < other.getArea());}
bool Triangle::operator > (const Triangle & other) const{return (getArea() > other.getArea());}
bool Triangle::operator <= (const Triangle & other) const{return (getArea() <= other.getArea());}
bool Triangle::operator >= (const Triangle & other) const{return (getArea() >= other.getArea());}

ostream & operator << (ostream & print, const Triangle & smallShape){
	print << "Your triangle has an edge length of " << smallShape.getEdge() << ", has a perimeter length of "
		  << static_cast <int> (smallShape.getPerimeter()) << " and the area is " << fixed << setprecision(2) << smallShape.getArea() << "." << endl;
	return print;
}

ofstream & operator << (ofstream & file, const Triangle & smallShape){
	file.open("triangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << smallShape.getEdge() << R"(" height=")" << smallShape.getEdge()*sqrt(3.0)/2.0 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")" << 0.0 << ',' << smallShape.getEdge()*sqrt(3.0)/2.0 << ' ' << smallShape.getEdge()/2.0 << ',' << 0.0 << ' ' << smallShape.getEdge() << ',' << smallShape.getEdge()*sqrt(3.0)/2.0 << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

void Triangle::isEdgeValid(){
	if (getEdge() < 1){
		cout << "Please enter a valid input for the edge" << endl;
		string str;
		getline(cin,str,'\n');
		int size = str.size();
		if(size == 0){
			setEdge(-1);
			return;
		}
		if(size == 1 && (str[0] > '9' || str[0] < '0')){
			setEdge(-1);
			return;
		}
		for (int i = 0; i < size; ++i){
			if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
				setEdge(-1);
				return;
			}
		}
		int count = 0;
		for (int i = 0; i < size; ++i){
			if(str[i] == '.')
				++count;
			if(count > 1){
				setEdge(-1);
				return;
			}
		}
		int length = stod(str);
		if (length < 1){
			setEdge(-1);
			return;
		}
		setEdge(length);
	}
}
}