#ifndef POLYGONDYN_H_
#define POLYGONDYN_H_

namespace SpacePolygonDyn
{
class PolygonDyn : public Polygon{
public:
	PolygonDyn();
	PolygonDyn(int pg);
	PolygonDyn(const Rectangle & rect);
	PolygonDyn(const Circle & circ);
	PolygonDyn(const Triangle & tria);
	PolygonDyn(const vector<Point2D> & vec2d);
	PolygonDyn(const Point2D & p2d);
	PolygonDyn(const PolygonDyn & pg);
	PolygonDyn & operator = (const PolygonDyn & pg);
	~PolygonDyn();
	ofstream & draw(ofstream & file) const override;
	ofstream & drawContainer(ofstream & file) const override;
	ofstream & drawSmall(ofstream & file) const override;
	const Point2D & operator [] (int index) const override;
	Point2D & operator [] (int index) override;
	const PolygonDyn operator + (const PolygonDyn & other) const;
	double getSize() const override;
	PolygonDyn & operator ++ () override;
	PolygonDyn & operator ++ (int ignoreMe) override;
	PolygonDyn & operator -- () override;
	PolygonDyn & operator -- (int ignoreMe) override;
private:
	Point2D * points;
	int size;
public:
	virtual ostream & printOut(ostream & print) const{return print;}
};
}

#endif