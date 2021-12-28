import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 * ShapeHelper is a class that compares/draws/sorts/converts to polygon given Shape objects
 * 
 * @author Tayfun
 *
 */
public class ShapeHelper {	
	
	public static final double PI = 3.1415;
	
	public static double hypotenus(double x1, double y1, double x2, double y2){
		return Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	}
	
	private static class Paint extends JPanel{
		
		private Shape[] shapes;
		private boolean paintPolygons;
		
		Paint(){}
		
		Paint(Shape[] s, boolean ifPolygon){
			shapes = s;
			paintPolygons = ifPolygon;
		}		
				
		public void paintComponent(Graphics g){
					
			super.paintComponent(g);
				
			if(paintPolygons){
				for(int i=0; i<shapes.length; ++i)
					if (shapes[i] instanceof PolygonDyn || shapes[i] instanceof PolygonVect)
						shapes[i].draw(g);
			}
			
			else{		
				for(int i=0; i<shapes.length; ++i)
					if (!(shapes[i] instanceof ComposedShape))
						shapes[i].draw(g);
			}

		}
			
	}
	/**
	 * drawAll draws all the shapes except any ComposedShape object on the screen
	 * any ComposedShape object is drawn on another screen 
	 * 
	 * @param s shape array to be drawn
	 * 
	 */
	public static void drawAll(Shape[] s){

		int count = 0;
		for(int i=0; i<s.length; ++i)
			if (s[i] instanceof ComposedShape){
				ComposedShape cs = (ComposedShape)s[i];
				cs.drawComposed();
				++count;
			}
		if(count < s.length) {
			JFrame frame = new JFrame("All Shapes");
			Paint painter = new Paint(s,false);
			frame.add(painter);
			frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			frame.setLocation(80,45);
			frame.setSize(960,540);
			frame.setResizable(false);
			frame.setVisible(true);
		}

	}
	/**
	 * drawPoly draws only any Polygon object on the screen
	 * 
	 * @param s shape array to be drawn
	 * 
	 */
	public static void drawPoly(Shape[] s){
		
		int count = 0;
		for(int i=0; i<s.length; ++i)
			if (s[i] instanceof PolygonDyn || s[i] instanceof PolygonVect)
				++count;
		if (count > 0) {
			JFrame frame = new JFrame("All Polygons");
			Paint painter = new Paint(s,true);
			frame.add(painter);
			frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			frame.setLocation(80,45);
			frame.setSize(960,540);
			frame.setResizable(false);
			frame.setVisible(true);
		}
	}
	/**
	 * printAll prints any Shape object's info on the screen
	 * 
	 * @param s shape array to be drawn
	 * 
	 */
	public static void printAll(Shape[] s){
		for(int i=0; i<s.length; ++i)
			s[i].print();
	}
	/**
	 * printAll converts all Shape objects to Polygon objects
	 * 
	 * @param s shape array to be drawn
	 * @return polygons as an array that are converted
	 * 
	 */
	public static Polygon[] convertAll(Shape[] s) throws MyErrors{
		int count = 0;
		for(int i=0; i<s.length; ++i)
			if(!(s[i] instanceof ComposedShape))
				++count;
		
		PolygonDyn[] poly = new PolygonDyn[count];
		
		count = 0;
		for(int i=0; i<s.length; ++i)
			if(!(s[i] instanceof ComposedShape)){
				if(s[i] instanceof Rectangle){
					Rectangle r = (Rectangle)s[i];
					poly[count] = new PolygonDyn(r);
					++count;
				}
				if(s[i] instanceof Circle){
					Circle c = (Circle)s[i];
					poly[count] = new PolygonDyn(c);
					++count;
				}
				if(s[i] instanceof Triangle){
					Triangle t = (Triangle)s[i];
					poly[count] = new PolygonDyn(t);
					++count;
				}
				if(s[i] instanceof PolygonDyn){
					PolygonDyn pd = (PolygonDyn)s[i];
					poly[count] = new PolygonDyn(pd);
					++count;
				}
				if(s[i] instanceof PolygonVect){
					PolygonVect pv = (PolygonVect)s[i];
					poly[count] = new PolygonDyn(pv);
					++count;
				}
			}
		return poly;
	}
	/**
	 * sortShapes sorts all Shape objects according to their areas
	 * 
	 * @param s shape array to be drawn
	 * 
	 */
	public static void sortShapes(Shape[] s){
		for (int i = 0; i < s.length-1; ++i){
			for (int j = i+1; j < s.length; ++j){
				if (s[i].compareTo(s[j]) > 0){
					Shape sp;
					sp = s[i];
					s[i] = s[j];
					s[j] = sp;
				}
			}
		}
	}
	
}
