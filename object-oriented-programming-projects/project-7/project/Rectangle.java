import java.awt.Color;
import java.awt.Graphics;

/**
 * Rectangle is a Shape class that holds rectangle object
 * 
 * @author Tayfun
 *
 */
public class Rectangle implements Shape{

	private int width;
	private int height;
	private double x;
	private double y;
	private static double totalArea;
	private static double totalPerimeter;
	
	public Rectangle() throws MyErrors{
		this(5,5);
	}
	
	public Rectangle(int myWidth, int myHeight) throws MyErrors{
		this(myWidth,myHeight,0.0,0.0);
	}
	
	public Rectangle(int myWidth, int myHeight, double myX, double myY) throws MyErrors{
		x = myX;
		y = myY;
		width = myWidth;
		height = myHeight;
		if (width < 1) throw new MyErrors(-3);
		if (height < 1) throw new MyErrors(-4);
		totalArea += area();
		totalPerimeter += perimeter();
	}
	
	void setWidth(int myWidth) throws MyErrors{
		totalArea -= area();
		totalPerimeter -= perimeter();
		width = myWidth;
		if (width < 1)
			throw new MyErrors(-3);
		totalArea += area();
		totalPerimeter += perimeter();
	}
	void setHeight(int myHeight) throws MyErrors{
		totalArea -= area();
		totalPerimeter -= perimeter();
		height = myHeight;
		if (height < 1)
			throw new MyErrors(-4);
		totalArea += area();
		totalPerimeter += perimeter();
	}
	
	public Rectangle add(double d) throws MyErrors{
		Rectangle r = new Rectangle();
		r.setWidth(getWidth() + (int)d);
		r.setHeight(getHeight() + (int)d);
		return r;
	}
	
	public void setX(double myX){x = myX;}
	public void setY(double myY){y = myY;}
	public int getWidth() {return width;}
	public int getHeight() {return height;}
	public double perimeter() {return 2.0*width+2.0*height;}
	public double area() {return width*height;}
	public double getX() {return x;}
	public double getY() {return y;}
	public static double totalArea(){return totalArea;}
	public static double totalPerimeter(){return totalPerimeter;}
	
	public Rectangle increment(){
		++x;
		++y;
		return this;
	}
	public Rectangle decrement(){
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
		g.fillRect((int)x,(int)y,width,height);
		g.setColor(Color.BLACK);
		g.drawRect((int)x,(int)y,width,height);
	}
	
	public void print(){
		System.out.printf("Your rectangle has a width of %d and has a height of %d, has a perimeter length of %.2f and the area is %.2f.\n", getWidth(),getHeight(),perimeter(),area());
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
