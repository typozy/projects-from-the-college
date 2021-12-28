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

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stod;

namespace SpaceRectangle
{
Rectangle::Rectangle():Rectangle(5,5){}
Rectangle::Rectangle(int myWidth, int myHeight)
	:width(myWidth),height(myHeight),x(0.0),y(0.0){
		if (width < 1) throw MyErrors(-3);
		if (height < 1) throw MyErrors(-4);
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Rectangle::Rectangle(int myWidth, int myHeight, double myX, double myY)
	:width(myWidth),height(myHeight),x(myX),y(myY){
		if (width < 1) throw MyErrors(-3);
		if (height < 1) throw MyErrors(-4);
		totalArea += getArea();
		totalPerimeter += getPerimeter();
	}
Rectangle::Rectangle(const Rectangle & other){
	width = other.width;
	height = other.height;
	x = other.x;
	y = other.y;
	totalArea += other.getArea();
	totalPerimeter += other.getPerimeter();
}
Rectangle & Rectangle::operator = (const Rectangle & other){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	width = other.width;
	height = other.height;
	x = other.x;
	y = other.y;
	totalArea += other.getArea();
	totalPerimeter += other.getPerimeter();
	return *this;
}
Rectangle::~Rectangle(){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
}
void Rectangle::setWidth(int myWidth){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	width = myWidth;
	isWidthValid();
	totalArea += getArea();
	totalPerimeter += getPerimeter();
}
void Rectangle::setHeight(int myHeight){
	totalArea -= getArea();
	totalPerimeter -= getPerimeter();
	height = myHeight;
	isHeightValid();
	totalArea += getArea();
	totalPerimeter += getPerimeter();
}
void Rectangle::setX(double myX){x = myX;}
void Rectangle::setY(double myY){y = myY;}
int Rectangle::getWidth() const{return width;}
int Rectangle::getHeight() const{return height;}
double Rectangle::getPerimeter() const{return 2.0*width+2.0*height;}
double Rectangle::getArea() const{return width*height;}
double Rectangle::getX() const{return x;}
double Rectangle::getY() const{return y;}
double Rectangle::getTotalArea(){return totalArea;}
double Rectangle::getTotalPerimeter(){return totalPerimeter;}

Rectangle & Rectangle::operator ++ (){
	++x;
	++y;
	return *this;
}

Rectangle & Rectangle::operator ++ (int ignoreMe){
	Rectangle * temp = new Rectangle;
	*temp = *this;
	++x;
	++y;
	return *temp;
}

Rectangle & Rectangle::operator -- (){
	--x;
	--y;
	return *this;
}

Rectangle & Rectangle::operator -- (int ignoreMe){
	Rectangle * temp = new Rectangle;
	*temp = *this;
	--x;
	--y;
	return *temp;
}

const Rectangle Rectangle::operator + (double mySize) const{
	Rectangle temp = *this;
	temp.width = ((temp.width+mySize < 1) ? 1 : temp.width+mySize);
	temp.height = ((temp.height+mySize < 1) ? 1 : temp.height+mySize);
	return temp;
}

const Rectangle Rectangle::operator - (double mySize) const{
	Rectangle temp = *this;
	temp.width = ((temp.width-mySize < 1) ? 1 : temp.width-mySize);
	temp.height = ((temp.height-mySize < 1) ? 1 : temp.height-mySize);
	return temp;
}

const Rectangle operator + (double mySize, const Rectangle & myRectangle){
	Rectangle temp = myRectangle;
	temp.width = ((temp.width+mySize < 1) ? 1 : temp.width+mySize);
	temp.height = ((temp.height+mySize < 1) ? 1 : temp.height+mySize);
	return temp;
}

const Rectangle operator - (double mySize, const Rectangle & myRectangle){
	Rectangle temp = myRectangle;
	temp.width = ((temp.width-mySize < 1) ? 1 : temp.width-mySize);
	temp.height = ((temp.height-mySize < 1) ? 1 : temp.height-mySize);
	return temp;
}

ostream & Rectangle::printOut(ostream & print) const{
	print << "Your rectangle has a width of " << getWidth() << " and has a height of " 
		  << getHeight() << ", has a perimeter length of "
		  << static_cast <int> (getPerimeter()) << " and the area is " << getArea() << "." << endl;
	return print;
}

ofstream & Rectangle::draw(ofstream & file) const{
	file.open("rectangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << getWidth() << R"(" height=")" << getHeight() << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<rect x = ")" << 0 << R"(" y = ")" << 0 << R"(" width = ")" << getWidth() << R"(" height = ")" << getHeight() << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	file << "</svg>";
	file.close();
	return file;
}

ofstream & Rectangle::drawContainer(ofstream & file) const{
	file << '\t' << R"(<rect x = ")" << 0 << R"(" y = ")" << 0 << R"(" width = ")" << getWidth() << R"(" height = ")" << getHeight() << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

ofstream & Rectangle::drawSmall(ofstream & file) const{
	file << '\t' << R"(<rect x = ")" << getX() << R"(" y = ")" << getY() << R"(" width = ")" << getWidth() << R"(" height = ")" << getHeight() << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
	return file;
}

void Rectangle::isWidthValid(){
	if (getWidth() < 1){
		cout << "Please enter a valid input for the width" << endl;
		string str;
		getline(cin,str,'\n');
		int size = str.size();
		if(size == 0){
			setWidth(-1);
			return;
		}
		if(size == 1 && (str[0] > '9' || str[0] < '0')){
			setWidth(-1);
			return;
		}
		for (int i = 0; i < size; ++i){
			if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
				setWidth(-1);
				return;
			}
		}
		int count = 0;
		for (int i = 0; i < size; ++i){
			if(str[i] == '.')
				++count;
			if(count > 1){
				setWidth(-1);
				return;
			}
		}
		int length = stod(str);
		if (length < 1){
			setWidth(-1);
			return;
		}
		setWidth(length);
	}
}

void Rectangle::isHeightValid(){
	if (getHeight() < 1){
		cout << "Please enter a valid input for the height" << endl;
		string str;
		getline(cin,str,'\n');
		int size = str.size();
		if(size == 0){
			setHeight(-1);
			return;
		}
		if(size == 1 && (str[0] > '9' || str[0] < '0')){
			setHeight(-1);
			return;
		}
		for (int i = 0; i < size; ++i){
			if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
				setHeight(-1);
				return;
			}
		}
		int count = 0;
		for (int i = 0; i < size; ++i){
			if(str[i] == '.')
				++count;
			if(count > 1){
				setHeight(-1);
				return;
			}
		}
		int length = stod(str);
		if (length < 1){
			setHeight(-1);
			return;
		}
		setHeight(length);
	}
}
}