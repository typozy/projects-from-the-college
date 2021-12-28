#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "circle.h"

Circle::Circle()
	:radius(1),x(0.0),y(0.0){}
Circle::Circle(int myRadius)
	:radius(myRadius),x(0.0),y(0.0){
		isRadiusValid();
	}
Circle::Circle(int myRadius, double myX, double myY)
	:radius(myRadius),x(myX),y(myY){
		isRadiusValid();
	}
void Circle::setRadius(int myRadius){radius = myRadius; isRadiusValid();}
void Circle::setX(double myX){x = myX;}
void Circle::setY(double myY){y = myY;}
int Circle::getRadius() const{return radius;}
double Circle::getX() const{return x;}
double Circle::getY() const{return y;}

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