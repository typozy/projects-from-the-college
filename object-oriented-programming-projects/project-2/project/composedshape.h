#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

#define PI 3.14159265359

enum class Shape {Rectangle, Circle, Triangle};

double hypotenus (double x1, double y1, double x2, double y2);

class ComposedShape{
public:
	ComposedShape(const Rectangle & containerShape, const Rectangle & smallShape);
	ComposedShape(const Rectangle & containerShape, const Circle & smallShape);
	ComposedShape(const Rectangle & containerShape, const Triangle & smallShape);
	ComposedShape(const Circle & containerShape, const Rectangle & smallShape);
	ComposedShape(const Circle & containerShape, const Circle & smallShape);
	ComposedShape(const Circle & containerShape, const Triangle & smallShape);
	ComposedShape(const Triangle & containerShape, const Rectangle & smallShape);
	ComposedShape(const Triangle & containerShape, const Circle & smallShape);
	ComposedShape(const Triangle & containerShape, const Triangle & smallShape);
	void optimalFit(const Rectangle & containerShape, const Rectangle & smallShape);
	void optimalFit(const Rectangle & containerShape, const Circle & smallShape);
	void optimalFit(const Rectangle & containerShape, const Triangle & smallShape);
	void optimalFit(const Circle & containerShape, const Rectangle & smallShape);
	void optimalFit(const Circle & containerShape, const Circle & smallShape);
	void optimalFit(const Circle & containerShape, const Triangle & smallShape);
	void optimalFit(const Triangle & containerShape, const Rectangle & smallShape);
	void optimalFit(const Triangle & containerShape, const Circle & smallShape);
	void optimalFit(const Triangle & containerShape, const Triangle & smallShape);
	ofstream & draw(ofstream & file) const;
	vector<Rectangle> getSmallRectangles() const;
	vector<Circle> getSmallCircles() const;
	vector<Triangle> getSmallTriangles() const;
	double getRestArea() const;
	int getTotalSmallShapes() const;
	Shape containerType;
	Rectangle containerRectangle;
	Circle containerCircle;
	Triangle containerTriangle;
	Shape smallType;
	vector<Rectangle> smallRectangles;
	vector<Circle> smallCircles;
	vector<Triangle> smallTriangles;
private:
	double restContainerArea;
	int totalSmallShapes;
	ofstream & drawRectangleInRectangle(ofstream & file) const;
	ofstream & drawCircleInRectangle(ofstream & file) const;
	ofstream & drawTriangleInRectangle(ofstream & file) const;
	ofstream & drawRectangleInCircle(ofstream & file) const;
	ofstream & drawCircleInCircle(ofstream & file) const;
	ofstream & drawTriangleInCircle(ofstream & file) const;
	ofstream & drawRectangleInTriangle(ofstream & file) const;
	ofstream & drawCircleInTriangle(ofstream & file) const;
	ofstream & drawTriangleInTriangle(ofstream & file) const;
};

#endif