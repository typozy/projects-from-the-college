#ifndef POLYGON_H_
#define POLYGON_H_

namespace SpacePolygon
{
class Polygon{
public:
	class Point2D{
	public:
		Point2D();
		Point2D(int myX, int myY);
		double getX() const;
		double getY() const;
		void setX(double ix);
		void setY(double iy);
	private:
		double x;
		double y;
		void isXvalid();
		void isYvalid();
	};
	Polygon();
	Polygon(int pg);
	Polygon(const Rectangle & rect);
	Polygon(const Circle & circ);
	Polygon(const Triangle & tria);
	Polygon(const vector<Point2D> & vec2d);
	Polygon(const Point2D & p2d);
	Polygon(const Polygon & pg);
	Polygon & operator = (const Polygon & pg);
	~Polygon();
	friend ofstream & operator << (ofstream & file, const Polygon & pg);
	ofstream & drawContainer(ofstream & file) const;
	ofstream & drawSmall(ofstream & file) const;
	const Point2D & operator [] (int index) const;
	Point2D & operator [] (int index);
	bool operator == (const Polygon & other) const;
	bool operator != (const Polygon & other) const;
	const Polygon operator + (const Polygon & other) const;
	double getSize() const;
	double getArea() const;
	double getPerimeter() const;
private:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				Point2D noPoint;
	Point2D * points;
	int size;
	double area;
	double perimeter;
};
}

#endif