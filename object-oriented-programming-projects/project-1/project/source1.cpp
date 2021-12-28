#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#include "source1.h"

double hypotenus (double x1, double y1, double x2, double y2){
	return (sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

void isValid(string & str, int & length, char type){
	int size = str.size();
	if(size == 0){
		notValid(str,length,type);
		return;
	}
	if(size == 1 && (str[0] > '9' || str[0] < '0')){
		notValid(str,length,type);
		return;
	}
	for (int i = 0; i < size; ++i){
		if((str[i] > '9' || str[i] < '0')&&(str[i] != '.')){
			notValid(str,length,type);
			return;
		}
	}
	int count = 0;
	for (int i = 0; i < size; ++i){
		if(str[i] == '.')
			++count;
		if(count > 1){
			notValid(str,length,type);
			return;
		}
	}
	double enteredNum;
	enteredNum = stod(str);
	length = enteredNum;
	if (length < 1){
		notValid(str,length,type);
		return;
	}
}

void notValid(string & str, int & length, char type){
	switch(type){
		case 'w':
			cout << "Enter a valid length for the width" << endl;
			getline(cin,str,'\n');
			isValid(str,length,type);
			break;
		case 'h':
			cout << "Enter a valid length for the height" << endl;
			getline(cin,str,'\n');
			isValid(str,length,type);
			break;
		case 'r':
			cout << "Enter a valid length for the radius" << endl;
			getline(cin,str,'\n');
			isValid(str,length,type);
			break;
		case 'e':
			cout << "Enter a valid length for the edge" << endl;
			getline(cin,str,'\n');
			isValid(str,length,type);
			break;
	}
}

int rectangleInRectangle(int mainWidth, int mainHeight, int smallWidth, int smallHeight, double & restArea){
	int count = 0;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainWidth << R"(" height=")" << mainHeight << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	int i = 0, j = 0;
	file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << mainWidth << R"(" height = ")" << mainHeight << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	int temp;
	if (smallHeight > smallWidth){
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
	}
	int count1 = 0;
	j = 0;
	while (mainHeight - j >= smallHeight){
		i = 0;
		while (mainWidth - i >= smallWidth){
			++count1;
			i += smallWidth;
		}
		j += smallHeight;
	}
	int k = 0;
	while (mainWidth - k >= smallWidth)
		k += smallWidth;
	temp = smallWidth;
	smallWidth = smallHeight;
	smallHeight = temp;
	j = 0;
	while (mainHeight - j >= smallHeight){
		i = k;
		while (mainWidth - i >= smallWidth){
			++count1;
			i += smallWidth;
		}
		j += smallHeight;
	}
	int count2 = 0;
	j = 0;
	while (mainHeight - j >= smallHeight){
		i = 0;
		while (mainWidth - i >= smallWidth){
			++count2;
			i += smallWidth;
		}
		j += smallHeight;
	}
	k = 0;
	while (mainHeight - k >= smallHeight)
		k += smallHeight;
	temp = smallWidth;
	smallWidth = smallHeight;
	smallHeight = temp;
	j = k;
	while (mainHeight - j >= smallHeight){
		i = 0;
		while (mainWidth - i >= smallWidth){
			++count2;
			i += smallWidth;
		}
		j += smallHeight;
	}
	if (count1 > count2){
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallWidth;
			}
			j += smallHeight;
		}
		int k = 0;
		while (mainWidth - k >= smallWidth)
			k += smallWidth;
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = k;
			while (mainWidth - i >= smallWidth){
				file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	else{
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallWidth;
			}
			j += smallHeight;
		}
		k = 0;
		while (mainHeight - k >= smallHeight)
			k += smallHeight;
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		j = k;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	file << "</svg>";
	file.close();
	restArea = mainWidth*mainHeight - count*smallWidth*smallHeight;
	return count;
}

int circleInRectangle(int mainWidth, int mainHeight, int smallRadius, double & restArea){
	int count = 0;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainWidth << R"(" height=")" << mainHeight << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	int i = 0, j = 0;
	file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << mainWidth << R"(" height = ")" << mainHeight << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double distance = smallRadius*sqrt(3.0);
	int count1 = 0;
	j = smallRadius;
	while (mainHeight - j >= smallRadius){
		i = smallRadius;
		while (mainWidth - i >= smallRadius){
			++count1;
			i += smallRadius*2;
		}
		j += smallRadius*2;
	}
	int count2 = 0;
	j = smallRadius;
	while (mainHeight - j >= smallRadius){
		i = smallRadius;
		while (mainWidth - i >= smallRadius){
			++count2;
			i += smallRadius*2;
		}
		j += distance*2;
	}
	j = smallRadius+distance;
	while (mainHeight - j >= smallRadius){
		i = smallRadius*2;
		while (mainWidth - i >= smallRadius){
			++count2;
			i += smallRadius*2;
		}
		j += distance*2;
	}
	int count3 = 0;
	j = smallRadius;
	while (mainHeight - j >= smallRadius){
		i = smallRadius;
		while (mainWidth - i >= smallRadius){
			++count3;
			i += distance*2;
		}
		j += smallRadius*2;
	}
	j = smallRadius*2;
	while (mainHeight - j >= smallRadius){
		i = smallRadius+distance;
		while (mainWidth - i >= smallRadius){
			++count3;
			i += distance*2;
		}
		j += smallRadius*2;
	}
	if(count1 >= count2 && count1 >= count3){
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallRadius*2;
			}
			j += smallRadius*2;
		}
	}
	else if(count2 >= count1 && count2 >= count3){
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallRadius*2;
			}
			j += distance*2;
		}
		j = smallRadius+distance;
		while (mainHeight - j >= smallRadius){
			i = smallRadius*2;
			while (mainWidth - i >= smallRadius){
				file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallRadius*2;
			}
			j += distance*2;
		}
	}
	else{
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += distance*2;
			}
			j += smallRadius*2;
		}
		j = smallRadius*2;
		while (mainHeight - j >= smallRadius){
			i = smallRadius+distance;
			while (mainWidth - i >= smallRadius){
				file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += distance*2;
			}
			j += smallRadius*2;
		}
	}
	file << "</svg>";
	file.close();
	restArea = mainWidth*mainHeight - count*PI*smallRadius*smallRadius;
	return count;
}

