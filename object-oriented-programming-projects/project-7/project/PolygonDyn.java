import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

/**
 * PolygonDyn is a Polygon class that holds polygon coordinates 
 * in an array of Point2D objects
 * 
 * @author Tayfun
 *
 */
public class PolygonDyn extends Polygon{
	private Point2D[] points;
	private int size;
	
	public PolygonDyn(){
		points = null;
		size = 0;
	}
	
	PolygonDyn(Rectangle rect) throws MyErrors{
		size = 4;
		points = new Point2D[size];
		double rx = rect.getX();
		double ry = rect.getY();
		if (rx < 0.0) rx = 0.0;
		if (ry < 0.0) ry = 0.0;
		points[0] = new Point2D();
		points[0].setX(rx);
		points[0].setY(ry);
		points[1] = new Point2D();
		points[1].setX(rx+rect.getWidth());
		points[1].setY(ry);
		points[2] = new Point2D();
		points[2].setX(rx+rect.getWidth());
		points[2].setY(ry+rect.getHeight());
		points[3] = new Point2D();
		points[3].setX(rx);
		points[3].setY(ry+rect.getHeight());
		area = rect.area();
		perimeter = rect.perimeter();
	}
	PolygonDyn(Circle circ) throws MyErrors{
		size = 100;
		points = new Point2D[size];
		double cx = circ.getX();
		double cy = circ.getY();
		double r = circ.getRadius();
		if (cx < r) cx = r;
		if (cy < r) cy = r;
		for (int i=0; i<100; ++i){
			points[i] = new Point2D();
			points[i].setX(cx+r*Math.cos(i*2.0*ShapeHelper.PI/100.0));
			points[i].setY(cy-r*Math.sin(i*2.0*ShapeHelper.PI/100.0));
		}
		area = circ.area();
		perimeter = circ.perimeter();
	}
	PolygonDyn(Triangle tria) throws MyErrors{
		size = 3;
		points = new Point2D[size];
		double tempX = 0.0;
		if (tempX > tria.getX0()) tempX = tria.getX0();
		if (tempX > tria.getX1()) tempX = tria.getX1();
		if (tempX > tria.getX2()) tempX = tria.getX2();
		double tempY = 0.0;
		if (tempY > tria.getY0()) tempX = tria.getY0();
		if (tempY > tria.getY1()) tempX = tria.getY1();
		if (tempY > tria.getY2()) tempX = tria.getY2();
		points[0] = new Point2D();
		points[0].setX(tria.getX0()-tempX);
		points[0].setY(tria.getY0()-tempY);
		points[1] = new Point2D();
		points[1].setX(tria.getX1()-tempX);
		points[1].setY(tria.getY1()-tempY);
		points[2] = new Point2D();
		points[2].setX(tria.getX2()-tempX);
		points[2].setY(tria.getY2()-tempY);
		area = tria.area();
		perimeter = tria.perimeter();
	}
	
	PolygonDyn(PolygonDyn polydyn) throws MyErrors{
		size = polydyn.points.length;
		points = new Point2D[size];
		for(int i=0; i<size; ++i){
			points[i] = new Point2D();
			points[i].setX(polydyn.points[i].getX());
			points[i].setY(polydyn.points[i].getY());
		}
	}
	
	PolygonDyn(PolygonVect polyvect) throws MyErrors{
		size = polyvect.size();
		points = new Point2D[size];
		for(int i=0; i<size; ++i){
			points[i] = new Point2D();
			points[i].setX(polyvect.getPoint(i).getX());
			points[i].setY(polyvect.getPoint(i).getY());
		}
	}
	
	public PolygonDyn(Point2D[] arr2d) throws MyErrors{
		size = arr2d.length;
		area = 0.0;
		perimeter = 0.0;
		points = new Point2D[size];
		for(int i=0; i<size; ++i){
			points[i] = new Point2D();
			points[i].setX(arr2d[i].getX());
			points[i].setY(arr2d[i].getY());
		}
	}
	
	public PolygonDyn(ArrayList<Point2D> arrlst2d) throws MyErrors{
		size = arrlst2d.size();
		area = 0.0;
		perimeter = 0.0;
		points = new Point2D[size];
		for(int i=0; i<size; ++i){
			points[i] = new Point2D();
			points[i].setX(arrlst2d.get(i).getX());
			points[i].setY(arrlst2d.get(i).getY());
		}
	}
	
	PolygonDyn(Point2D p2d) throws MyErrors{
		size = 1;
		area = 0.0;
		perimeter = 0.0;
		points = new Point2D[size];
		points[0] = new Point2D();
		points[0].setX(p2d.getX());
		points[0].setY(p2d.getY());
	}
	
	public int size(){return size;}
	


	public void draw(Graphics g){
		int[] tempX = new int[size];
		for(int i=0; i<size; ++i)
			tempX[i] = (int)points[i].getX();
		int[] tempY = new int[size];
		for(int i=0; i<size; ++i)
			tempY[i] = (int)points[i].getY();
		g.setColor(Color.MAGENTA);
		g.fillPolygon(tempX,tempY,size);
		g.setColor(Color.BLACK);
		g.drawPolygon(tempX,tempY,size);
	}
	
	public void print(){
		System.out.printf("Your dynamic polygon has %d points.\n",size);
	}
	/**
	 * increment method increases x, y coordinates of all points by 1
	 * 
	 */
	public PolygonDyn increment() throws MyErrors{
		for (int i = 0; i < size; ++i){
			points[i].setX(points[i].getX()+1.0);
			points[i].setX(points[i].getX()+1.0);
		}
		return this;
	}
	/**
	 * decrement method decreases x, y coordinates of all points by 1
	 * 
	 */
	public PolygonDyn decrement() throws MyErrors{
		for (int i = 0; i < size; ++i){
			if (points[i].getX() > 1.0)
				points[i].setX(points[i].getX()-1.0);
			else
				points[i].setX(0.0);
			if (points[i].getY() > 1.0)
				points[i].setY(points[i].getY()-1.0);
			else
				points[i].setY(0.0);
		}
		return this;
	}
}
