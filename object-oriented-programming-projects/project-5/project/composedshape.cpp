#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <typeinfo>

#include "myerrors.h"

using std::ostream;
using std::ofstream;
using std::vector;

#include "shape.h"

using SpaceShape::Shape;

#include "rectangle.h"
#include "triangle.h"
#include "circle.h"

using SpaceRectangle::Rectangle;
using SpaceCircle::Circle;
using SpaceTriangle::Triangle;

#include "composedshape.h"

using std::endl;
using std::string;
using std::fixed;
using std::setprecision;

namespace {
	double hypotenus(double x1, double y1, double x2, double y2){
		return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	}
}

namespace SpaceComposedShape
{
ComposedShape & ComposedShape::operator += (Shape * smallShape){
	mySmallShapes.push_back(smallShape);
	restContainerArea -= smallShape->getArea();
	return *this;
}

const Shape * ComposedShape::operator [] (int index) const{
	if (index < 0 || index >= mySmallShapes.size()) throw MyErrors(-1);
	return mySmallShapes[index];
}

Shape * ComposedShape::operator [] (int index){
	if (index < 0 || index >= mySmallShapes.size()) throw MyErrors(-1);
	return mySmallShapes[index];
}

vector<Shape*> ComposedShape::getSmallShapes() const{return mySmallShapes;}
double ComposedShape::getRestArea() const{return restContainerArea;};
int ComposedShape::getTotalSmallShapes() const{return mySmallShapes.size();};

ostream & ComposedShape::printOut(ostream & print) const{
	string c = typeid(*myContainerShape).name();
	print << "Your container ";
	if (c == "N14SpaceRectangle9RectangleE") print << "rectangle";
	else if (c == "N11SpaceCircle6CircleE") print << "circle";
	else if (c == "N13SpaceTriangle8TriangleE") print << "triangle";
	else print << "shape";
	print << " holds " << mySmallShapes.size() << " small ";
	print << ((mySmallShapes.size() > 1) ? "shapes" : "shape");
	print << ". The rest area is " << fixed << setprecision(2) << restContainerArea << "." << endl;
	return print;
}

ofstream & ComposedShape::draw(ofstream & file) const{
	string c = typeid(*myContainerShape).name();
	if (mySmallShapes.size() < 1){
		if (c == "N14SpaceRectangle9RectangleE") file.open("containerrectangle.svg");
		else if (c == "N11SpaceCircle6CircleE") file.open("containercircle.svg");
		else if (c == "N13SpaceTriangle8TriangleE") file.open("containertriangle.svg");
		else file.open("containershape.svg");
	}
	else{
		string s = typeid(*(mySmallShapes[0])).name();
		if (c == "N14SpaceRectangle9RectangleE" && s == "N14SpaceRectangle9RectangleE") file.open("rectanglesinrectangle.svg");
		else if (c == "N14SpaceRectangle9RectangleE" && s == "N11SpaceCircle6CircleE") file.open("circlesinrectangle.svg");
		else if (c == "N14SpaceRectangle9RectangleE" && s == "N13SpaceTriangle8TriangleE") file.open("trianglesinrectangle.svg");
		else if (c == "N11SpaceCircle6CircleE" && s == "N14SpaceRectangle9RectangleE") file.open("rectanglesincircle.svg");
		else if (c == "N11SpaceCircle6CircleE" && s == "N11SpaceCircle6CircleE") file.open("circlesincircle.svg");
		else if (c == "N11SpaceCircle6CircleE" && s == "N13SpaceTriangle8TriangleE") file.open("trianglesincircle.svg");
		else if (c == "N13SpaceTriangle8TriangleE" && s == "N14SpaceRectangle9RectangleE") file.open("rectanglesintriangle.svg");
		else if (c == "N13SpaceTriangle8TriangleE" && s == "N11SpaceCircle6CircleE") file.open("circlesintriangle.svg");
		else if (c == "N13SpaceTriangle8TriangleE" && s == "N13SpaceTriangle8TriangleE") file.open("trianglesintriangle.svg");
		else file.open("shapesincontainer.svg");
	}
	file << R"(<svg version="1.1" baseProfile="full" width="100%" height="100%" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	if (myContainerShape != nullptr)
		myContainerShape->drawContainer(file);
	for (int i = 0; i < mySmallShapes.size(); ++i)
		if (mySmallShapes[i] != nullptr)
			mySmallShapes[i]->drawSmall(file);
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawSmall(ofstream & file) const{
	if (myContainerShape != nullptr)
		myContainerShape->drawContainer(file);
	for (int i = 0; i < mySmallShapes.size(); ++i)
		if (mySmallShapes[i] != nullptr)
			mySmallShapes[i]->drawSmall(file);
	return file;
}

void ComposedShape::clearComposedShape(){
	if (myContainerShape != nullptr){
		delete myContainerShape;
		myContainerShape = nullptr;
	}
	for (int i = 0; i < mySmallShapes.size(); ++i)
		if (mySmallShapes[i] != nullptr)
			delete mySmallShapes[i];
	mySmallShapes.clear();
}

ComposedShape::ComposedShape()
	:myContainerShape(nullptr){
	optimalFit(Rectangle(1920,1080),Rectangle(2000,1500));
	}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Rectangle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);
}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Circle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Triangle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Rectangle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Circle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Triangle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Rectangle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Circle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Triangle & smallShape)
	:myContainerShape(nullptr){
	optimalFit(containerShape,smallShape);
}