int triangleInRectangle(int mainWidth, int mainHeight, int smallEdge, double & restArea){
	int count = 0;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainWidth << R"(" height=")" << mainHeight << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	double i = 0.0, j = 0.0;
	file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << mainWidth << R"(" height = ")" << mainHeight << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double height = smallEdge*sqrt(3.0)/2.0;
	int count1 = 0;
	j = 0.0;
	while (mainHeight - j >= height){
		i = 0.0;
		while (mainWidth - i >= smallEdge){
			++count1;
			i += smallEdge;
		}
		j += height;
	}
	j = height;
	while (mainHeight - j >= 0){
		i = smallEdge/2.0;
		while (mainWidth - i >= smallEdge){
			++count1;
			i += smallEdge;
		}
		j += height;
	}
	int count2 = 0;
	j = 0.0;
	while (mainHeight - j >= smallEdge){
		i = 0.0;
		while (mainWidth - i >= height){
			++count2;
			i += height;
		}
		j += smallEdge;
	}
	j = smallEdge;
	while (mainHeight - j >= smallEdge/2.0){
		i = 0.0;
		while (mainWidth - i >= height){
			++count2;
			i += height;
		}
		j += smallEdge;
	}
	if (count1 > count2){
		j = 0.0;
		while (mainHeight - j >= height){
			i = 0.0;
			while (mainWidth - i >= smallEdge){
				file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i+smallEdge << ',' << j << ' ' << i+smallEdge/2.0 << ',' << j+height << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallEdge;
			}
			j += height;
		}
		j = height;
		while (mainHeight - j >= 0){
			i = smallEdge/2.0;
			while (mainWidth - i >= smallEdge){
				file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i+smallEdge << ',' << j << ' ' << i+smallEdge/2.0 << ',' << j-height << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallEdge;
			}
			j += height;
		}
	}
	else{
		j = 0.0;
		while (mainHeight - j >= smallEdge){
			i = 0.0;
			while (mainWidth - i >= height){
				file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i << ',' << j+smallEdge << ' ' << i+height << ',' << j+smallEdge/2.0 << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += height;
			}
			j += smallEdge;
		}
		j = smallEdge;
		while (mainHeight - j >= smallEdge/2.0){
			i = 0.0;
			while (mainWidth - i >= height){
				file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i+height << ',' << j-smallEdge/2.0 << ' ' << i+height << ',' << j+smallEdge/2.0 << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += height;
			}
			j += smallEdge;
		}
	}
	file << "</svg>";
	file.close();
	restArea = mainWidth*mainHeight - count*smallEdge*height/2.0;
	return count;
}

