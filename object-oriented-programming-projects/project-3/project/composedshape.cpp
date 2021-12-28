#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "attribute.h"
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "composedshape.h"

double ComposedShape::hypotenus(double x1, double y1, double x2, double y2){
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

ComposedShape & ComposedShape::operator += (const ComposedShape::ShapeElem & smallShape){
	mySmallShapes.push_back(smallShape);
	restContainerArea -= smallShape.getArea();
	++totalSmallShapes;
	return *this;
}

const ComposedShape::ShapeElem & ComposedShape::operator [] (int index) const{
	return ((index < totalSmallShapes && index > -1) ? mySmallShapes[index] : noShape);
}

ComposedShape::ShapeElem & ComposedShape::operator [] (int index){
	return ((index < totalSmallShapes && index > -1) ? mySmallShapes[index] : noShape);
}

ComposedShape::ShapeElem::ShapeElem():shapeObject(nullptr),objectType(Shape::NoShape){}
void ComposedShape::ShapeElem::setObjectType(Shape myShape){objectType = myShape;}
Shape ComposedShape::ShapeElem::getObjectType() const{return objectType;}
void * ComposedShape::ShapeElem::getShapeObject() const{return shapeObject;}
void ComposedShape::ShapeElem::setShapeObject(void * ptr){shapeObject = ptr;}

double ComposedShape::ShapeElem::getPerimeter() const{
	if (objectType == Shape::Rectangle){
		Rectangle * temp = static_cast <Rectangle *> (shapeObject);
		return temp->getPerimeter();
	}
	else if (objectType == Shape::Circle){
		Circle * temp = static_cast <Circle *> (shapeObject);
		return temp->getPerimeter();
	}
	else if (objectType == Shape::Triangle){
		Triangle * temp = static_cast <Triangle *> (shapeObject);
		return temp->getPerimeter();
	}
	else return 0.0;
}

double ComposedShape::ShapeElem::getArea() const{
	if (objectType == Shape::Rectangle){
		Rectangle * temp = static_cast <Rectangle *> (shapeObject);
		return temp->getArea();
	}
	else if (objectType == Shape::Circle){
		Circle * temp = static_cast <Circle *> (shapeObject);
		return temp->getArea();
	}
	else if (objectType == Shape::Triangle){
		Triangle * temp = static_cast <Triangle *> (shapeObject);
		return temp->getArea();
	}
	else return 0.0;
}

ofstream & operator << (ofstream & file, const ComposedShape::ShapeElem & smallShape){
	if (smallShape.objectType == Shape::Rectangle){
		Rectangle * temp = static_cast <Rectangle *> (smallShape.shapeObject);
		file << (*temp);
	}
	else if (smallShape.objectType == Shape::Circle){
		Circle * temp = static_cast <Circle *> (smallShape.shapeObject);
		file << (*temp);
	}
	else if (smallShape.objectType == Shape::Triangle){
		Triangle * temp = static_cast <Triangle *> (smallShape.shapeObject);
		file << (*temp);
	}
	return file;
}

ostream & operator << (ostream & print, const ComposedShape::ShapeElem & smallShape){
	if (smallShape.objectType == Shape::Rectangle){
		Rectangle * temp = static_cast <Rectangle *> (smallShape.shapeObject);
		print << (*temp);
	}
	else if (smallShape.objectType == Shape::Circle){
		Circle * temp = static_cast <Circle *> (smallShape.shapeObject);
		print << (*temp);
	}
	else if (smallShape.objectType == Shape::Triangle){
		Triangle * temp = static_cast <Triangle *> (smallShape.shapeObject);
		print << (*temp);
	}
	else print << "There is no small shape with this index." << endl;
	return print;
}

vector<ComposedShape::ShapeElem> ComposedShape::getSmallShapes() const{return mySmallShapes;}
double ComposedShape::getRestArea() const{return restContainerArea;};
int ComposedShape::getTotalSmallShapes() const{return totalSmallShapes;};

ostream & operator << (ostream & print, const ComposedShape & bigPicture){
	print << "Your container ";
	if (bigPicture.myContainerShape.getObjectType() == Shape::Rectangle){
		print << "rectangle";
	}
	else if (bigPicture.myContainerShape.getObjectType() == Shape::Circle){
		print << "circle";
	}
	else{
		print << "triangle";
	}
	print << " holds " << bigPicture.totalSmallShapes << " small ";
	print << ((bigPicture.totalSmallShapes > 1) ? "shapes" : "shape");
	print << ". The rest area is " << fixed << setprecision(2) << bigPicture.restContainerArea << "." << endl;
	return print;
}

ofstream & operator << (ofstream & file, const ComposedShape & bigPicture){
	if (bigPicture.totalSmallShapes < 1){
		if (bigPicture.myContainerShape.getObjectType() == Shape::Rectangle) file.open("containerrectangle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Circle) file.open("containercircle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Triangle) file.open("containertriangle.svg");
	}
	else{
		if (bigPicture.myContainerShape.getObjectType() == Shape::Rectangle
			&& bigPicture[0].getObjectType() == Shape::Rectangle) file.open("rectanglesinrectangle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Rectangle
			&& bigPicture[0].getObjectType() == Shape::Circle) file.open("circlesinrectangle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Rectangle
			&& bigPicture[0].getObjectType() == Shape::Triangle) file.open("trianglesinrectangle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Circle
			&& bigPicture[0].getObjectType() == Shape::Rectangle) file.open("rectanglesincircle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Circle
			&& bigPicture[0].getObjectType() == Shape::Circle) file.open("circlesincircle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Circle
			&& bigPicture[0].getObjectType() == Shape::Triangle) file.open("trianglesincircle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Triangle
			&& bigPicture[0].getObjectType() == Shape::Rectangle) file.open("rectanglesintriangle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Triangle
			&& bigPicture[0].getObjectType() == Shape::Circle) file.open("circlesintriangle.svg");
		else if (bigPicture.myContainerShape.getObjectType() == Shape::Triangle
			&& bigPicture[0].getObjectType() == Shape::Triangle) file.open("trianglesintriangle.svg");
	}
	if (bigPicture.myContainerShape.getObjectType() == Shape::Rectangle){
		Rectangle * temp;
		temp = static_cast <Rectangle *> (bigPicture.myContainerShape.getShapeObject());
		temp->drawContainer(file);
	}
	else if (bigPicture.myContainerShape.getObjectType() == Shape::Circle){
		Circle * temp;
		temp = static_cast <Circle *> (bigPicture.myContainerShape.getShapeObject());
		temp->drawContainer(file);
	}
	else if (bigPicture.myContainerShape.getObjectType() == Shape::Triangle){
		Triangle * temp;
		temp = static_cast <Triangle *> (bigPicture.myContainerShape.getShapeObject());
		temp->drawContainer(file);
	}
	for (int i = 0; i < bigPicture.totalSmallShapes; ++i){
		if (bigPicture[i].getObjectType() == Shape::Rectangle){
			Rectangle * temp;
			temp = static_cast <Rectangle *> (bigPicture[i].getShapeObject());
			temp->drawSmall(file);
		}
		else if (bigPicture[i].getObjectType() == Shape::Circle){
			Circle * temp;
			temp = static_cast <Circle *> (bigPicture[i].getShapeObject());
			temp->drawSmall(file);			
		}
		else if (bigPicture[i].getObjectType() == Shape::Triangle){
			Triangle * temp;
			temp = static_cast <Triangle *> (bigPicture[i].getShapeObject());
			temp->drawSmall(file);
		}
	}
	file << "</svg>";
	file.close();
	return file;
}

void ComposedShape::clearComposedShape(){
	if (myContainerShape.getShapeObject() != nullptr){
		if (myContainerShape.getObjectType() == Shape::Rectangle){
			Rectangle * temp;
			temp = static_cast <Rectangle *> (myContainerShape.getShapeObject());
			delete temp;
		}
		else if (myContainerShape.getObjectType() == Shape::Circle){
			Circle * temp;
			temp = static_cast <Circle *> (myContainerShape.getShapeObject());
			delete temp;
		}
		else{
			Triangle * temp;
			temp = static_cast <Triangle *> (myContainerShape.getShapeObject());
			delete temp;
		}
		myContainerShape.setShapeObject(nullptr);
	}
	for (int i = totalSmallShapes-1; i > -1; --i){
		if ((*this)[i].getObjectType() == Shape::Rectangle){
			Rectangle * temp;
			temp = static_cast <Rectangle *> ((*this)[i].getShapeObject());
			delete temp;
			mySmallShapes.pop_back();
			
		}
		else if ((*this)[i].getObjectType() == Shape::Circle){
			Circle * temp;
			temp = static_cast <Circle *> ((*this)[i].getShapeObject());
			delete temp;
			mySmallShapes.pop_back();				
			
		}
		else if ((*this)[i].getObjectType() == Shape::Triangle){
			Triangle * temp;
			temp = static_cast <Triangle *> ((*this)[i].getShapeObject());
			delete temp;
			mySmallShapes.pop_back();
		}
		totalSmallShapes = 0;
	}
}

ComposedShape::ComposedShape()
	:totalSmallShapes(0){
	optimalFit(Rectangle(1920,1080),Rectangle(2000,1500));
	}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Rectangle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);
}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Circle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Triangle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Rectangle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Circle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Triangle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Rectangle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Circle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Triangle & smallShape)
	:totalSmallShapes(0){
	optimalFit(containerShape,smallShape);
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Rectangle & smallShape){
	clearComposedShape();
	Rectangle * containerRectangle = new Rectangle(containerShape);
	myContainerShape.setObjectType(Shape::Rectangle);
	myContainerShape.setShapeObject(static_cast <void *> (containerRectangle));
	int mainHeight = containerShape.getHeight();
	int mainWidth = containerShape.getWidth();
	int smallHeight = smallShape.getHeight();
	int smallWidth = smallShape.getWidth();
	restContainerArea = mainWidth*mainHeight;
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
	ShapeElem smallRectangles;
	smallRectangles.setObjectType(Shape::Rectangle);
	Rectangle * smallRectangle;
	if (count1 > count2){
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
				smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
				smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
				smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
				smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
				smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
				smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
				smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
	myContainerShape.setObjectType(Shape::Rectangle);
	myContainerShape.setShapeObject(static_cast <void *> (containerRectangle));
	int mainHeight = containerShape.getHeight();
	int mainWidth = containerShape.getWidth();
	int smallRadius = smallShape.getRadius();
	double distance = smallRadius*sqrt(3.0);
	restContainerArea = mainWidth*mainHeight;
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
	ShapeElem smallCircles;
	smallCircles.setObjectType(Shape::Circle);
	Circle * smallCircle;
	if(count1 >= count2 && count1 >= count3){
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				smallCircle = new Circle(smallRadius,i,j);
				smallCircles.setShapeObject(static_cast <void *> (smallCircle));
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
				smallCircle = new Circle(smallRadius,i,j);
				smallCircles.setShapeObject(static_cast <void *> (smallCircle));
				*this += smallCircles;
				i += smallRadius*2;
			}
			j += distance*2;
		}
		j = smallRadius+distance;
		while (mainHeight - j >= smallRadius){
			i = smallRadius*2;
			while (mainWidth - i >= smallRadius){
				smallCircle = new Circle(smallRadius,i,j);
				smallCircles.setShapeObject(static_cast <void *> (smallCircle));
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
				smallCircle = new Circle(smallRadius,i,j);
				smallCircles.setShapeObject(static_cast <void *> (smallCircle));
				*this += smallCircles;
				i += distance*2;
			}
			j += smallRadius*2;
		}
		j = smallRadius*2;
		while (mainHeight - j >= smallRadius){
			i = smallRadius+distance;
			while (mainWidth - i >= smallRadius){
				smallCircle = new Circle(smallRadius,i,j);
				smallCircles.setShapeObject(static_cast <void *> (smallCircle));
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
	myContainerShape.setObjectType(Shape::Rectangle);
	myContainerShape.setShapeObject(static_cast <void *> (containerRectangle));
	int mainWidth = containerShape.getWidth();
	int mainHeight = containerShape.getHeight();
	int smallEdge = smallShape.getEdge();
	restContainerArea = mainWidth*mainHeight;
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
	ShapeElem smallTriangles;
	smallTriangles.setObjectType(Shape::Triangle);
	Triangle * smallTriangle;
	if (count1 > count2){
		j = 0.0;
		while (mainHeight - j >= height){
			i = 0.0;
			while (mainWidth - i >= smallEdge){
				smallTriangle = new Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j+height);
				smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
				*this += smallTriangles;
				i += smallEdge;
			}
			j += height;
		}
		j = height;
		while (mainHeight - j >= 0){
			i = smallEdge/2.0;
			while (mainWidth - i >= smallEdge){
				smallTriangle = new Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j-height);
				smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
				smallTriangle = new Triangle(smallEdge,i,j,i,j+smallEdge,i+height,j+smallEdge/2.0);
				smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
				*this += smallTriangles;
				i += height;
			}
			j += smallEdge;
		}
		j = smallEdge;
		while (mainHeight - j >= smallEdge/2.0){
			i = 0.0;
			while (mainWidth - i >= height){
				smallTriangle = new Triangle(smallEdge,i,j,i+height,j-smallEdge/2.0,i+height,j+smallEdge/2.0);
				smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
	myContainerShape.setObjectType(Shape::Circle);
	myContainerShape.setShapeObject(static_cast <void *> (containerCircle));
	int mainRadius = containerShape.getRadius();
	int smallWidth = smallShape.getWidth();
	int smallHeight = smallShape.getHeight();
	restContainerArea = PI*mainRadius*mainRadius;
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
	ShapeElem smallRectangles;
	smallRectangles.setObjectType(Shape::Rectangle);
	Rectangle * smallRectangle;
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
					smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
					smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
					smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
					smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
					smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
					smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
					smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
					smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
	myContainerShape.setObjectType(Shape::Circle);
	myContainerShape.setShapeObject(static_cast <void *> (containerCircle));
	int mainRadius = containerShape.getRadius();
	int smallRadius = smallShape.getRadius();
	double height60 = smallRadius*sqrt(2.99999999999999);
	restContainerArea = PI*mainRadius*mainRadius;
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
	ShapeElem smallCircles;
	smallCircles.setObjectType(Shape::Circle);
	Circle * smallCircle;
	if (count1 > count2){
		i = mainRadius;
		j = smallRadius;
		while (mainRadius*2 - j >= smallRadius){
			while (i >= smallRadius)
				i -= 2*height60;
			i += 2*height60;
			while (mainRadius*2 - i >= smallRadius){
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
					smallCircle = new Circle(smallRadius,i,j);
					smallCircles.setShapeObject(static_cast <void *> (smallCircle));
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
					smallCircle = new Circle(smallRadius,i,j);
					smallCircles.setShapeObject(static_cast <void *> (smallCircle));
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
	myContainerShape.setObjectType(Shape::Circle);
	myContainerShape.setShapeObject(static_cast <void *> (containerCircle));
	int mainRadius = containerShape.getRadius();
	int smallEdge = smallShape.getEdge();
	double height60 = smallEdge*sqrt(2.99999999999999)/2.0;
	restContainerArea = PI*mainRadius*mainRadius;
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
	ShapeElem smallTriangles;
	smallTriangles.setObjectType(Shape::Triangle);
	Triangle * smallTriangle;
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
					smallTriangle = new Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60);
					smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
					smallTriangle = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j);
					smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
					smallTriangle = new Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60);
					smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
					smallTriangle = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j);
					smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
	myContainerShape.setObjectType(Shape::Triangle);
	myContainerShape.setShapeObject(static_cast <void *> (containerTriangle));
	int mainEdge = containerShape.getEdge();
	int smallWidth = smallShape.getWidth();
	int smallHeight = smallShape.getHeight();
	double mainHeight = mainEdge*sqrt(3.0)/2.0;
	restContainerArea = mainEdge*mainEdge*sqrt(3.0)/4.0;
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
	ShapeElem smallRectangles;
	smallRectangles.setObjectType(Shape::Rectangle);
	Rectangle * smallRectangle;
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
				smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
				smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
				smallRectangle = new Rectangle(smallWidth,smallHeight,i,j);
				smallRectangles.setShapeObject(static_cast <void *> (smallRectangle));
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
	myContainerShape.setObjectType(Shape::Triangle);
	myContainerShape.setShapeObject(static_cast <void *> (containerTriangle));
	int mainEdge = containerShape.getEdge();
	int smallRadius = smallShape.getRadius();
	double mainHeight = mainEdge*sqrt(3.0)/2.0;
	restContainerArea = mainEdge*mainEdge*sqrt(3.0)/4.0;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = smallRadius*sqrt(3.0);
	iWall = mainEdge;
	j = mainHeight - smallRadius;
	ShapeElem smallCircles;
	smallCircles.setObjectType(Shape::Circle);
	Circle * smallCircle;
	while (j >= smallRadius*2){
		i = iOffset;
		while (iWall - i >= smallRadius*sqrt(3.0)){
			smallCircle = new Circle(smallRadius,i,j);
			smallCircles.setShapeObject(static_cast <void *> (smallCircle));
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
	myContainerShape.setObjectType(Shape::Triangle);
	myContainerShape.setShapeObject(static_cast <void *> (containerTriangle));
	int mainEdge = containerShape.getEdge();
	int smallEdge = smallShape.getEdge();
	double mainHeight = mainEdge*sqrt(3.0)/2.0;
	double smallHeight = smallEdge*sqrt(2.99999999999999)/2.0;
	restContainerArea = mainEdge*mainEdge*sqrt(3.0)/4.0;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = 0.0;
	iWall = mainEdge;
	j = mainHeight;
	ShapeElem smallTriangles;
	smallTriangles.setObjectType(Shape::Triangle);
	Triangle * smallTriangle;
	while (j >= smallHeight){
		i = iOffset;
		while (i <= iWall-smallEdge){
			smallTriangle = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j-smallHeight,i+smallEdge,j);
			smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
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
			smallTriangle = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+smallHeight,i+smallEdge,j);
			smallTriangles.setShapeObject(static_cast <void *> (smallTriangle));
			*this += smallTriangles;
			i += smallEdge;
		}
		iOffset += smallEdge/2.0;
		iWall -= smallEdge/2.0;
		j -= smallHeight;
	}
}