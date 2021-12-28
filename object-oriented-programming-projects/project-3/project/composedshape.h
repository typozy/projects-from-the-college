#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

class ComposedShape{
public:
	class ShapeElem{
	public:
		ShapeElem();
		void setObjectType(Shape myShape);
		Shape getObjectType() const;
		void * getShapeObject() const;
		void setShapeObject(void * ptr);
		double getPerimeter() const;
		double getArea() const;
		friend ofstream & operator << (ofstream & file, const ShapeElem & smallShape);
		friend ostream & operator << (ostream & print, const ShapeElem & smallShape);
	private:
		void * shapeObject;
		Shape objectType;
	};
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
	void clearComposedShape();
	const ShapeElem & operator [] (int index) const;
	ShapeElem & operator [] (int index);
	ComposedShape & operator += (const ShapeElem & smallShape);
	friend ofstream & operator << (ofstream & file, const ComposedShape & bigPicture);
	friend ostream & operator << (ostream & print, const ComposedShape & bigPicture);
	vector<ShapeElem> getSmallShapes() const;
	double getRestArea() const;
	int getTotalSmallShapes() const;
private:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				ShapeElem noShape;
	ShapeElem myContainerShape;
	vector<ShapeElem> mySmallShapes;
	double restContainerArea;
	int totalSmallShapes;
	double hypotenus(double x1, double y1, double x2, double y2);
};

#endif