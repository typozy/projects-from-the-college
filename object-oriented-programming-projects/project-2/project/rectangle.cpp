#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "rectangle.h"

Rectangle::Rectangle()
	:width(1),height(1),x(0.0),y(0.0){}
Rectangle::Rectangle(int myWidth, int myHeight)
	:width(myWidth),height(myHeight),x(0.0),y(0.0){
		isWidthValid();
		isHeightValid();
	}
Rectangle::Rectangle(int myWidth, int myHeight, double myX, double myY)
	:width(myWidth),height(myHeight),x(myX),y(myY){
		isWidthValid();
		isHeightValid();
	}
void Rectangle::setWidth(int myWidth){width = myWidth; isWidthValid();}
void Rectangle::setHeight(int myHeight){height = myHeight; isHeightValid();}
void Rectangle::setX(double myX){x = myX;}
void Rectangle::setY(double myY){y = myY;}
int Rectangle::getWidth() const{return width;}
int Rectangle::getHeight() const{return height;}
double Rectangle::getX() const{return x;}
double Rectangle::getY() const{return y;}

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