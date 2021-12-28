#ifndef POLYGON_H_
#define POLYGON_H_

namespace SpacePolygon
{
class Polygon : public Shape{
public:
	class Point2D
	{
		public:
			Point2D();
			Point2D(int myX, int myY);
			double getX() const;
			double getY() const;
			void setX(double ix);
			void setY(double iy);
		protected:
			double x;
			double y;
			void isXvalid();
			void isYvalid();
	};
	double getArea() const override;
	double getPerimeter() const override;
protected:
	double area;
	double perimeter;
public:
	virtual const Point2D & operator [] (int index) const = 0;
	virtual Point2D & operator [] (int index) = 0;
	virtual double getSize() const = 0;
};
}

#endif