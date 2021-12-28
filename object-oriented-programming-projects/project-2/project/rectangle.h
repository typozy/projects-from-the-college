#ifndef RECTANGLE_H_
#define RECTANGLE_H_

class Rectangle{
public:
	Rectangle();
	Rectangle(int myWidth, int myHeight);
	Rectangle(int myWidth, int myHeight, double myX, double myY);
	void setWidth(int myWidth);
	void setHeight(int myHeight);
	void setX(double myX);
	void setY(double myY);
	int getWidth() const;
	int getHeight() const;
	double getX() const;
	double getY() const;
	ofstream & draw(ofstream & file) const;
	ofstream & drawContainer(ofstream & file) const;
	ofstream & drawSmall(ofstream & file) const;
private:
	int width;
	int height;
	double x;
	double y;
	void isWidthValid();
	void isHeightValid();
};

#endif