#ifndef CIRCLE_H_
#define CIRCLE_H_

namespace SpaceCircle
{
class Circle : public Shape{
public:
	Circle();
	Circle(int myRadius);
	Circle(int myRadius, double myX, double myY);
	Circle(const Circle & other);
	Circle & operator = (const Circle & other);
	~Circle();
	void setRadius(int myRadius);
	void setX(double myX);
	void setY(double myY);
	int getRadius() const;
	double getPerimeter() const override;
	double getArea() const override;
	double getX() const;
	double getY() const;
	static double getTotalArea();
	static double getTotalPerimeter();
	Circle & operator ++ () override;
	Circle & operator ++ (int ignoreMe) override;
	Circle & operator -- () override;
	Circle & operator -- (int ignoreMe) override;
	const Circle operator + (double mySize) const;
	const Circle operator - (double mySize) const;
	friend const Circle operator + (double mySize, const Circle & myCircle);
	friend const Circle operator - (double mySize, const Circle & myCircle);
	ostream & printOut(ostream & print) const override;
	ofstream & draw(ofstream & file) const override;
	ofstream & drawContainer(ofstream & file) const override;
	ofstream & drawSmall(ofstream & file) const override;
private:
	int radius;
	double x;
	double y;
	static double totalArea;
	static double totalPerimeter;
	void isRadiusValid();
};
}

#endif