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

#include "circle.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;
using std::fixed;
using std::setprecision;

namespace {
	const double PI = 3.14159265358979;
}

namespace SpaceCircle
{
Circle::Circle():Circle(5){}
Circle::Circle(int myRadius)
	:radius(myRadius),x(myRadius),y(myRadius){
		if (radius < 1) throw MyErrors(-5);
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Circle::Circle(int myRadius, double myX, double myY)
	:radius(myRadius),x(myX),y(myY){
		if (radius < 1) throw MyErrors(-5);
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Circle::Circle(const Circle & other){
	radius = other.radius;
	x = other.x;
	y = other.y;
	totalArea += other.getArea();
	totalPerimeter += other.getPerimeter();
}
Circle & Circle::operator = (const Circle & other){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	radius = other.radius;
	x = other.x;
	y = other.y;
	totalArea += other.getArea();
	totalPerimeter += other.getPerimeter();
	return *this;
}
Circle::~Circle(){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
}
void Circle::setRadius(int myRadius){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	radius = myRadius;
	isRadiusValid();
	totalArea += getArea();
	totalPerimeter += getPerimeter();
}
void Circle::setX(double myX){x = myX;}
void Circle::setY(double myY){y = myY;}
int Circle::getRadius() const{return radius;}
double Circle::Circle::getPerimeter() const{return 2.0*PI*radius;}
double Circle::getArea() const{return PI*radius*radius;}
double Circle::getX() const{return x;}
double Circle::getY() const{return y;}
double Circle::getTotalArea(){return totalArea;}
double Circle::getTotalPerimeter(){return totalPerimeter;}

Circle & Circle::operator ++ (){
	++x;
	++y;
	return *this;
}

Circle & Circle::operator ++ (int ignoreMe){
	Circle * temp = new Circle;
	*temp = *this;
	++x;
	++y;
	return *temp;
}

Circle & Circle::operator -- (){
	--x;
	--y;
	return *this;
}

Circle & Circle::operator -- (int ignoreMe){
	Circle * temp = new Circle;
	*temp = *this;
	--x;
	--y;
	return *temp;
}

const Circle Circle::operator + (double mySize) const{
	Circle temp = *this;
	temp.radius = ((temp.radius+mySize < 1) ? 1 : temp.radius+mySize);
	return temp;
}

const Circle Circle::operator - (double mySize) const{
	Circle temp = *this;
	temp.radius = ((temp.radius-mySize < 1) ? 1 : temp.radius-mySize);
	return temp;
}

const Circle operator + (double mySize, const Circle & myCircle){
	Circle temp = myCircle;
	temp.radius = ((temp.radius+mySize < 1) ? 1 : temp.radius+mySize);
	return temp;
}

const Circle operator - (double mySize, const Circle & myCircle){
	Circle temp = myCircle;
	temp.radius = ((temp.radius-mySize < 1) ? 1 : temp.radius-mySize);
	return temp;
}

ostream & Circle::printOut(ostream & print) const{
	print << "Your circle has a radius of " << getRadius() << ", has a perimeter length of "
		  << fixed << setprecision(2) << getPerimeter() << " and the area is " << getArea() << "." << endl;
	return print;
}

ofstream & Circle::draw(ofstream & file) const{
	file.open("circle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << getRadius()*2 << R"(" height=")" << getRadius()*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<circle cx = ")" << getRadius() << R"(" cy = ")" << getRadius() << R"(" r = ")" << getRadius() << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

ofstream & Circle::drawContainer(ofstream & file) const{
	file << '\t' << R"(<circle cx = ")" << getRadius() << R"(" cy = ")" << getRadius() << R"(" r = ")" << getRadius() << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

ofstream & Circle::drawSmall(ofstream & file) const{
	file << '\t' << R"(<circle cx = ")" << getX() << R"(" cy = ")" << getY() << R"(" r = ")" << getRadius() << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

void Circle::isRadiusValid(){
	if (getRadius() < 1){
		cout << "Please enter a valid input for the radius" << endl;
		string str;
		getline(cin,str,'\n');
		int size = str.size();
		if(size == 0){
			setRadius(-1);
			return;
		}
		if(size == 1 && (str[0] > '9' || str[0] < '0')){
			setRadius(-1);
			return;
		}
		for (int i = 0; i < size; ++i){
			if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
				setRadius(-1);
				return;
			}
		}
		int count = 0;
		for (int i = 0; i < size; ++i){
			if(str[i] == '.')
				++count;
			if(count > 1){
				setRadius(-1);
				return;
			}
		}
		int length = stod(str);
		if (length < 1){
			setRadius(-1);
			return;
		}
		setRadius(length);
	}
}
}