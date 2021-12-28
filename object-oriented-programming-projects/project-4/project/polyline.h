#ifndef POLYLINE_H_
#define POLYLINE_H_

namespace SpacePolyline
{
class Polyline{
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
	Polyline();
	Polyline(const Rectangle & rect);
	Polyline(const Circle & circ);
	Polyline(const Triangle & tria);
	Polyline(const vector<Point2D> & vec2d);
	Polyline(const Point2D & p2d);
	Polyline(const Polyline & pl);
	Polyline & operator = (const Polyline & pl);
	~Polyline();
	friend ofstream & operator << (ofstream & file, const Polyline & pl);
	const Point2D & operator [] (int index) const;
	Point2D & operator [] (int index);
	bool operator == (const Polyline & other) const;
	bool operator != (const Polyline & other) const;
	const Polyline operator + (const Polyline & other) const;
	double getSize() const;
private:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				Point2D noPoint;
	Point2D * points;
	int size;
};
}

#endif