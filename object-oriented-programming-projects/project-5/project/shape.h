#ifndef SHAPE_H_
#define SHAPE_H_

namespace SpaceShape
{
class Shape{
public:
	friend void printAll(const vector<Shape *> & shapeVec);
	friend void printPoly(const vector<Shape *> & shapeVec);
	friend vector<Shape *> convertAll(const vector<Shape *> & shapeVec);
	friend void sortShapes(vector<Shape *> & shapeVec);
	virtual double getPerimeter() const = 0;
	virtual double getArea() const = 0;
	virtual Shape & operator ++ () = 0;
	virtual Shape & operator ++ (int ignoreMe) = 0;
	virtual Shape & operator -- () = 0;
	virtual Shape & operator -- (int ignoreMe) = 0;
	bool operator == (const Shape & other) const;
	bool operator != (const Shape & other) const;
	bool operator < (const Shape & other) const;
	bool operator > (const Shape & other) const;
	bool operator <= (const Shape & other) const;
	bool operator >= (const Shape & other) const;
	friend ofstream & operator << (ofstream & file, const Shape & sh);
	friend ostream & operator << (ostream & print, const Shape & sh);
	virtual ofstream & draw(ofstream & file) const = 0;
	virtual ofstream & drawContainer(ofstream & file) const = 0;
	virtual ofstream & drawSmall(ofstream & file) const = 0;
	virtual ostream & printOut(ostream & print) const = 0;
	virtual ~Shape(){}
};
}

#endif