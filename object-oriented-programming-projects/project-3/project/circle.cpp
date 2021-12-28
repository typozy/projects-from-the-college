#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "attribute.h"
#include "circle.h"

Circle::Circle()
	:radius(1),x(0.0),y(0.0){
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Circle::Circle(int myRadius)
	:radius(myRadius),x(0.0),y(0.0){
		isRadiusValid();
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Circle::Circle(int myRadius=1, double myX=0.0, double myY=0.0)
	:radius(myRadius),x(myX),y(myY){
		isRadiusValid();
		totalArea += getArea();
		totalPerimeter += getPerimeter();
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

Circle Circle::operator ++ (){
	++x;
	++y;
	return *this;
}

Circle Circle::operator ++ (int ignoreMe){
	Circle temp = *this;
	++x;
	++y;
	return temp;
}

Circle Circle::operator -- (){
	--x;
	--y;
	return *this;
}

Circle Circle::operator -- (int ignoreMe){
	Circle temp = *this;
	--x;
	--y;
	return temp;
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

bool Circle::operator == (const Circle & other) const{return (getRadius() == other.getRadius());}
bool Circle::operator != (const Circle & other) const{return (getArea() != other.getArea());}
bool Circle::operator < (const Circle & other) const{return (getArea() < other.getArea());}
bool Circle::operator > (const Circle & other) const{return (getArea() > other.getArea());}
bool Circle::operator <= (const Circle & other) const{return (getArea() <= other.getArea());}
bool Circle::operator >= (const Circle & other) const{return (getArea() >= other.getArea());}

ostream & operator << (ostream & print, const Circle & smallShape){
	print << "Your circle has a radius of " << smallShape.getRadius() << ", has a perimeter length of "
		  << fixed << setprecision(2) << smallShape.getPerimeter() << " and the area is " << smallShape.getArea() << "." << endl;
	return print;
}

ofstream & operator << (ofstream & file, const Circle & smallShape){
	file.open("circle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << smallShape.getRadius()*2 << R"(" height=")" << smallShape.getRadius()*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<circle cx = ")" << smallShape.getRadius() << R"(" cy = ")" << smallShape.getRadius() << R"(" r = ")" << smallShape.getRadius() << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

ofstream & Circle::drawContainer(ofstream & file) const{
	file << R"(<svg version="1.1" baseProfile="full" width=")" << getRadius()*2 << R"(" height=")" << getRadius()*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
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