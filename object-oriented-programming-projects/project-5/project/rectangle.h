#ifndef RECTANGLE_H_
#define RECTANGLE_H_

namespace SpaceRectangle
{
class Rectangle : public Shape{
public:
	Rectangle();
	Rectangle(int myWidth, int myHeight);
	Rectangle(int myWidth, int myHeight, double myX, double myY);
	Rectangle(const Rectangle & other);
	Rectangle & operator = (const Rectangle & other);
	~Rectangle();
	void setWidth(int myWidth);
	void setHeight(int myHeight);
	void setX(double myX);
	void setY(double myY);
	int getWidth() const;
	int getHeight() const;
	double getPerimeter() const override;
	double getArea() const override;
	double getX() const;
	double getY() const;
	Rectangle & operator ++ () override;
	Rectangle & operator ++ (int ignoreMe) override;
	Rectangle & operator -- () override;
	Rectangle & operator -- (int ignoreMe) override;
	const Rectangle operator + (double mySize) const;
	const Rectangle operator - (double mySize) const;
	friend const Rectangle operator + (double mySize, const Rectangle & myRectangle);
	friend const Rectangle operator - (double mySize, const Rectangle & myRectangle);
	static double getTotalArea();
	static double getTotalPerimeter();
	ostream & printOut(ostream & print) const override;
	ofstream & draw(ofstream & file) const override;
	ofstream & drawContainer(ofstream & file) const override;
	ofstream & drawSmall(ofstream & file) const override;
private:
	int width;
	int height;
	double x;
	double y;
	static double totalArea;
	static double totalPerimeter;
	void isWidthValid();
	void isHeightValid();
};
}

#endif