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
double Polygon::getArea() const{return area;}
double Polygon::getPerimeter() const{return perimeter;}

Polygon::Point2D::Point2D():Point2D(0.0,0.0){}
Polygon::Point2D::Point2D(int myX, int myY):x(myX),y(myY){
	if (x < 0.0) throw MyErrors(-2);
	if (y < 0.0) throw MyErrors(-2);
}

double Polygon::Point2D::getX() const{return x;}
double Polygon::Point2D::getY() const{return y;}
void Polygon::Point2D::setX(double ix){x = ix; isXvalid();}
void Polygon::Point2D::setY(double iy){y = iy; isYvalid();}

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