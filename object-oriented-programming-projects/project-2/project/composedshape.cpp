#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "composedshape.h"

double hypotenus (double x1, double y1, double x2, double y2){
	return (sqrt((x2-x1)*(x2-x1)*1.0+(y2-y1)*(y2-y1))*1.0);
}

vector<Rectangle> ComposedShape::getSmallRectangles() const{return smallRectangles;}
vector<Circle> ComposedShape::getSmallCircles() const{return smallCircles;}
vector<Triangle> ComposedShape::getSmallTriangles() const{return smallTriangles;}
double ComposedShape::getRestArea() const{return restContainerArea;};
int ComposedShape::getTotalSmallShapes() const{return totalSmallShapes;};

ComposedShape::ComposedShape(const Rectangle & containerShape, const Rectangle & smallShape){
	optimalFit(containerShape,smallShape);
}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Circle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Rectangle & containerShape, const Triangle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Rectangle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Circle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Circle & containerShape, const Triangle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Rectangle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Circle & smallShape){
	optimalFit(containerShape,smallShape);	
}

ComposedShape::ComposedShape(const Triangle & containerShape, const Triangle & smallShape){
	optimalFit(containerShape,smallShape);	
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Rectangle & smallShape){
	containerRectangle = containerShape;
	containerType = Shape::Rectangle;
	int count = 0;
	smallType = Shape::Rectangle;
	smallRectangles.clear();
	int mainHeight = containerShape.getHeight();
	int mainWidth = containerShape.getWidth();
	int smallHeight = smallShape.getHeight();
	int smallWidth = smallShape.getWidth();
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
	if (count1 > count2){
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
				smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
				smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
				smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
				++count;
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	restContainerArea = mainWidth*mainHeight - count*smallWidth*smallHeight;
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Circle & smallShape){
	containerRectangle = containerShape;
	containerType = Shape::Rectangle;
	int count = 0;
	smallType = Shape::Circle;
	smallCircles.clear();
	int mainHeight = containerShape.getHeight();
	int mainWidth = containerShape.getWidth();
	int smallRadius = smallShape.getRadius();
	double i = 0.0, j = 0.0;
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
				smallCircles.push_back(Circle(smallRadius,i,j));
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
				smallCircles.push_back(Circle(smallRadius,i,j));
				++count;
				i += smallRadius*2;
			}
			j += distance*2;
		}
		j = smallRadius+distance;
		while (mainHeight - j >= smallRadius){
			i = smallRadius*2;
			while (mainWidth - i >= smallRadius){
				smallCircles.push_back(Circle(smallRadius,i,j));
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
				smallCircles.push_back(Circle(smallRadius,i,j));
				++count;
				i += distance*2;
			}
			j += smallRadius*2;
		}
		j = smallRadius*2;
		while (mainHeight - j >= smallRadius){
			i = smallRadius+distance;
			while (mainWidth - i >= smallRadius){
				smallCircles.push_back(Circle(smallRadius,i,j));
				++count;
				i += distance*2;
			}
			j += smallRadius*2;
		}
	}
	restContainerArea = mainWidth*mainHeight - count*PI*smallRadius*smallRadius;
	totalSmallShapes = count;	
}