int rectangleInCircle(int mainRadius, int smallWidth, int smallHeight, double & restArea){
	int count = 0;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainRadius*2 << R"(" height=")" << mainRadius*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<circle cx = ")" << mainRadius << R"(" cy = ")" << mainRadius << R"(" r = ")" << mainRadius << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double i = 0.0, j = 0.0;
	double iOffset, jOffset;
	iOffset = mainRadius;
	jOffset = mainRadius;
	while (iOffset >= 0)
		iOffset -= smallWidth;
	iOffset += smallWidth;
	while (jOffset >= 0)
		jOffset -= smallHeight;
	jOffset += smallHeight;
	int count1 = 0;
	j = jOffset;
	while (mainRadius*2 - j >= smallHeight){
		i = iOffset;
		while (mainRadius*2 - i >= smallWidth){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
			 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
				++count1;
			}
			i += smallWidth;
		}
		j += smallHeight;
	}
	iOffset = mainRadius + smallWidth/2.0;
	jOffset = mainRadius;
	while (iOffset >= 0)
		iOffset -= smallWidth;
	iOffset += smallWidth;
	while (jOffset >= 0)
		jOffset -= smallHeight;
	jOffset += smallHeight;
	int count2 = 0;
	j = jOffset;
	while (mainRadius*2 - j >= smallHeight){
		i = iOffset;
		while (mainRadius*2 - i >= smallWidth){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
			 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
				++count2;
			}
			i += smallWidth;
		}
		j += smallHeight;
	}
	iOffset = mainRadius;
	jOffset = mainRadius + smallHeight/2.0;
	while (iOffset >= 0)
		iOffset -= smallWidth;
	iOffset += smallWidth;
	while (jOffset >= 0)
		jOffset -= smallHeight;
	jOffset += smallHeight;
	int count3 = 0;
	j = jOffset;
	while (mainRadius*2 - j >= smallHeight){
		i = iOffset;
		while (mainRadius*2 - i >= smallWidth){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
			 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
				++count3;
			}
			i += smallWidth;
		}
		j += smallHeight;
	}
	iOffset = mainRadius + smallWidth/2.0;
	jOffset = mainRadius + smallHeight/2.0;
	while (iOffset >= 0)
		iOffset -= smallWidth;
	iOffset += smallWidth;
	while (jOffset >= 0)
		jOffset -= smallHeight;
	jOffset += smallHeight;
	int count4 = 0;
	j = jOffset;
	while (mainRadius*2 - j >= smallHeight){
		i = iOffset;
		while (mainRadius*2 - i >= smallWidth){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
			 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
				++count4;
			}
			i += smallWidth;
		}
		j += smallHeight;
	}
	if (count1 >= count2 && count1 >= count3 && count1 >= count4){
		iOffset = mainRadius;
		jOffset = mainRadius;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	else if (count2 >= count1 && count2 >= count3 && count2 >= count4){
		iOffset = mainRadius + smallWidth/2.0;
		jOffset = mainRadius;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	else if (count3 >= count1 && count3 >= count2 && count3 >= count4){
		iOffset = mainRadius;
		jOffset = mainRadius + smallHeight/2.0;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	else{
		iOffset = mainRadius + smallWidth/2.0;
		jOffset = mainRadius + smallHeight/2.0;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	file << "</svg>";
	file.close();
	restArea = PI*mainRadius*mainRadius-count*smallWidth*smallHeight;
	return count;
}

int circleInCircle(int mainRadius, int smallRadius, double & restArea){
	int count = 0;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainRadius*2 << R"(" height=")" << mainRadius*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<circle cx = ")" << mainRadius << R"(" cy = ")" << mainRadius << R"(" r = ")" << mainRadius << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double height60 = smallRadius*sqrt(3.0);
	double i = 0.0, j = 0.0;
	i = mainRadius;
	j = smallRadius;
	int count1 = 0;
	while (mainRadius*2 - j >= smallRadius){
		while (i >= smallRadius)
			i -= 2*height60;
		i += 2*height60;
		while (mainRadius*2 - i >= smallRadius){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
				++count1;
			}
			i += 2*height60;
		}
		i += height60;
		j += smallRadius;
	}
	i = mainRadius;
	j = smallRadius;
	int count2 = 0;
	while (mainRadius*2 - j >= smallRadius){
		while (i >= smallRadius)
			i -= 2*smallRadius;
		i += 2*smallRadius;
		while (mainRadius*2 - i >= smallRadius){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
				++count2;
			}
			i += 2*smallRadius;
		}
		i += smallRadius;
		j += height60;
	}
	if (count1 > count2){
		i = mainRadius;
		j = smallRadius;
		while (mainRadius*2 - j >= smallRadius){
			while (i >= smallRadius)
				i -= 2*height60;
			i += 2*height60;
			while (mainRadius*2 - i >= smallRadius){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
					file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += 2*height60;
			}
			i += height60;
			j += smallRadius;
		}
	}
	else{
		i = mainRadius;
		j = smallRadius;
		while (mainRadius*2 - j >= smallRadius){
			while (i >= smallRadius)
				i -= 2*smallRadius;
			i += 2*smallRadius;
			while (mainRadius*2 - i >= smallRadius){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
					file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += 2*smallRadius;
			}
			i += smallRadius;
			j += height60;
		}
	}
	file << "</svg>";
	file.close();
	restArea = PI*(mainRadius*mainRadius-count*smallRadius*smallRadius);
	return count;
}

int triangleInCircle(int mainRadius, int smallEdge, double & restArea){
	int count = 0;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainRadius*2 << R"(" height=")" << mainRadius*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<circle cx = ")" << mainRadius << R"(" cy = ")" << mainRadius << R"(" r = ")" << mainRadius << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double height60 = smallEdge*sqrt(3.0)/2;
	double i = 0.0, j = 0.0;
	i = mainRadius;
	j = 0.0;
	int count1 = 0;
	while (i >= smallEdge/2.0)
		i -= smallEdge;
	i += smallEdge;
	while (mainRadius*2 - j >= height60){
		while (i >= smallEdge/2.0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - i >= smallEdge/2.0){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius){
				++count1;
			}
			i += smallEdge;
		}
		i += smallEdge/2.0;
		j += height60;
	}
	i = mainRadius;
	j = 0.0;
	while (i >= 0)
		i -= smallEdge;
	i += smallEdge;
	while (mainRadius*2 - j >= height60){
		while (i >= 0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - i >= smallEdge){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
				++count1;
			}
			i += smallEdge;
		}
		i += smallEdge/2.0;
		j += height60;
	}
	i = mainRadius;
	j = mainRadius;
	int count2 = 0;
	while (j >= 0){
		i -= smallEdge/2.0;
		j -= height60;
	}
	i += smallEdge/2.0;
	j += height60;
	while (i >= smallEdge/2.0)
		i -= smallEdge;
	i += smallEdge;
	while (mainRadius*2 - j >= height60){
		while (i >= smallEdge/2.0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - i >= smallEdge/2.0){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius){
				++count2;
			}
			i += smallEdge;
		}
		i += smallEdge/2.0;
		j += height60;
	}
	i = mainRadius;
	j = mainRadius;
	while (j >= 0){
		i -= smallEdge/2.0;
		j -= height60;
	}
	i += smallEdge/2.0;
	j += height60;
	while (i >= 0)
		i -= smallEdge;
	i += smallEdge;
	while (mainRadius*2 - j >= height60){
		while (i >= 0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - i >= smallEdge){
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
				++count2;
			}
			i += smallEdge;
		}
		i += smallEdge/2.0;
		j += height60;
	}
	if (count1 > count2){
		i = mainRadius;
		j = 0.0;
		while (i >= smallEdge/2.0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= smallEdge/2.0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge/2.0){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i-smallEdge/2 << ',' << j+height60 << ' ' << i+smallEdge/2 << ',' << j+height60 << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
		i = mainRadius;
		j = 0.0;
		while (i >= 0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= 0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i+smallEdge/2 << ',' << j+height60 << ' ' << i+smallEdge << ',' << j << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
	}
	else{
		i = mainRadius;
		j = mainRadius;
		while (j >= 0){
			i -= smallEdge/2.0;
			j -= height60;
		}
		i += smallEdge/2.0;
		j += height60;
		while (i >= smallEdge/2.0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= smallEdge/2.0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge/2.0){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i-smallEdge/2 << ',' << j+height60 << ' ' << i+smallEdge/2 << ',' << j+height60 << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
		i = mainRadius;
		j = mainRadius;
		while (j >= 0){
			i -= smallEdge/2.0;
			j -= height60;
		}
		i += smallEdge/2.0;
		j += height60;
		while (i >= 0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= 0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i+smallEdge/2 << ',' << j+height60 << ' ' << i+smallEdge << ',' << j << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
					++count;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
	}
	file << "</svg>";
	file.close();
	restArea = PI*mainRadius*mainRadius-count*smallEdge*height60/2.0;
	return count;
}

int rectangleInTriangle(int mainEdge, int smallWidth, int smallHeight, double & restArea){
	int count = 0;
	double mainHeight = mainEdge*sqrt(3.0)/2;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainEdge << R"(" height=")" << mainHeight << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")" << 0 << ',' << mainHeight << ' ' << mainEdge/2.0 << ',' << 0 << ' ' << mainEdge << ',' << mainHeight << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = smallHeight/sqrt(3.0);
	iWall = mainEdge - smallHeight/sqrt(3.0);
	int count1 = 0;
	j = mainHeight - smallHeight;
	while (j >= 0){
		i = iOffset;
		while (i <= iWall-smallWidth){
			++count1;
			i += smallWidth;
		}
		iOffset += smallHeight/sqrt(3.0);
		iWall -= smallHeight/sqrt(3.0);
		j -= smallHeight;
	}
	int temp;
	temp = smallWidth;
	smallWidth = smallHeight;
	smallHeight = temp;
	iOffset = smallHeight/sqrt(3.0);
	iWall = mainEdge - smallHeight/sqrt(3.0);
	int count2 = 0;
	j = mainHeight - smallHeight;
	while (j >= 0){
		i = iOffset;
		while (i <= iWall-smallWidth){
			++count2;
			i += smallWidth;
		}
		iOffset += smallHeight/sqrt(3.0);
		iWall -= smallHeight/sqrt(3.0);
		j -= smallHeight;
	}
	if (count1 > count2){
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		iOffset = smallHeight/sqrt(3.0);
		iWall = mainEdge - smallHeight/sqrt(3.0);
		j = mainHeight - smallHeight;
		while (j >= 0){
			i = iOffset;
			while (i <= iWall-smallWidth){
				file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallWidth;
			}
			iOffset += smallHeight/sqrt(3.0);
			iWall -= smallHeight/sqrt(3.0);
			j -= smallHeight;
		}
	}
	else{
		iOffset = smallHeight/sqrt(3.0);
		iWall = mainEdge - smallHeight/sqrt(3.0);
		j = mainHeight - smallHeight;
		while (j >= 0){
			i = iOffset;
			while (i <= iWall-smallWidth){
				file << '\t' << R"(<rect x = ")" << i << R"(" y = ")" << j << R"(" width = ")" << smallWidth << R"(" height = ")" << smallHeight << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
				++count;
				i += smallWidth;
			}
			iOffset += smallHeight/sqrt(3.0);
			iWall -= smallHeight/sqrt(3.0);
			j -= smallHeight;
		}
	}
	file << "</svg>";
	file.close();
	restArea = mainEdge*mainEdge*sqrt(3.0)/4.0 - count*smallHeight*smallWidth;
	return count;
}

int circleInTriangle(int mainEdge, int smallRadius, double & restArea){
	int count = 0;
	double mainHeight = mainEdge*sqrt(3.0)/2;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainEdge << R"(" height=")" << mainHeight << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")" << 0 << ',' << mainHeight << ' ' << mainEdge/2.0 << ',' << 0 << ' ' << mainEdge << ',' << mainHeight << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = smallRadius*sqrt(3.0);
	iWall = mainEdge;
	j = mainHeight - smallRadius;
	while (j >= smallRadius*2){
		i = iOffset;
		while (iWall - i >= smallRadius*sqrt(3.0)){
			file << '\t' << R"(<circle cx = ")" << i << R"(" cy = ")" << j << R"(" r = ")" << smallRadius << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
			++count;
			i += smallRadius*2;
		}
		iOffset += smallRadius;
		iWall -= smallRadius;
		j -= smallRadius*sqrt(3.0);
	}
	file << "</svg>";
	file.close();
	restArea = mainEdge*mainEdge*sqrt(3.0)/4.0 - count*PI*smallRadius*smallRadius;
	return count;
}

int triangleInTriangle(int mainEdge, int smallEdge, double & restArea){
	int count = 0;
	double mainHeight = mainEdge*sqrt(3.0)/2;
	double smallHeight = smallEdge*sqrt(3.0)/2;
	ofstream file;
	file.open("output.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << mainEdge << R"(" height=")" << mainHeight << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	file << '\t' << R"(<polygon points = ")" << 0 << ',' << mainHeight << ' ' << mainEdge/2.0 << ',' << 0 << ' ' << mainEdge << ',' << mainHeight << R"(" fill = "pink" stroke = "black" stroke-width = "1" />)" << endl;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = 0.0;
	iWall = mainEdge;
	j = mainHeight;
	while (j >= smallHeight){
		i = iOffset;
		while (i <= iWall-smallEdge){
			file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i + smallEdge/2.0 << ',' << j - smallHeight << ' ' << i + smallEdge << ',' << j << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
			++count;
			i += smallEdge;
		}
		iOffset += smallEdge/2.0;
		iWall -= smallEdge/2.0;
		j -= smallHeight;
	}
	iOffset = smallEdge/2.0;
	iWall = mainEdge - smallEdge/2.0;
	j = mainHeight - smallHeight;
	while (j >= smallHeight){
		i = iOffset;
		while (i <= iWall-smallEdge){
			file << '\t' << R"(<polygon points = ")" << i << ',' << j << ' ' << i + smallEdge/2.0 << ',' << j + smallHeight << ' ' << i + smallEdge << ',' << j << R"(" fill = "purple" stroke = "black" stroke-width = "1" />)" << endl;
			++count;
			i += smallEdge;
		}
		iOffset += smallEdge/2.0;
		iWall -= smallEdge/2.0;
		j -= smallHeight;
	}
	file << "</svg>";
	file.close();
	restArea = (mainEdge*mainEdge - count*smallEdge*smallEdge)*sqrt(3.0)/4.0;
	return count;
}