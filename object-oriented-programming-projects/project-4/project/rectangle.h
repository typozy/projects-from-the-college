#ifndef RECTANGLE_H_
#define RECTANGLE_H_

namespace SpaceRectangle
{
class Rectangle{
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
	double getPerimeter() const;
	double getArea() const;
	double getX() const;
	double getY() const;
	Rectangle operator ++ ();
	Rectangle operator ++ (int ignoreMe);
	Rectangle operator -- ();
	Rectangle operator -- (int ignoreMe);
	const Rectangle operator + (double mySize) const;
	const Rectangle operator - (double mySize) const;
	friend const Rectangle operator + (double mySize, const Rectangle & myRectangle);
	friend const Rectangle operator - (double mySize, const Rectangle & myRectangle);
	bool operator == (const Rectangle & other) const;
	bool operator != (const Rectangle & other) const;
	bool operator < (const Rectangle & other) const;
	bool operator > (const Rectangle & other) const;
	bool operator <= (const Rectangle & other) const;
	bool operator >= (const Rectangle & other) const;
	static double getTotalArea();
	static double getTotalPerimeter();
	friend ofstream & operator << (ofstream & file, const Rectangle & smallShape);
	friend ostream & operator << (ostream & print, const Rectangle & smallShape);
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