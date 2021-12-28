#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

namespace SpaceComposedShape
{
class ComposedShape : public Shape{
public:
	ComposedShape();
	ComposedShape(const Rectangle & containerShape, const Rectangle & smallShape);
	ComposedShape(const Rectangle & containerShape, const Circle & smallShape);
	ComposedShape(const Rectangle & containerShape, const Triangle & smallShape);
	ComposedShape(const Circle & containerShape, const Rectangle & smallShape);
	ComposedShape(const Circle & containerShape, const Circle & smallShape);
	ComposedShape(const Circle & containerShape, const Triangle & smallShape);
	ComposedShape(const Triangle & containerShape, const Rectangle & smallShape);
	ComposedShape(const Triangle & containerShape, const Circle & smallShape);
	ComposedShape(const Triangle & containerShape, const Triangle & smallShape);
	void optimalFit(const Rectangle & containerShape, const Rectangle & smallShape);
	void optimalFit(const Rectangle & containerShape, const Circle & smallShape);
	void optimalFit(const Rectangle & containerShape, const Triangle & smallShape);
	void optimalFit(const Circle & containerShape, const Rectangle & smallShape);
	void optimalFit(const Circle & containerShape, const Circle & smallShape);
	void optimalFit(const Circle & containerShape, const Triangle & smallShape);
	void optimalFit(const Triangle & containerShape, const Rectangle & smallShape);
	void optimalFit(const Triangle & containerShape, const Circle & smallShape);
	void optimalFit(const Triangle & containerShape, const Triangle & smallShape);
	~ComposedShape();
	void clearComposedShape();
	const Shape * operator [] (int index) const;
	Shape * operator [] (int index);
	ComposedShape & operator += (Shape * smallShape);
	ofstream & draw(ofstream & file) const override;
	ofstream & drawSmall(ofstream & file) const override;
	ostream & printOut(ostream & print) const override;
	vector<Shape *> getSmallShapes() const;
	double getRestArea() const;
	int getTotalSmallShapes() const;
private:
	Shape * myContainerShape;
	vector<Shape *> mySmallShapes;
	double restContainerArea;
public:
	virtual double getPerimeter() const{return 0.0;}
	virtual double getArea() const{return 0.0;}
	virtual Shape & operator ++ (){return *myContainerShape;}
	virtual Shape & operator ++ (int ignoreMe){return *myContainerShape;}
	virtual Shape & operator -- (){return *myContainerShape;}
	virtual Shape & operator -- (int ignoreMe){return *myContainerShape;}
	virtual ofstream & drawContainer(ofstream & file) const{return file;}
};
}

#endif