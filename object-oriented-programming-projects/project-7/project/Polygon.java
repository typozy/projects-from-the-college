/**
 * Polygon is an abstract class that PolygonDyn and PolygonVect derives from this class
 * 
 * @author Tayfun
 *
 */

public abstract class Polygon implements Shape{
	/**
	 * Point2D is an inner class for any polygon object that 
	 * holds the coordinates of a point 
	 * 
	 * @author Tayfun
	 *
	 */
	public class Point2D
	{
		protected double x;
		protected double y;
		public Point2D() throws MyErrors{
			this(0.0,0.0);
		}
		public Point2D(double myX, double myY) throws MyErrors{
			x = myX;
			y = myY;
			if (x < 0.0) throw new MyErrors(-2);
			if (y < 0.0) throw new MyErrors(-2);
		}
		public double getX(){return x;}
		public double getY(){return y;}
		public void setX(double myX) throws MyErrors{
			x = myX;
			if (x < 0.0) throw new MyErrors(-2);
		}
		public void setY(double myY) throws MyErrors{
			y = myY;
			if (y < 0.0) throw new MyErrors(-2);
		}

	}
	
	protected double area;
	protected double perimeter;
	
	
	
	public double area(){return area;}
	public double perimeter(){return perimeter;}

	public abstract int size();
	/**
	 *compareTo method compares two Shape objects depending on their areas
	 * 
	 *@param s Shape object
	 *@return an integer depending on the result of the comparison
	 *
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