void ComposedShape::optimalFit(const Rectangle & containerShape, const Triangle & smallShape){
	containerRectangle = containerShape;
	containerType = Shape::Rectangle;
	int count = 0;
	smallType = Shape::Triangle;
	smallTriangles.clear();
	int mainWidth = containerShape.getWidth();
	int mainHeight = containerShape.getHeight();
	int smallEdge = smallShape.getEdge();
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
	if (count1 > count2){
		j = 0.0;
		while (mainHeight - j >= height){
			i = 0.0;
			while (mainWidth - i >= smallEdge){
				smallTriangles.push_back(Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j+height));
				++count;
				i += smallEdge;
			}
			j += height;
		}
		j = height;
		while (mainHeight - j >= 0){
			i = smallEdge/2.0;
			while (mainWidth - i >= smallEdge){
				smallTriangles.push_back(Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j-height));
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
				smallTriangles.push_back(Triangle(smallEdge,i,j,i,j+smallEdge,i+height,j+smallEdge/2.0));
				++count;
				i += height;
			}
			j += smallEdge;
		}
		j = smallEdge;
		while (mainHeight - j >= smallEdge/2.0){
			i = 0.0;
			while (mainWidth - i >= height){
				smallTriangles.push_back(Triangle(smallEdge,i,j,i+height,j-smallEdge/2.0,i+height,j+smallEdge/2.0));
				++count;
				i += height;
			}
			j += smallEdge;
		}
	}
	restContainerArea = mainWidth*mainHeight - count*smallEdge*height/2.0;
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Circle & containerShape, const Rectangle & smallShape){
	containerCircle = containerShape;
	containerType = Shape::Circle;
	int count = 0;
	smallType = Shape::Rectangle;
	smallRectangles.clear();
	int mainRadius = containerShape.getRadius();
	int smallWidth = smallShape.getWidth();
	int smallHeight = smallShape.getHeight();
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
					smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
					smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
					smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
					smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
					++count;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
	}
	restContainerArea = PI*mainRadius*mainRadius-count*smallWidth*smallHeight;
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Circle & containerShape, const Circle & smallShape){
	containerCircle = containerShape;
	containerType = Shape::Circle;
	int count = 0;
	smallType = Shape::Circle;
	smallCircles.clear();
	int mainRadius = containerShape.getRadius();
	int smallRadius = smallShape.getRadius();
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
					smallCircles.push_back(Circle(smallRadius,i,j));
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
					smallCircles.push_back(Circle(smallRadius,i,j));
					++count;
				}
				i += 2*smallRadius;
			}
			i += smallRadius;
			j += height60;
		}
	}
	restContainerArea = PI*(mainRadius*mainRadius-count*smallRadius*smallRadius);
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Circle & containerShape, const Triangle & smallShape){
	containerCircle = containerShape;
	containerType = Shape::Circle;
	int count = 0;
	smallType = Shape::Triangle;
	smallTriangles.clear();
	int mainRadius = containerShape.getRadius();
	int smallEdge = smallShape.getEdge();
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
					smallTriangles.push_back(Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60));
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					smallTriangles.push_back(Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j));
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
					smallTriangles.push_back(Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60));
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
				if (hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					smallTriangles.push_back(Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j));
					++count;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
	}
	restContainerArea = PI*mainRadius*mainRadius-count*smallEdge*height60/2.0;
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Triangle & containerShape, const Rectangle & smallShape){
	containerTriangle = containerShape;
	containerType = Shape::Triangle;
	int count = 0;
	smallType = Shape::Rectangle;
	smallRectangles.clear();
	int mainEdge = containerShape.getEdge();
	int smallWidth = smallShape.getWidth();
	int smallHeight = smallShape.getHeight();
	double mainHeight = mainEdge*sqrt(3.0)/2;
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
				smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
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
				smallRectangles.push_back(Rectangle(smallWidth,smallHeight,i,j));
				++count;
				i += smallWidth;
			}
			iOffset += smallHeight/sqrt(3.0);
			iWall -= smallHeight/sqrt(3.0);
			j -= smallHeight;
		}
	}
	restContainerArea = mainEdge*mainEdge*sqrt(3.0)/4.0 - count*smallHeight*smallWidth;
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Triangle & containerShape, const Circle & smallShape){
	containerTriangle = containerShape;
	containerType = Shape::Triangle;
	int count = 0;
	smallType = Shape::Circle;
	smallCircles.clear();
	int mainEdge = containerShape.getEdge();
	int smallRadius = smallShape.getRadius();
	double mainHeight = mainEdge*sqrt(3.0)/2;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = smallRadius*sqrt(3.0);
	iWall = mainEdge;
	j = mainHeight - smallRadius;
	while (j >= smallRadius*2){
		i = iOffset;
		while (iWall - i >= smallRadius*sqrt(3.0)){
			smallCircles.push_back(Circle(smallRadius,i,j));
			++count;
			i += smallRadius*2;
		}
		iOffset += smallRadius;
		iWall -= smallRadius;
		j -= smallRadius*sqrt(3.0);
	}
	restContainerArea = mainEdge*mainEdge*sqrt(3.0)/4.0 - count*PI*smallRadius*smallRadius;
	totalSmallShapes = count;
}

