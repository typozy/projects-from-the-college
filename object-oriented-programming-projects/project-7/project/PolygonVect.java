import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

/**
 * PolygonVect is a Polygon class that holds polygon coordinates 
 * in an ArrayList struct of Point2D objects
 * 
 * @author Tayfun
 *
 */
public class PolygonVect extends Polygon{
	private ArrayList<Point2D> points;
	
	public PolygonVect(){}
	
	public PolygonVect(Rectangle rect) throws MyErrors{
		Point2D p2d;
		double rx = rect.getX();
		double ry = rect.getY();
		if (rx < 0.0) rx = 0.0;
		if (ry < 0.0) ry = 0.0;
		p2d = new Point2D();
		p2d.setX(rx);
		p2d.setY(ry);
		points.add(p2d);
		p2d = new Point2D();
		p2d.setX(rx+rect.getWidth());
		p2d.setY(ry);
		points.add(p2d);
		p2d = new Point2D();
		p2d.setX(rx+rect.getWidth());
		p2d.setY(ry+rect.getHeight());
		points.add(p2d);
		p2d = new Point2D();
		p2d.setX(rx);
		p2d.setY(ry+rect.getHeight());
		points.add(p2d);
		area = rect.area();
		perimeter = rect.perimeter();
	}
	public PolygonVect(Circle circ) throws MyErrors{
		Point2D p2d;
		double cx = circ.getX();
		double cy = circ.getY();
		double r = circ.getRadius();
		if (cx < r) cx = r;
		if (cy < r) cy = r;
		for (int i=0; i<100; ++i){
			p2d = new Point2D();
			p2d.setX(cx+r*Math.cos(i*2.0*ShapeHelper.PI/100.0));
			p2d.setY(cy-r*Math.sin(i*2.0*ShapeHelper.PI/100.0));
			points.add(p2d);
		}
		area = circ.area();
		perimeter = circ.perimeter();
	}
	
	public PolygonVect(Triangle tria) throws MyErrors{
		Point2D p2d;
		double tempX = 0.0;
		if (tempX > tria.getX0()) tempX = tria.getX0();
		if (tempX > tria.getX1()) tempX = tria.getX1();
		if (tempX > tria.getX2()) tempX = tria.getX2();
		double tempY = 0.0;
		if (tempY > tria.getY0()) tempX = tria.getY0();
		if (tempY > tria.getY1()) tempX = tria.getY1();
		if (tempY > tria.getY2()) tempX = tria.getY2();
		p2d = new Point2D();
		p2d.setX(tria.getX0()-tempX);
		p2d.setY(tria.getY0()-tempY);
		points.add(p2d);
		p2d = new Point2D();
		p2d.setX(tria.getX1()-tempX);
		p2d.setY(tria.getY1()-tempY);
		points.add(p2d);
		p2d = new Point2D();
		p2d.setX(tria.getX2()-tempX);
		p2d.setY(tria.getY2()-tempY);
		points.add(p2d);
		area = tria.area();
		perimeter = tria.perimeter();
	}
	
	public PolygonVect(ArrayList<Point2D> arrlst2d) throws MyErrors{
		area = 0.0;
		perimeter = 0.0;
		Point2D p2d;
		for(int i=0; i<arrlst2d.size(); ++i){
			p2d = new Point2D();
			p2d.setX(arrlst2d.get(i).getX());
			p2d.setY(arrlst2d.get(i).getY());
			points.add(p2d);
		}
	}
	
	public PolygonVect(Point2D[] arr2d) throws MyErrors{
		area = 0.0;
		perimeter = 0.0;
		Point2D p2d;
		for(int i=0; i<arr2d.length; ++i){
			p2d = new Point2D();
			p2d.setX(arr2d[i].getX());
			p2d.setY(arr2d[i].getY());
			points.add(p2d);
		}
	}
	
	public PolygonVect(Point2D p2d) throws MyErrors{
		area = 0.0;
		perimeter = 0.0;
		Point2D temp2d = new Point2D();
		temp2d = new Point2D();
		temp2d.setX(p2d.getX());
		temp2d.setY(p2d.getY());
		points.add(temp2d);
	}
	
	public int size(){return points.size();}
	/**
	 * increment method increases x, y coordinates of all points by 1
	 * 
	 */
	public PolygonVect increment() throws MyErrors{
		for (int i = 0; i < points.size(); ++i){
			points.get(i).setX(points.get(i).getX()+1.0);
			points.get(i).setX(points.get(i).getX()+1.0);
		}
		return this;
	}
	
	public Point2D getPoint(int index){
		return points.get(index);
	}
	/**
	 * decrement method decreases x, y coordinates of all points by 1
	 * 
	 */
	public PolygonVect decrement() throws MyErrors{
		for (int i = 0; i < points.size(); ++i){
			if (points.get(i).getX() > 1.0)
				points.get(i).setX(points.get(i).getX()-1.0);
			else
				points.get(i).setX(0.0);
			if (points.get(i).getY() > 1.0)
				points.get(i).setY(points.get(i).getY()-1.0);
			else
				points.get(i).setY(0.0);
		}
		return this;
	}
	
	public void draw(Graphics g){
		int[] tempX = new int[points.size()];
		for(int i=0; i<points.size(); ++i)
			tempX[i] = (int)points.get(i).getX();
		int[] tempY = new int[points.size()];
		for(int i=0; i<points.size(); ++i)
			tempY[i] = (int)points.get(i).getY();
		g.setColor(Color.MAGENTA);
		g.fillPolygon(tempX,tempY,points.size());
		g.setColor(Color.BLACK);
		g.drawPolygon(tempX,tempY,points.size());
	}
	
	public void print(){
		System.out.printf("Your polygon vector has %d points.\n", points.size());
	}

}
