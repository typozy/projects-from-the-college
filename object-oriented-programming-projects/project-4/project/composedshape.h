#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

namespace SpaceComposedShape
{
class ComposedShape{
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
	const Polygon & operator [] (int index) const;
	Polygon & operator [] (int index);
	ComposedShape & operator += (const Polygon & smallShape);
	friend ofstream & operator << (ofstream & file, const ComposedShape & bigPicture);
	friend ostream & operator << (ostream & print, const ComposedShape & bigPicture);
	vector<Polygon> getSmallShapes() const;
	double getRestArea() const;
	int getTotalSmallShapes() const;
private:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				Polygon noPolygon;
	Polygon myContainerShape;
	vector<Polygon> mySmallShapes;
	double restContainerArea;
	int totalSmallShapes;
};
}

#endif