void ComposedShape::optimalFit(const Triangle & containerShape, const Triangle & smallShape){
	containerTriangle = containerShape;
	containerType = Shape::Triangle;
	int count = 0;
	smallType = Shape::Triangle;
	smallTriangles.clear();
	int mainEdge = containerShape.getEdge();
	int smallEdge = smallShape.getEdge();
	double mainHeight = mainEdge*sqrt(3.0)/2;
	double smallHeight = smallEdge*sqrt(3.0)/2;
	double i = 0.0, j = 0.0;
	double iOffset = 0.0, iWall = 0.0;
	iOffset = 0.0;
	iWall = mainEdge;
	j = mainHeight;
	while (j >= smallHeight){
		i = iOffset;
		while (i <= iWall-smallEdge){
			smallTriangles.push_back(Triangle(smallEdge,i,j,i+smallEdge/2.0,j-smallHeight,i+smallEdge,j));
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
			smallTriangles.push_back(Triangle(smallEdge,i,j,i+smallEdge/2.0,j+smallHeight,i+smallEdge,j));
			++count;
			i += smallEdge;
		}
		iOffset += smallEdge/2.0;
		iWall -= smallEdge/2.0;
		j -= smallHeight;
	}
	restContainerArea = (mainEdge*mainEdge - count*smallEdge*smallEdge)*sqrt(3.0)/4.0;
	totalSmallShapes = count;
}

ofstream & ComposedShape::draw(ofstream & file) const{
	if (containerType == Shape::Rectangle && smallType == Shape::Rectangle){
		drawRectangleInRectangle(file);
	}
	else if (containerType == Shape::Rectangle && smallType == Shape::Circle){
		drawCircleInRectangle(file);
	}
	else if (containerType == Shape::Rectangle && smallType == Shape::Triangle){
		drawTriangleInRectangle(file);
	}
	else{
		if (containerType == Shape::Circle && smallType == Shape::Rectangle){
			drawRectangleInCircle(file);
		}
		else if (containerType == Shape::Circle && smallType == Shape::Circle){
			drawCircleInCircle(file);
		}
		else if (containerType == Shape::Circle && smallType == Shape::Triangle){
			drawTriangleInCircle(file);
		}
		else{
			if (containerType == Shape::Triangle && smallType == Shape::Rectangle){
				drawRectangleInTriangle(file);
			}
			else if (containerType == Shape::Triangle && smallType == Shape::Circle){
				drawCircleInTriangle(file);
			}
			else if (containerType == Shape::Triangle && smallType == Shape::Triangle){
				drawTriangleInTriangle(file);
			}
		}
	}
	return file;
}

ofstream & ComposedShape::drawRectangleInRectangle(ofstream & file) const{
	file.open("rectangleInRectangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerRectangle.getWidth() << R"(" height=")" << containerRectangle.getHeight() << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerRectangle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallRectangles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawCircleInRectangle(ofstream & file) const{
	file.open("circleInRectangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerRectangle.getWidth() << R"(" height=")" << containerRectangle.getHeight() << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerRectangle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallCircles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawTriangleInRectangle(ofstream & file) const{
	file.open("triangleInRectangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerRectangle.getWidth() << R"(" height=")" << containerRectangle.getHeight() << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerRectangle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallTriangles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawRectangleInCircle(ofstream & file) const{
	file.open("rectangleInCircle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerCircle.getRadius()*2 << R"(" height=")" << containerCircle.getRadius()*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerCircle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallRectangles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawCircleInCircle(ofstream & file) const{
	file.open("circleInCircle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerCircle.getRadius()*2 << R"(" height=")" << containerCircle.getRadius()*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerCircle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallCircles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawTriangleInCircle(ofstream & file) const{
	file.open("triangleInCircle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerCircle.getRadius()*2 << R"(" height=")" << containerCircle.getRadius()*2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerCircle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallTriangles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawRectangleInTriangle(ofstream & file) const{
	file.open("rectangleInTriangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerTriangle.getEdge() << R"(" height=")" << containerTriangle.getEdge()*sqrt(3.0)/2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerTriangle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallRectangles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawCircleInTriangle(ofstream & file) const{
	file.open("circleInTriangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerTriangle.getEdge() << R"(" height=")" << containerTriangle.getEdge()*sqrt(3.0)/2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerTriangle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallCircles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}

ofstream & ComposedShape::drawTriangleInTriangle(ofstream & file) const{
	file.open("triangleInTriangle.svg");
	file << R"(<svg version="1.1" baseProfile="full" width=")" << containerTriangle.getEdge() << R"(" height=")" << containerTriangle.getEdge()*sqrt(3.0)/2 << R"(" xmlns="http://www.w3.org/2000/svg">)" << endl
		 << '\t' << R"(<rect width="100%" height="100%" fill="gray" />)" << endl;
	containerTriangle.drawContainer(file);
	for (int i = 0; i < totalSmallShapes; ++i){
		smallTriangles[i].drawSmall(file);
	}
	file << "</svg>";
	file.close();
	return file;
}