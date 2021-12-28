import java.awt.Color;
import java.awt.Graphics;
/**
 * Circle is a Shape class that holds circle object
 * 
 * @author Tayfun
 *
 */

public class Circle implements Shape{
	
	private int radius;
	private double x;
	private double y;
	private static double totalArea;
	private static double totalPerimeter;
	
	Circle() throws MyErrors{
		this(5);
	}
	Circle(int myRadius) throws MyErrors{
		this(myRadius,myRadius,myRadius);
	}
	Circle(int myRadius, double myX, double myY) throws MyErrors{
		radius = myRadius;
		x = myX;
		y = myY;
		if (radius < 1)
			throw new MyErrors(-5);
		totalArea += area();
		totalPerimeter += perimeter();
	}
	
	void setRadius(int myRadius) throws MyErrors{
		totalArea -= area();
		totalPerimeter -= perimeter();
		if (radius < 1)
			throw new MyErrors(-5);
		totalArea += area();
		totalPerimeter += perimeter();
	}
	
	public Circle add(double d) throws MyErrors{
		Circle c = new Circle();
		c.setRadius(getRadius() + (int)d);
		return c;
	}
	
	public void setX(double myX){x = myX;}
	public void setY(double myY){y = myY;}
	public int getRadius() {return radius;}
	public double perimeter() {return 2.0*ShapeHelper.PI*radius;}
	public double area() {return ShapeHelper.PI*radius*radius;}
	public double getX() {return x;}
	public double getY() {return y;}
	public static double totalArea(){return totalArea;}
	public static double totalPerimeter(){return totalPerimeter;}
	
	public Circle increment(){
		++x;
		++y;
		return this;
	}
	
	public Circle decrement(){
		--x;
		--y;
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
		g.setColor(Color.MAGENTA);
		g.fillOval((int)(x-radius),(int)(y-radius),2*radius,2*radius);
		g.setColor(Color.BLACK);
		g.drawOval((int)(x-radius),(int)(y-radius),2*radius,2*radius);
	}
	
	public void print(){
		System.out.printf("Your circle has a radius of %d, has a perimeter length of %.2f and the area is %.2f.\n",getRadius(),perimeter(),area());
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
