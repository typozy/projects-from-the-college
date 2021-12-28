import java.awt.Graphics;
import java.lang.Comparable;

/**
 * Shape is an interface that the other shapes from this one
 * Shape extends Comparable<Shape> interface to make a comparison between Shape objects
 * 
 * @author Tayfun
 *
 */

public interface Shape extends Comparable<Shape>{
	
	public double area();
	
	public double perimeter();
	
	public Shape increment() throws MyErrors;
	
	public Shape decrement() throws MyErrors;
	
	public void draw(Graphics g);
	
	public void print();

}
