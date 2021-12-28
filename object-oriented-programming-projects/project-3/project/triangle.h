#ifndef TRIANGLE_H_
#define TRIANGLE_H_

class Triangle{
public:
	Triangle();
	Triangle(int myEdge);
	Triangle(int myEdge, double myX1, double myY1, double myX2, double myY2, double myX3, double myY3);
	void setEdge(int myEdge);
	void setX1(double myX1);
	void setY1(double myY1);
	void setX2(double myX2);
	void setY2(double myY2);
	void setX3(double myX3);
	void setY3(double myY3);
	int getEdge() const;
	double getPerimeter() const;
	double getArea() const;
	double getX1() const;
	double getY1() const;
	double getX2() const;
	double getY2() const;
	double getX3() const;
	double getY3() const;
	Triangle operator ++ ();
	Triangle operator ++ (int ignoreMe);
	Triangle operator -- ();
	Triangle operator -- (int ignoreMe);
	const Triangle operator + (double mySize) const;
	const Triangle operator - (double mySize) const;
	friend const Triangle operator + (double mySize, const Triangle & myTriangle);
	friend const Triangle operator - (double mySize, const Triangle & myTriangle);
	bool operator == (const Triangle & other) const;
	bool operator != (const Triangle & other) const;
	bool operator < (const Triangle & other) const;
	bool operator > (const Triangle & other) const;
	bool operator <= (const Triangle & other) const;
	bool operator >= (const Triangle & other) const;
	static double getTotalArea();
	static double getTotalPerimeter();
	friend ofstream & operator << (ofstream & file, const Triangle & smallShape);
	friend ostream & operator << (ostream & print, const Triangle & smallShape);
	ofstream & drawContainer(ofstream & file) const;
	ofstream & drawSmall(ofstream & file) const;
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

#endif