ComposedShape::~ComposedShape(){
	clearComposedShape();
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Rectangle & smallShape){
	clearComposedShape();
	Rectangle * containerRectangle = new Rectangle(containerShape);
	myContainerShape = containerRectangle;
	int mainHeight = containerShape.getHeight();
	int mainWidth = containerShape.getWidth();
	int smallHeight = smallShape.getHeight();
	int smallWidth = smallShape.getWidth();
	restContainerArea = containerShape.getArea();
	int i = 0, j = 0;
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
	Rectangle * smallRectangles;
	if (count1 > count2){
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
				*this += smallRectangles;
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
				smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
				*this += smallRectangles;
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
				smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
				*this += smallRectangles;
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
				smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
				*this += smallRectangles;
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Circle & smallShape){
	clearComposedShape();
	Rectangle * containerRectangle = new Rectangle(containerShape);
	myContainerShape = containerRectangle;
	int mainHeight = containerShape.getHeight();
	int mainWidth = containerShape.getWidth();
	int smallRadius = smallShape.getRadius();
	double distance = smallRadius*sqrt(3.0);
	restContainerArea = containerShape.getArea();
	double i = 0.0, j = 0.0;
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
	Circle * smallCircles;
	if(count1 >= count2 && count1 >= count3){
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				smallCircles = new Circle(smallRadius,i,j);
				*this += smallCircles;
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
				smallCircles = new Circle(smallRadius,i,j);
				*this += smallCircles;
				i += smallRadius*2;
			}
			j += distance*2;
		}
		j = smallRadius+distance;
		while (mainHeight - j >= smallRadius){
			i = smallRadius*2;
			while (mainWidth - i >= smallRadius){
				smallCircles = new Circle(smallRadius,i,j);
				*this += smallCircles;
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
				smallCircles = new Circle(smallRadius,i,j);
				*this += smallCircles;
				i += distance*2;
			}
			j += smallRadius*2;
		}
		j = smallRadius*2;
		while (mainHeight - j >= smallRadius){
			i = smallRadius+distance;
			while (mainWidth - i >= smallRadius){
				smallCircles = new Circle(smallRadius,i,j);
				*this += smallCircles;
				i += distance*2;
			}
			j += smallRadius*2;
		}
	}
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Triangle & smallShape){
	clearComposedShape();
	Rectangle * containerRectangle = new Rectangle(containerShape);
	myContainerShape = containerRectangle;
	int mainWidth = containerShape.getWidth();
	int mainHeight = containerShape.getHeight();
	int smallEdge = smallShape.getEdge();
	restContainerArea = containerShape.getArea();
	double i = 0.0, j = 0.0;
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
	Triangle * smallTriangles;
	if (count1 > count2){
		j = 0.0;
		while (mainHeight - j >= height){
			i = 0.0;
			while (mainWidth - i >= smallEdge){
				smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j+height);
				*this += smallTriangles;
				i += smallEdge;
			}
			j += height;
		}
		j = height;
		while (mainHeight - j >= 0){
			i = smallEdge/2.0;
			while (mainWidth - i >= smallEdge){
				smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j-height);
				*this += smallTriangles;
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
				smallTriangles = new Triangle(smallEdge,i,j,i,j+smallEdge,i+height,j+smallEdge/2.0);
				*this += smallTriangles;
				i += height;
			}
			j += smallEdge;
		}
		j = smallEdge;
		while (mainHeight - j >= smallEdge/2.0){
			i = 0.0;
			while (mainWidth - i >= height){
				smallTriangles = new Triangle(smallEdge,i,j,i+height,j-smallEdge/2.0,i+height,j+smallEdge/2.0);
				*this += smallTriangles;
				i += height;
			}
			j += smallEdge;
		}
	}
}

void ComposedShape::optimalFit(const Circle & containerShape, const Rectangle & smallShape){
	clearComposedShape();
	Circle * containerCircle = new Circle(containerShape);
	myContainerShape = containerCircle;
	int mainRadius = containerShape.getRadius();
	int smallWidth = smallShape.getWidth();
	int smallHeight = smallShape.getHeight();
	restContainerArea = containerShape.getArea();
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
	Rectangle * smallRectangles;
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
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					*this += smallRectangles;
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
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					*this += smallRectangles;
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
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					*this += smallRectangles;
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
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					*this += smallRectangles;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
}

