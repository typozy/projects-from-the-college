#ifndef CIRCLE_H_
#define CIRCLE_H_

class Circle{
public:
	Circle();
	Circle(int myRadius);
	Circle(int myRadius, double myX, double myY);
	void setRadius(int myRadius);
	void setX(double myX);
	void setY(double myY);
	int getRadius() const;
	double getPerimeter() const;
	double getArea() const;
	double getX() const;
	double getY() const;
	static double getTotalArea();
	static double getTotalPerimeter();
	Circle operator ++ ();
	Circle operator ++ (int ignoreMe);
	Circle operator -- ();
	Circle operator -- (int ignoreMe);
	const Circle operator + (double mySize) const;
	const Circle operator - (double mySize) const;
	friend const Circle operator + (double mySize, const Circle & myCircle);
	friend const Circle operator - (double mySize, const Circle & myCircle);
	bool operator == (const Circle & other) const;
	bool operator != (const Circle & other) const;
	bool operator < (const Circle & other) const;
	bool operator > (const Circle & other) const;
	bool operator <= (const Circle & other) const;
	bool operator >= (const Circle & other) const;
	friend ofstream & operator << (ofstream & file, const Circle & smallShape);
	friend ostream & operator << (ostream & print, const Circle & smallShape);
	ofstream & drawContainer(ofstream & file) const;
	ofstream & drawSmall(ofstream & file) const;
private:
	int radius;
	double x;
	double y;
	static double totalArea;
	static double totalPerimeter;
	void isRadiusValid();
};

#endif