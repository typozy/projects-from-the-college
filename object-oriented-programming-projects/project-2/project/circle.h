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
	double getX() const;
	double getY() const;
	ofstream & draw(ofstream & file) const;
	ofstream & drawContainer(ofstream & file) const;
	ofstream & drawSmall(ofstream & file) const;
private:
	int radius;
	double x;
	double y;
	void isRadiusValid();
};

#endif