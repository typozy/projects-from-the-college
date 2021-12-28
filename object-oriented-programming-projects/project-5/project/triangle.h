#ifndef TRIANGLE_H_
#define TRIANGLE_H_

namespace SpaceTriangle
{
class Triangle : public Shape{
public:
	Triangle();
	Triangle(int myEdge);
	Triangle(int myEdge, double myX, double myY);
	Triangle(int myEdge, double myX1, double myY1, double myX2, double myY2, double myX3, double myY3);
	Triangle(const Triangle & other);
	Triangle & operator = (const Triangle & other);
	~Triangle();
	void setEdge(int myEdge);
	void setX1(double myX1);
	void setY1(double myY1);
	void setX2(double myX2);
	void setY2(double myY2);
	void setX3(double myX3);
	void setY3(double myY3);
	int getEdge() const;
	double getPerimeter() const override;
	double getArea() const override;
	double getX1() const;
	double getY1() const;
	double getX2() const;
	double getY2() const;
	double getX3() const;
	double getY3() const;
	Triangle & operator ++ () override;
	Triangle & operator ++ (int ignoreMe) override;
	Triangle & operator -- () override;
	Triangle & operator -- (int ignoreMe) override;
	const Triangle operator + (double mySize) const;
	const Triangle operator - (double mySize) const;
	friend const Triangle operator + (double mySize, const Triangle & myTriangle);
	friend const Triangle operator - (double mySize, const Triangle & myTriangle);
	static double getTotalArea();
	static double getTotalPerimeter();
	ostream & printOut(ostream & print) const override;
	ofstream & draw(ofstream & file) const override;
	ofstream & drawContainer(ofstream & file) const override;
	ofstream & drawSmall(ofstream & file) const override;
private:
	int edge;
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	static double totalArea;
	static double totalPerimeter;
	void isEdgeValid();
};
}

#endif