#include <iostream>
#include <iomanip>

using namespace std;

#include "source1.h"

int main(){
	shape mainShape;
	cout << "Please enter the main container shape (R, C, T)" << endl;
	string temp;
	getline(cin,temp,'\n');
	while (temp != "R" && temp != "C" && temp != "T" && temp != "r" && temp != "c" && temp != "t"){
		cout << "Please enter the right shape code for the main container shape" << endl;
		getline(cin,temp,'\n');
	}
	char tempchar = temp[0];
	switch (tempchar){
		case 'R':
		case 'r':
			mainShape = shape::rectangle;
			break;
		case 'C':
		case 'c':
			mainShape = shape::circle;
			break;
		case 'T':
		case 't':
			mainShape = shape::triangle;
			break;
	}
	int mainWidth, mainHeight, mainRadius, mainEdge;
	switch (mainShape){
		case shape::rectangle:
			cout << "Please enter the width" << endl;
			getline(cin,temp,'\n');
			isValid(temp,mainWidth,'w');
			cout << "Please enter the height" << endl;
			getline(cin,temp,'\n');
			isValid(temp,mainHeight,'h');
			break;
		case shape::circle:
			cout << "Please enter the radius" << endl;
			getline(cin,temp,'\n');
			isValid(temp,mainRadius,'r');
			break;
		case shape::triangle:
			cout << "Please enter the length of an edge" << endl;
			getline(cin,temp,'\n');
			isValid(temp,mainEdge,'e');
			break;
	}
	shape smallShape;
	cout << "Please enter the small shape (R, C, T)" << endl;
	getline(cin,temp,'\n');
	while (temp != "R" && temp != "C" && temp != "T" && temp != "r" && temp != "c" && temp != "t"){
		cout << "Please enter the right shape code for the small shape" << endl;
		getline(cin,temp,'\n');
	}
	tempchar = temp[0];
	switch (tempchar){
		case 'R':
		case 'r':
			smallShape = shape::rectangle;
			break;
		case 'C':
		case 'c':
			smallShape = shape::circle;
			break;
		case 'T':
		case 't':
			smallShape = shape::triangle;
			break;
	}
	int smallWidth, smallHeight, smallRadius, smallEdge;
	switch (smallShape){
		case shape::rectangle:
			cout << "Please enter the width" << endl;
			getline(cin,temp,'\n');
			isValid(temp,smallWidth,'w');
			cout << "Please enter the height" << endl;
			getline(cin,temp,'\n');
			isValid(temp,smallHeight,'h');
			break;
		case shape::circle:
			cout << "Please enter the radius" << endl;
			getline(cin,temp,'\n');
			isValid(temp,smallRadius,'r');
			break;
		case shape::triangle:
			cout << "Please enter the length of an edge" << endl;
			getline(cin,temp,'\n');
			isValid(temp,smallEdge,'e');
			break;
	}
	int count;
	double restArea;
	if (mainShape == shape::rectangle && smallShape == shape::rectangle){
		count = rectangleInRectangle(mainWidth, mainHeight, smallWidth, smallHeight, restArea);
	}
	else if (mainShape == shape::rectangle && smallShape == shape::circle){
		count = circleInRectangle(mainWidth, mainHeight, smallRadius, restArea);
	}
	else if (mainShape == shape::rectangle && smallShape == shape::triangle){
		count = triangleInRectangle(mainWidth, mainHeight, smallEdge, restArea);
	}
	else{
		if (mainShape == shape::circle && smallShape == shape::rectangle){
			count = rectangleInCircle(mainRadius, smallWidth, smallHeight, restArea);
		}
		else if (mainShape == shape::circle && smallShape == shape::circle){
			count = circleInCircle(mainRadius, smallRadius, restArea);
		}
		else if (mainShape == shape::circle && smallShape == shape::triangle){
			count = triangleInCircle(mainRadius, smallEdge, restArea);
		}
		else{
			if (mainShape == shape::triangle && smallShape == shape::rectangle){
				count = rectangleInTriangle(mainEdge, smallWidth, smallHeight, restArea);
			}
			else if (mainShape == shape::triangle && smallShape == shape::circle){
				count = circleInTriangle(mainEdge, smallRadius, restArea);
			}
			else if (mainShape == shape::triangle && smallShape == shape::triangle){
				count = triangleInTriangle(mainEdge, smallEdge, restArea);
			}
		}
	}
	cout << "I can fit at most " << count << " small shapes into the main container. The empty area (pink) in container is " << fixed << setprecision(2) << restArea << '.' << endl;
	return 0;
}