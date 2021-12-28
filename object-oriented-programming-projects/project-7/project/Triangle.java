import java.awt.Color;
import java.awt.Graphics;

/**
 * Triangle is a Shape class that holds triangle object
 * 
 * @author Tayfun
 *
 */
public class Triangle implements Shape{

	private int edge;
	
	private static double totalArea = 0.0;
	
	private static double totalPerimeter = 0.0;
	
	private double[] x;
	
	private double[] y;
	
	public Triangle() throws MyErrors{
		this(5,0.0,0.0);
	}
	
	public Triangle(int myEdge) throws MyErrors{
		this(myEdge,0.0,0.0);
	}
	
	public Triangle(int myEdge,double myX, double myY) throws MyErrors{
		this(myEdge,myX,myY+myEdge*Math.sqrt(3.0)/2.0,myX+myEdge/2.0,myY,myX+myEdge,myY+myEdge*Math.sqrt(3.0)/2.0);
	}
	
	Triangle(int myEdge, double myX1, double myY1, double myX2, double myY2, double myX3, double myY3) throws MyErrors{
		x = new double[3];
		y = new double[3];
		edge = myEdge;
		x[0] = myX1;
		y[0] = myY1;
		x[1] = myX2;
		y[1] = myY2;
		x[2] = myX3;
		y[2] = myY3;
		if (edge < 1)
			throw new MyErrors(-6);
		totalArea += area();
		totalPerimeter += perimeter();
	}
	
	public void setEdge(int myEdge) throws MyErrors{
		totalArea -= area();
		totalPerimeter -= perimeter();
		edge = myEdge;
		if (edge < 1)
			throw new MyErrors(-6);
		totalArea += area();
		totalPerimeter = perimeter();
	}
	
	public Triangle add(double d) throws MyErrors{
		Triangle t = new Triangle();
		t.setEdge(getEdge() + (int)d);
		return t;
	}
	
	public void setX0(double myX1){x[0] = myX1;}
	public void setY0(double myY1){y[0] = myY1;}
	public void setX1(double myX2){x[1] = myX2;}
	public void setY1(double myY2){y[1] = myY2;}
	public void setX2(double myX3){x[2] = myX3;}
	public void setY2(double myY3){y[2] = myY3;}
	public int getEdge() {return edge;}
	public double perimeter() {return edge*3.0;}
	public double area() {return edge*edge*Math.sqrt(3.0)/4.0;}
	public double getX0() {return x[0];}
	public double getY0() {return y[0];}
	public double getX1() {return x[1];}
	public double getY1() {return y[1];}
	public double getX2() {return x[2];}
	public double getY2() {return y[2];}
	public static double totalArea(){return totalArea;}
	public static double totalPerimeter(){return totalPerimeter;}
	public Triangle increment(){
		++x[0];
		++y[0];
		++x[1];
		++y[1];
		++x[2];
		++y[2];
		return this;
	}
	public Triangle decrement(){
		--x[0];
		--y[0];
		--x[1];
		--y[1];
		--x[2];
		--y[2];
		return this;
	}
	/**
	 * 
	 * draw draws the indicated shape on the screen
	 * its called from paintComponent method
	 * 
	 * @param g Graphics object passed from paintComponent method
	 * 
	 */
	public void draw(Graphics g){
		int[] tempX = new int[3];
		tempX[0] = (int)x[0];
		tempX[1] = (int)x[1];
		tempX[2] = (int)x[2];
		int[] tempY = new int[3];
		tempY[0] = (int)y[0];
		tempY[1] = (int)y[1];
		tempY[2] = (int)y[2];
		g.setColor(Color.MAGENTA);
		g.fillPolygon(tempX,tempY,3);
		g.setColor(Color.BLACK);
		g.drawPolygon(tempX,tempY,3);
	}
	
	public void print(){
		System.out.printf("Your triangle has an edge length of %d, has a perimeter length of %.2f and the area is %.2f.\n",getEdge(),perimeter(),area());
	}
	/**
	 * compareTo method compares two shape objects according to their areas
	 * 
	 * @param s another shape object to be compared
	 * @return an integer due to the result (<s -1, =s 0, >s 1)
	 */
	public int compareTo(Shape s){
		if(area()-s.area()<0.0001 && area()-s.area()>-0.0001)
			return 0;
		else if(area()-s.area()<0.0)
			return -1;
		else
			return 1;
	}
}