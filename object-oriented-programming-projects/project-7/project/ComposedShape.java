import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JFrame;
import javax.swing.JPanel;
/**
 * ComposedShape is a composition of shapes that holds a container shape and
 * small shape arrays that all fits in the container shape
 * @author Tayfun
 *
 */
public class ComposedShape implements Shape{
	
	private Shape myContainerShape;
	private Shape[] mySmallShapes;
	private double restContainerArea;
	
	private class PaintComp extends JPanel{
		
		public void paintComponent(Graphics g){
			
			super.paintComponent(g);
			
			drawContainer(g);
			
			for(int i=0; i<mySmallShapes.length; ++i)
				mySmallShapes[i].draw(g);
			
		}
	}
	
	/**
	 * any ComposedShape function makes a composed shape object depending on given container and small shape
	 * default constructor makes an empty rectangle
	 * 
	 * @throws MyErrors
	 */
	public ComposedShape() throws MyErrors{
		optimalFit(new Rectangle(1920,1080),new Rectangle(2000,1500));
	}

	public ComposedShape(Rectangle containerShape, Rectangle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);
	}

	public ComposedShape(Rectangle containerShape, Circle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);	
	}

	public ComposedShape(Rectangle containerShape, Triangle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);	
	}

	public ComposedShape(Circle containerShape, Rectangle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);	
	}

	public ComposedShape(Circle containerShape, Circle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);	
	}

	public ComposedShape(Circle containerShape, Triangle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);	
	}

	public ComposedShape(Triangle containerShape, Rectangle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);	
	}

	public ComposedShape(Triangle containerShape, Circle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);
	}

	public ComposedShape(Triangle containerShape, Triangle smallShape) throws MyErrors{
		optimalFit(containerShape,smallShape);
	}
	/**
	 * drawComposed method is used in the drawAll method of ShapeHelper class
	 * if there is any composed object, this method is called and the composed shape
	 * is drawn in a new frame
	 * 
	 */
	public void drawComposed(){
		
		JFrame frame = new JFrame("Composed Shape");
		PaintComp painter = new PaintComp();
		frame.add(painter);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setLocation(80,45);
		frame.setSize(540,540);
		frame.setResizable(false);
		frame.setVisible(true);

	}
	
	public void drawContainer(Graphics g){
		if(myContainerShape instanceof Rectangle){
			Rectangle myRectangle = (Rectangle)myContainerShape;
			g.setColor(Color.PINK);
			g.fillRect((int)myRectangle.getX(),(int)myRectangle.getY(),myRectangle.getWidth(),myRectangle.getHeight());
			g.setColor(Color.BLACK);
			g.drawRect((int)myRectangle.getX(),(int)myRectangle.getY(),myRectangle.getWidth(),myRectangle.getHeight());
		}
		if(myContainerShape instanceof Circle){
			Circle myCircle = (Circle)myContainerShape;
			g.setColor(Color.PINK);
			g.fillOval((int)(myCircle.getX()-myCircle.getRadius()),(int)(myCircle.getY()-myCircle.getRadius()),2*myCircle.getRadius(),2*myCircle.getRadius());
			g.setColor(Color.BLACK);
			g.drawOval((int)(myCircle.getX()-myCircle.getRadius()),(int)(myCircle.getY()-myCircle.getRadius()),2*myCircle.getRadius(),2*myCircle.getRadius());
		}
		if(myContainerShape instanceof Triangle){
			Triangle myTriangle = (Triangle)myContainerShape;
			int[] tempX = new int[3];
			tempX[0] = (int)myTriangle.getX0();
			tempX[1] = (int)myTriangle.getX1();
			tempX[2] = (int)myTriangle.getX2();
			int[] tempY = new int[3];
			tempY[0] = (int)myTriangle.getY0();
			tempY[1] = (int)myTriangle.getY1();
			tempY[2] = (int)myTriangle.getY2();
			g.setColor(Color.PINK);
			g.fillPolygon(tempX,tempY,3);
			g.setColor(Color.BLACK);
			g.drawPolygon(tempX,tempY,3);
		}
	}
	
	public void draw(Graphics g){
		
		drawContainer(g);
		
		for(int i=0; i<mySmallShapes.length; ++i)
			mySmallShapes[i].draw(g);
	
	}
	
	public void print(){
		System.out.printf("Your container shape has %d small shape/shapes. Rest area is %.2f.\n",mySmallShapes.length,restContainerArea);
	}
	
	public ComposedShape increment() throws MyErrors{
		throw new MyErrors(-7);
	}
	
	public ComposedShape decrement() throws MyErrors{
		throw new MyErrors(-7);
	}
	public double perimeter(){
		return myContainerShape.perimeter();
	}
	public double area(){
		return myContainerShape.area();
	}
	/**
	 * restArea method gives the rest area after max small shapes
	 * fit in the container
	 * 
	 */
	public double restArea(){
		return restContainerArea;
	}
	
	public int compareTo(Shape s){
		if(area()-s.area()<0.0001 && area()-s.area()>-0.0001)
			return 0;
		else if(area()-s.area()<0.0)
			return -1;
		else
			return 1;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/**
	 * any optimalFit function fits small shapes in the given container shape
	 * 
	 * @param containerShape given container shape
	 * @param smallShape given small shape to fit the container
	 * @throws MyErrors
	 */
	
	
	
	
	
	
	
	public void optimalFit(Rectangle containerShape, Rectangle smallShape) throws MyErrors{
		Rectangle containerRectangle = new Rectangle(containerShape.getWidth(),containerShape.getHeight());
		myContainerShape = containerRectangle;
		restContainerArea = containerShape.area();
		int mainHeight = containerShape.getHeight();
		int mainWidth = containerShape.getWidth();
		int smallHeight = smallShape.getHeight();
		int smallWidth = smallShape.getWidth();
		int i = 0, j = 0;
		int temp;
		if (smallHeight > smallWidth){
			temp = smallWidth;
			smallWidth = smallHeight;
			smallHeight = temp;
		}
		int count1 = 0;
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				++count1;
				i += smallWidth;
			}
			j += smallHeight;
		}
		int k = 0;
		while (mainWidth - k >= smallWidth)
			k += smallWidth;
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = k;
			while (mainWidth - i >= smallWidth){
				++count1;
				i += smallWidth;
			}
			j += smallHeight;
		}
		int count2 = 0;
		j = 0;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				++count2;
				i += smallWidth;
			}
			j += smallHeight;
		}
		k = 0;
		while (mainHeight - k >= smallHeight)
			k += smallHeight;
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		j = k;
		while (mainHeight - j >= smallHeight){
			i = 0;
			while (mainWidth - i >= smallWidth){
				++count2;
				i += smallWidth;
			}
			j += smallHeight;
		}
		Rectangle smallRectangles;
		int count = 0;
		if (count1 > count2){
			mySmallShapes = new Shape[count1];
			j = 0;
			while (mainHeight - j >= smallHeight){
				i = 0;
				while (mainWidth - i >= smallWidth){
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					mySmallShapes[count] = smallRectangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallWidth;
				}
				j += smallHeight;
			}
			k = 0;
			while (mainWidth - k >= smallWidth)
				k += smallWidth;
			temp = smallWidth;
			smallWidth = smallHeight;
			smallHeight = temp;
			j = 0;
			while (mainHeight - j >= smallHeight){
				i = k;
				while (mainWidth - i >= smallWidth){
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					mySmallShapes[count] = smallRectangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallWidth;
				}
				j += smallHeight;
			}
		}
		else{
			mySmallShapes = new Shape[count2];
			temp = smallWidth;
			smallWidth = smallHeight;
			smallHeight = temp;
			j = 0;
			while (mainHeight - j >= smallHeight){
				i = 0;
				while (mainWidth - i >= smallWidth){
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					mySmallShapes[count] = smallRectangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallWidth;
				}
				j += smallHeight;
			}
			k = 0;
			while (mainHeight - k >= smallHeight)
				k += smallHeight;
			temp = smallWidth;
			smallWidth = smallHeight;
			smallHeight = temp;
			j = k;
			while (mainHeight - j >= smallHeight){
				i = 0;
				while (mainWidth - i >= smallWidth){
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					mySmallShapes[count] = smallRectangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallWidth;
				}
				j += smallHeight;
			}
		}
	}

	public void optimalFit(Rectangle containerShape, Circle smallShape) throws MyErrors{
		Rectangle containerRectangle = new Rectangle(containerShape.getWidth(),containerShape.getHeight());
		myContainerShape = containerRectangle;
		restContainerArea = containerShape.area();
		int mainHeight = containerShape.getHeight();
		int mainWidth = containerShape.getWidth();
		int smallRadius = smallShape.getRadius();
		double distance = smallRadius*Math.sqrt(3.0);
		double i = 0.0, j = 0.0;
		int count1 = 0;
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				++count1;
				i += smallRadius*2;
			}
			j += smallRadius*2;
		}
		int count2 = 0;
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				++count2;
				i += smallRadius*2;
			}
			j += distance*2;
		}
		j = smallRadius+distance;
		while (mainHeight - j >= smallRadius){
			i = smallRadius*2;
			while (mainWidth - i >= smallRadius){
				++count2;
				i += smallRadius*2;
			}
			j += distance*2;
		}
		int count3 = 0;
		j = smallRadius;
		while (mainHeight - j >= smallRadius){
			i = smallRadius;
			while (mainWidth - i >= smallRadius){
				++count3;
				i += distance*2;
			}
			j += smallRadius*2;
		}
		j = smallRadius*2;
		while (mainHeight - j >= smallRadius){
			i = smallRadius+distance;
			while (mainWidth - i >= smallRadius){
				++count3;
				i += distance*2;
			}
			j += smallRadius*2;
		}
		Circle smallCircles;
		int count = 0;
		if(count1 >= count2 && count1 >= count3){
			mySmallShapes = new Shape[count1];
			j = smallRadius;
			while (mainHeight - j >= smallRadius){
				i = smallRadius;
				while (mainWidth - i >= smallRadius){
					smallCircles = new Circle(smallRadius,i,j);
					mySmallShapes[count] = smallCircles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallRadius*2;
				}
				j += smallRadius*2;
			}
		}
		else if(count2 >= count1 && count2 >= count3){
			mySmallShapes = new Shape[count2];
			j = smallRadius;
			while (mainHeight - j >= smallRadius){
				i = smallRadius;
				while (mainWidth - i >= smallRadius){
					smallCircles = new Circle(smallRadius,i,j);
					mySmallShapes[count] = smallCircles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallRadius*2;
				}
				j += distance*2;
			}
			j = smallRadius+distance;
			while (mainHeight - j >= smallRadius){
				i = smallRadius*2;
				while (mainWidth - i >= smallRadius){
					smallCircles = new Circle(smallRadius,i,j);
					mySmallShapes[count] = smallCircles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallRadius*2;
				}
				j += distance*2;
			}
		}
		else{
			mySmallShapes = new Shape[count3];
			j = smallRadius;
			while (mainHeight - j >= smallRadius){
				i = smallRadius;
				while (mainWidth - i >= smallRadius){
					smallCircles = new Circle(smallRadius,i,j);
					mySmallShapes[count] = smallCircles;
					restContainerArea -= smallShape.area();
					++count;
					i += distance*2;
				}
				j += smallRadius*2;
			}
			j = smallRadius*2;
			while (mainHeight - j >= smallRadius){
				i = smallRadius+distance;
				while (mainWidth - i >= smallRadius){
					smallCircles = new Circle(smallRadius,i,j);
					mySmallShapes[count] = smallCircles;
					restContainerArea -= smallShape.area();
					++count;
					i += distance*2;
				}
				j += smallRadius*2;
			}
		}
	}

	public void optimalFit(Rectangle containerShape, Triangle smallShape) throws MyErrors{
		Rectangle containerRectangle = new Rectangle(containerShape.getWidth(),containerShape.getHeight());
		myContainerShape = containerRectangle;
		restContainerArea = containerShape.area();
		int mainWidth = containerShape.getWidth();
		int mainHeight = containerShape.getHeight();
		int smallEdge = smallShape.getEdge();
		double i = 0.0, j = 0.0;
		double height = smallEdge*Math.sqrt(3.0)/2.0;
		int count1 = 0;
		j = 0.0;
		while (mainHeight - j >= height){
			i = 0.0;
			while (mainWidth - i >= smallEdge){
				++count1;
				i += smallEdge;
			}
			j += height;
		}
		j = height;
		while (mainHeight - j >= 0){
			i = smallEdge/2.0;
			while (mainWidth - i >= smallEdge){
				++count1;
				i += smallEdge;
			}
			j += height;
		}
		int count2 = 0;
		j = 0.0;
		while (mainHeight - j >= smallEdge){
			i = 0.0;
			while (mainWidth - i >= height){
				++count2;
				i += height;
			}
			j += smallEdge;
		}
		j = smallEdge;
		while (mainHeight - j >= smallEdge/2.0){
			i = 0.0;
			while (mainWidth - i >= height){
				++count2;
				i += height;
			}
			j += smallEdge;
		}
		Triangle smallTriangles;
		int count = 0;
		if (count1 > count2){
			mySmallShapes = new Shape[count1];
			j = 0.0;
			while (mainHeight - j >= height){
				i = 0.0;
				while (mainWidth - i >= smallEdge){
					smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j+height);
					mySmallShapes[count] = smallTriangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallEdge;
				}
				j += height;
			}
			j = height;
			while (mainHeight - j >= 0){
				i = smallEdge/2.0;
				while (mainWidth - i >= smallEdge){
					smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge,j,i+smallEdge/2.0,j-height);
					mySmallShapes[count] = smallTriangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallEdge;
				}
				j += height;
			}
		}
		else{
			mySmallShapes = new Shape[count2];
			j = 0.0;
			while (mainHeight - j >= smallEdge){
				i = 0.0;
				while (mainWidth - i >= height){
					smallTriangles = new Triangle(smallEdge,i,j,i,j+smallEdge,i+height,j+smallEdge/2.0);
					mySmallShapes[count] = smallTriangles;
					restContainerArea -= smallShape.area();
					++count;
					i += height;
				}
				j += smallEdge;
			}
			j = smallEdge;
			while (mainHeight - j >= smallEdge/2.0){
				i = 0.0;
				while (mainWidth - i >= height){
					smallTriangles = new Triangle(smallEdge,i,j,i+height,j-smallEdge/2.0,i+height,j+smallEdge/2.0);
					mySmallShapes[count] = smallTriangles;
					restContainerArea -= smallShape.area();
					++count;
					i += height;
				}
				j += smallEdge;
			}
		}
	}

	public void optimalFit(Circle containerShape, Rectangle smallShape) throws MyErrors{
		Circle containerCircle = new Circle(containerShape.getRadius());
		myContainerShape = containerCircle;
		restContainerArea = containerShape.area();
		int mainRadius = containerShape.getRadius();
		int smallWidth = smallShape.getWidth();
		int smallHeight = smallShape.getHeight();
		double i = 0.0, j = 0.0;
		double iOffset, jOffset;
		iOffset = mainRadius;
		jOffset = mainRadius;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		int count1 = 0;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					++count1;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
		iOffset = mainRadius + smallWidth/2.0;
		jOffset = mainRadius;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		int count2 = 0;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					++count2;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
		iOffset = mainRadius;
		jOffset = mainRadius + smallHeight/2.0;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		int count3 = 0;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					++count3;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
		iOffset = mainRadius + smallWidth/2.0;
		jOffset = mainRadius + smallHeight/2.0;
		while (iOffset >= 0)
			iOffset -= smallWidth;
		iOffset += smallWidth;
		while (jOffset >= 0)
			jOffset -= smallHeight;
		jOffset += smallHeight;
		int count4 = 0;
		j = jOffset;
		while (mainRadius*2 - j >= smallHeight){
			i = iOffset;
			while (mainRadius*2 - i >= smallWidth){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
				 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
					++count4;
				}
				i += smallWidth;
			}
			j += smallHeight;
		}
		Rectangle smallRectangles;
		int count = 0;
		if (count1 >= count2 && count1 >= count3 && count1 >= count4){
			mySmallShapes = new Shape[count1];
			iOffset = mainRadius;
			jOffset = mainRadius;
			while (iOffset >= 0)
				iOffset -= smallWidth;
			iOffset += smallWidth;
			while (jOffset >= 0)
				jOffset -= smallHeight;
			jOffset += smallHeight;
			j = jOffset;
			while (mainRadius*2 - j >= smallHeight){
				i = iOffset;
				while (mainRadius*2 - i >= smallWidth){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
					 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
						smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
						mySmallShapes[count] = smallRectangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallWidth;
				}
				j += smallHeight;
			}
		}
		else if (count2 >= count1 && count2 >= count3 && count2 >= count4){
			mySmallShapes = new Shape[count2];
			iOffset = mainRadius + smallWidth/2.0;
			jOffset = mainRadius;
			while (iOffset >= 0)
				iOffset -= smallWidth;
			iOffset += smallWidth;
			while (jOffset >= 0)
				jOffset -= smallHeight;
			jOffset += smallHeight;
			j = jOffset;
			while (mainRadius*2 - j >= smallHeight){
				i = iOffset;
				while (mainRadius*2 - i >= smallWidth){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
					 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
						smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
						mySmallShapes[count] = smallRectangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallWidth;
				}
				j += smallHeight;
			}
		}
		else if (count3 >= count1 && count3 >= count2 && count3 >= count4){
			mySmallShapes = new Shape[count3];
			iOffset = mainRadius;
			jOffset = mainRadius + smallHeight/2.0;
			while (iOffset >= 0)
				iOffset -= smallWidth;
			iOffset += smallWidth;
			while (jOffset >= 0)
				jOffset -= smallHeight;
			jOffset += smallHeight;
			j = jOffset;
			while (mainRadius*2 - j >= smallHeight){
				i = iOffset;
				while (mainRadius*2 - i >= smallWidth){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
					 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
						smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
						mySmallShapes[count] = smallRectangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallWidth;
				}
				j += smallHeight;
			}
		}
		else{
			mySmallShapes = new Shape[count4];
			iOffset = mainRadius + smallWidth/2.0;
			jOffset = mainRadius + smallHeight/2.0;
			while (iOffset >= 0)
				iOffset -= smallWidth;
			iOffset += smallWidth;
			while (jOffset >= 0)
				jOffset -= smallHeight;
			jOffset += smallHeight;
			j = jOffset;
			while (mainRadius*2 - j >= smallHeight){
				i = iOffset;
				while (mainRadius*2 - i >= smallWidth){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i,j+smallHeight,mainRadius,mainRadius) <= mainRadius &&
					 ShapeHelper.hypotenus(i+smallWidth,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallWidth,j+smallHeight,mainRadius,mainRadius) <= mainRadius){
						smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
						mySmallShapes[count] = smallRectangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallWidth;
				}
				j += smallHeight;
			}
		}
	}

	public void optimalFit(Circle containerShape, Circle smallShape) throws MyErrors{
		Circle containerCircle = new Circle(containerShape.getRadius());
		myContainerShape = containerCircle;
		restContainerArea = containerShape.area();
		int mainRadius = containerShape.getRadius();
		int smallRadius = smallShape.getRadius();
		double height60 = smallRadius*Math.sqrt(2.9999);
		double i = 0.0, j = 0.0;
		i = mainRadius;
		j = smallRadius;
		int count1 = 0;
		while (mainRadius*2 - j >= smallRadius){
			while (i >= smallRadius)
				i -= 2*height60;
			i += 2*height60;
			while (mainRadius*2 - i >= smallRadius){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
					++count1;
				}
				i += 2*height60;
			}
			i += height60;
			j += smallRadius;
		}
		i = mainRadius;
		j = smallRadius;
		int count2 = 0;
		while (mainRadius*2 - j >= smallRadius){
			while (i >= smallRadius)
				i -= 2*smallRadius;
			i += 2*smallRadius;
			while (mainRadius*2 - i >= smallRadius){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
					++count2;
				}
				i += 2*smallRadius;
			}
			i += smallRadius;
			j += height60;
		}
		Circle smallCircles;
		int count = 0;
		if (count1 > count2){
			mySmallShapes = new Shape[count1];
			i = mainRadius;
			j = smallRadius;
			while (mainRadius*2 - j >= smallRadius){
				while (i >= smallRadius)
					i -= 2*height60;
				i += 2*height60;
				while (mainRadius*2 - i >= smallRadius){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
						smallCircles = new Circle(smallRadius,i,j);
						mySmallShapes[count] = smallCircles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += 2*height60;
				}
				i += height60;
				j += smallRadius;
			}
		}
		else{
			mySmallShapes = new Shape[count2];
			i = mainRadius;
			j = smallRadius;
			while (mainRadius*2 - j >= smallRadius){
				while (i >= smallRadius)
					i -= 2*smallRadius;
				i += 2*smallRadius;
				while (mainRadius*2 - i >= smallRadius){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius-smallRadius){
						smallCircles = new Circle(smallRadius,i,j);
						mySmallShapes[count] = smallCircles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += 2*smallRadius;
				}
				i += smallRadius;
				j += height60;
			}
		}
	}

	public void optimalFit(Circle containerShape, Triangle smallShape) throws MyErrors{
		Circle containerCircle = new Circle(containerShape.getRadius());
		myContainerShape = containerCircle;
		restContainerArea = containerShape.area();
		int mainRadius = containerShape.getRadius();
		int smallEdge = smallShape.getEdge();
		double height60 = smallEdge*Math.sqrt(2.9999)/2.0;
		double i = 0.0, j = 0.0;
		i = mainRadius;
		j = 0.0;
		int count1 = 0;
		while (i >= smallEdge/2.0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= smallEdge/2.0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge/2.0){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
					++count1;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
		i = mainRadius;
		j = 0.0;
		while (i >= 0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= 0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					++count1;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
		i = mainRadius;
		j = mainRadius;
		int count2 = 0;
		while (j >= 0){
			i -= smallEdge/2.0;
			j -= height60;
		}
		i += smallEdge/2.0;
		j += height60;
		while (i >= smallEdge/2.0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= smallEdge/2.0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge/2.0){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
					++count2;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
		i = mainRadius;
		j = mainRadius;
		while (j >= 0){
			i -= smallEdge/2.0;
			j -= height60;
		}
		i += smallEdge/2.0;
		j += height60;
		while (i >= 0)
			i -= smallEdge;
		i += smallEdge;
		while (mainRadius*2 - j >= height60){
			while (i >= 0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - i >= smallEdge){
				if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
					++count2;
				}
				i += smallEdge;
			}
			i += smallEdge/2.0;
			j += height60;
		}
		Triangle smallTriangles;
		int count = 0;
		if (count1 > count2){
			mySmallShapes = new Shape[count1];
			i = mainRadius;
			j = 0.0;
			while (i >= smallEdge/2.0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - j >= height60){
				while (i >= smallEdge/2.0)
					i -= smallEdge;
				i += smallEdge;
				while (mainRadius*2 - i >= smallEdge/2.0){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
						smallTriangles = new Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60);
						mySmallShapes[count] = smallTriangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallEdge;
				}
				i += smallEdge/2.0;
				j += height60;
			}
			i = mainRadius;
			j = 0.0;
			while (i >= 0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - j >= height60){
				while (i >= 0)
					i -= smallEdge;
				i += smallEdge;
				while (mainRadius*2 - i >= smallEdge){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
						smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j);
						mySmallShapes[count] = smallTriangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallEdge;
				}
				i += smallEdge/2.0;
				j += height60;
			}
		}
		else{
			mySmallShapes = new Shape[count2];
			i = mainRadius;
			j = mainRadius;
			while (j >= 0){
				i -= smallEdge/2.0;
				j -= height60;
			}
			i += smallEdge/2.0;
			j += height60;
			while (i >= smallEdge/2.0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - j >= height60){
				while (i >= smallEdge/2.0)
					i -= smallEdge;
				i += smallEdge;
				while (mainRadius*2 - i >= smallEdge/2.0){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i-smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius){
						smallTriangles = new Triangle(smallEdge,i,j,i-smallEdge/2.0,j+height60,i+smallEdge/2.0,j+height60);
						mySmallShapes[count] = smallTriangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallEdge;
				}
				i += smallEdge/2.0;
				j += height60;
			}
			i = mainRadius;
			j = mainRadius;
			while (j >= 0){
				i -= smallEdge/2.0;
				j -= height60;
			}
			i += smallEdge/2.0;
			j += height60;
			while (i >= 0)
				i -= smallEdge;
			i += smallEdge;
			while (mainRadius*2 - j >= height60){
				while (i >= 0)
					i -= smallEdge;
				i += smallEdge;
				while (mainRadius*2 - i >= smallEdge){
					if (ShapeHelper.hypotenus(i,j,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge/2.0,j+height60,mainRadius,mainRadius) <= mainRadius && ShapeHelper.hypotenus(i+smallEdge,j,mainRadius,mainRadius) <= mainRadius){
						smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+height60,i+smallEdge,j);
						mySmallShapes[count] = smallTriangles;
						restContainerArea -= smallShape.area();
						++count;
					}
					i += smallEdge;
				}
				i += smallEdge/2.0;
				j += height60;
			}
		}
	}

	public void optimalFit(Triangle containerShape, Rectangle smallShape) throws MyErrors{
		Triangle containerTriangle = new Triangle(containerShape.getEdge());
		myContainerShape = containerTriangle;
		restContainerArea = containerShape.area();
		int mainEdge = containerShape.getEdge();
		int smallWidth = smallShape.getWidth();
		int smallHeight = smallShape.getHeight();
		double mainHeight = mainEdge*Math.sqrt(3.0)/2.0;
		double i = 0.0, j = 0.0;
		double iOffset = 0.0, iWall = 0.0;
		iOffset = smallHeight/Math.sqrt(3.0);
		iWall = mainEdge - smallHeight/Math.sqrt(3.0);
		int count1 = 0;
		j = mainHeight - smallHeight;
		while (j >= 0){
			i = iOffset;
			while (i <= iWall-smallWidth){
				++count1;
				i += smallWidth;
			}
			iOffset += smallHeight/Math.sqrt(3.0);
			iWall -= smallHeight/Math.sqrt(3.0);
			j -= smallHeight;
		}
		int temp;
		temp = smallWidth;
		smallWidth = smallHeight;
		smallHeight = temp;
		iOffset = smallHeight/Math.sqrt(3.0);
		iWall = mainEdge - smallHeight/Math.sqrt(3.0);
		int count2 = 0;
		j = mainHeight - smallHeight;
		while (j >= 0){
			i = iOffset;
			while (i <= iWall-smallWidth){
				++count2;
				i += smallWidth;
			}
			iOffset += smallHeight/Math.sqrt(3.0);
			iWall -= smallHeight/Math.sqrt(3.0);
			j -= smallHeight;
		}
		Rectangle smallRectangles;
		int count = 0;
		if (count1 > count2){
			mySmallShapes = new Shape[count1];
			temp = smallWidth;
			smallWidth = smallHeight;
			smallHeight = temp;
			iOffset = smallHeight/Math.sqrt(3.0);
			iWall = mainEdge - smallHeight/Math.sqrt(3.0);
			j = mainHeight - smallHeight;
			while (j >= 0){
				i = iOffset;
				while (i <= iWall-smallWidth){
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					mySmallShapes[count] = smallRectangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallWidth;
				}
				iOffset += smallHeight/Math.sqrt(3.0);
				iWall -= smallHeight/Math.sqrt(3.0);
				j -= smallHeight;
			}
		}
		else{
			mySmallShapes = new Shape[count2];
			iOffset = smallHeight/Math.sqrt(3.0);
			iWall = mainEdge - smallHeight/Math.sqrt(3.0);
			j = mainHeight - smallHeight;
			while (j >= 0){
				i = iOffset;
				while (i <= iWall-smallWidth){
					smallRectangles = new Rectangle(smallWidth,smallHeight,i,j);
					mySmallShapes[count] = smallRectangles;
					restContainerArea -= smallShape.area();
					++count;
					i += smallWidth;
				}
				iOffset += smallHeight/Math.sqrt(3.0);
				iWall -= smallHeight/Math.sqrt(3.0);
				j -= smallHeight;
			}
		}
	}

	public void optimalFit(Triangle containerShape, Circle smallShape) throws MyErrors{
		Triangle containerTriangle = new Triangle(containerShape.getEdge());
		myContainerShape = containerTriangle;
		restContainerArea = containerShape.area();
		int mainEdge = containerShape.getEdge();
		int smallRadius = smallShape.getRadius();
		double mainHeight = mainEdge*Math.sqrt(3.0)/2.0;
		double i = 0.0, j = 0.0;
		double iOffset = 0.0, iWall = 0.0;
		int count = 0;
		iOffset = smallRadius*Math.sqrt(3.0);
		iWall = mainEdge;
		j = mainHeight - smallRadius;
		while (j >= smallRadius*2){
			i = iOffset;
			while (iWall - i >= smallRadius*Math.sqrt(3.0)){
				++count;
				i += smallRadius*2;
			}
			iOffset += smallRadius;
			iWall -= smallRadius;
			j -= smallRadius*Math.sqrt(3.0);
		}
		Circle smallCircles;
		mySmallShapes = new Shape[count];
		count = 0;
		iOffset = smallRadius*Math.sqrt(3.0);
		iWall = mainEdge;
		j = mainHeight - smallRadius;
		while (j >= smallRadius*2){
			i = iOffset;
			while (iWall - i >= smallRadius*Math.sqrt(3.0)){
				smallCircles = new Circle(smallRadius,i,j);
				mySmallShapes[count] = smallCircles;
				restContainerArea -= smallShape.area();
				++count;
				i += smallRadius*2;
			}
			iOffset += smallRadius;
			iWall -= smallRadius;
			j -= smallRadius*Math.sqrt(3.0);
		}
	}

	public void optimalFit(Triangle containerShape, Triangle smallShape) throws MyErrors{
		Triangle containerTriangle = new Triangle(containerShape.getEdge());
		myContainerShape = containerTriangle;
		restContainerArea = containerShape.area();
		int mainEdge = containerShape.getEdge();
		int smallEdge = smallShape.getEdge();
		double mainHeight = mainEdge*Math.sqrt(3.0)/2.0;
		double smallHeight = smallEdge*Math.sqrt(2.9999)/2.0;
		double i = 0.0, j = 0.0;
		double iOffset = 0.0, iWall = 0.0;
		int count = 0;
		iOffset = 0.0;
		iWall = mainEdge;
		j = mainHeight;
		while (j >= smallHeight){
			i = iOffset;
			while (i <= iWall-smallEdge){
				++count;
				i += smallEdge;
			}
			iOffset += smallEdge/2.0;
			iWall -= smallEdge/2.0;
			j -= smallHeight;
		}
		iOffset = smallEdge/2.0;
		iWall = mainEdge - smallEdge/2.0;
		j = mainHeight - smallHeight;
		while (j >= smallHeight){
			i = iOffset;
			while (i <= iWall-smallEdge){
				++count;
				i += smallEdge;
			}
			iOffset += smallEdge/2.0;
			iWall -= smallEdge/2.0;
			j -= smallHeight;
		}
		Triangle smallTriangles;
		mySmallShapes = new Shape[count];
		count = 0;
		iOffset = 0.0;
		iWall = mainEdge;
		j = mainHeight;
		while (j >= smallHeight){
			i = iOffset;
			while (i <= iWall-smallEdge){
				smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j-smallHeight,i+smallEdge,j);
				mySmallShapes[count] = smallTriangles;
				restContainerArea -= smallShape.area();
				++count;
				i += smallEdge;
			}
			iOffset += smallEdge/2.0;
			iWall -= smallEdge/2.0;
			j -= smallHeight;
		}
		iOffset = smallEdge/2.0;
		iWall = mainEdge - smallEdge/2.0;
		j = mainHeight - smallHeight;
		while (j >= smallHeight){
			i = iOffset;
			while (i <= iWall-smallEdge){
				smallTriangles = new Triangle(smallEdge,i,j,i+smallEdge/2.0,j+smallHeight,i+smallEdge,j);
				mySmallShapes[count] = smallTriangles;
				restContainerArea -= smallShape.area();
				++count;
				i += smallEdge;
			}
			iOffset += smallEdge/2.0;
			iWall -= smallEdge/2.0;
			j -= smallHeight;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