void ComposedShape::optimalFit(const Circle & containerShape, const Circle & smallShape){
	clearComposedShape();
	Circle * containerCircle = new Circle(containerShape);
	myContainerShape = containerCircle;
	int mainRadius = containerShape.getRadius();
	int smallRadius = smallShape.getRadius();
	double height60 = smallRadius*sqrt(2.99999999999999);
	restContainerArea = containerShape.getArea();
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
	Circle * smallCircles;
	if (count1 > count2){
		i = mainRadius;
		j = smallRadius;
		while (mainRadius*2 - j >= smallRadius){
			while (i >= smallRadius)
				i -= 2*height60;
			i += 2*height60;
			while (mainRadius*2 - i >= smallRadius){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
					smallCircles = new Circle(smallRadius,i,j);
					*this += smallCircles;
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
					smallCircles = new Circle(smallRadius,i,j);
					*this += smallCircles;
				}
				i += 2*smallRadius;
			}
			i += smallRadius;
			j += height60;
		}
	}
}

void ComposedShape::optimalFit(const Circle & containerShape, const Triangle & smallShape){
	clearComposedShape();
	Circle * containerCircle = new Circle(containerShape);
	myContainerShape = containerCircle;
	int mainRadius = containerShape.getRadius();
	int smallEdge = smallShape.getEdge();
	double height60 = smallEdge*sqrt(2.99999999999999)/2.0;
	restContainerArea = containerShape.getArea();
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
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
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
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
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
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
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
			if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
				++count2;
			}
			i += smallEdge;
		}
		i += smallEdge/2.0;
		j += height60;
	}
	Triangle * smallTriangles;
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
					smallTriangles = new Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60);
					*this += smallTriangles;
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j);
					*this += smallTriangles;
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
					smallTriangles = new Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60);
					*this += smallTriangles;
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j);
					*this += smallTriangles;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
	}
}

void ComposedShape::optimalFit(const Triangle & containerShape, const Rectangle & smallShape){
	clearComposedShape();
	Triangle * containerTriangle = new Triangle(containerShape);
	myContainerShape = containerTriangle;
	int mainEdge = containerShape.getEdge();
	int smallWidth = smallShape.getWidth();
	int smallHeight = smallShape.getHeight();
	double mainHeight = mainEdge*sqrt(3.0)/2.0;
	restContainerArea = containerShape.getArea();
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
	Rectangle * smallRectangles;
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
				smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
				*this += smallRectangles;
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
				smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
				*this += smallRectangles;
				i += smallWidth;
			}
			iOffset += smallHeight/sqrt(3.0);
			iWall -= smallHeight/sqrt(3.0);
			j -= smallHeight;
		}
	}
}

void ComposedShape::optimalFit(const Triangle & containerShape, const Circle & smallShape){
	clearComposedShape();
	Triangle * containerTriangle = new Triangle(containerShape);
	myContainerShape = containerTriangle;
	int mainEdge = containerShape.getEdge();
	int smallRadius = smallShape.getRadius();
	double mainHeight = mainEdge*sqrt(3.0)/2.0;
	restContainerArea = containerShape.getArea();
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = smallRadius*sqrt(3.0);
	iWall = mainEdge;
	j = mainHeight - smallRadius;
	Circle * smallCircles;
	while (j >= smallRadius*2){
		i = iOffset;
		while (iWall - i >= smallRadius*sqrt(3.0)){
			smallCircles = new Circle(smallRadius,i,j);
			*this += smallCircles;
			i += smallRadius*2;
		}
		iOffset += smallRadius;
		iWall -= smallRadius;
		j -= smallRadius*sqrt(3.0);
	}
}

void ComposedShape::optimalFit(const Triangle & containerShape, const Triangle & smallShape){
	clearComposedShape();
	Triangle * containerTriangle = new Triangle(containerShape);
	myContainerShape = containerTriangle;
	int mainEdge = containerShape.getEdge();
	int smallEdge = smallShape.getEdge();
	double mainHeight = mainEdge*sqrt(3.0)/2.0;
	double smallHeight = smallEdge*sqrt(2.99999999999999)/2.0;
	restContainerArea = containerShape.getArea();
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = 0.0;
	iWall = mainEdge;
	j = mainHeight;
	Triangle * smallTriangles;
	while (j >= smallHeight){
		i = iOffset;
		while (i <= iWall-smallEdge){
			smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j-smallHeight,i+smallEdge,j);
			*this += smallTriangles;
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
			smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+smallHeight,i+smallEdge,j);
			*this += smallTriangles;
			i += smallEdge;
		}
		iOffset += smallEdge/2.0;
		iWall -= smallEdge/2.0;
		j -= smallHeight;
	}
}
}