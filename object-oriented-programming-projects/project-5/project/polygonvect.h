#ifndef VECT_H_
#define VECT_H_

namespace SpacePolygonVect
{
class PolygonVect : public Polygon{
public:
	PolygonVect();
	PolygonVect(int pg);
	PolygonVect(const Rectangle & rect);
	PolygonVect(const Circle & circ);
	PolygonVect(const Triangle & tria);
	PolygonVect(const vector<Point2D> & vec2d);
	PolygonVect(const Point2D & p2d);
	ofstream & draw(ofstream & file) const override;
	ofstream & drawContainer(ofstream & file) const override;
	ofstream & drawSmall(ofstream & file) const override;
	const Point2D & operator [] (int index) const override;
	Point2D & operator [] (int index) override;
	const PolygonVect operator + (const PolygonVect & other) const;
	double getSize() const override;
	PolygonVect & operator ++ () override;
	PolygonVect & operator ++ (int ignoreMe) override;
	PolygonVect & operator -- () override;
	PolygonVect & operator -- (int ignoreMe) override;
private:
	vector<Point2D> points;
public:
	virtual ostream & printOut(ostream & print) const{return print;}
};
}

#endif