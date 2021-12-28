



public class Test {
	
	public static void drive(){
		try{
			System.out.printf("Now, area and perimeter of the total rectangles are %s and %s.\n", Rectangle.totalArea(), Rectangle.totalPerimeter());
			Rectangle r1 = new Rectangle(30,40,3.0,4.0);
			Rectangle r2 = new Rectangle(50,60);
			System.out.printf("Area and perimeter of the total rectangles are %s and %s.\n", Rectangle.totalArea(), Rectangle.totalPerimeter());
			Rectangle r3 = new Rectangle(10,20);
			System.out.printf("Now, area and perimeter of the total rectangles are %s and %s.\n", Rectangle.totalArea(), Rectangle.totalPerimeter());
			System.out.printf("Coordinates of r1 are %f,%f.\n", r1.getX(), r1.getY());
			Shape rp1 = r1;
			rp1.increment();
			rp1.increment();
			System.out.printf("After double incrementation, coordinates of r1 are %f,%f.\n", r1.getX(), r1.getY());
			rp1.decrement();
			System.out.printf("After decrementation, coordinates of r1 are %f,%f.\n", r1.getX(), r1.getY());
			System.out.printf("r2 has a width of %d and has a height of %d.\n", r2.getWidth(),r2.getHeight());
			Rectangle r4;
			r4 = r2.add(15.0);
			System.out.printf("After double addition, r4 has a width of %d and has a height of %d.\n", r4.getWidth(),r4.getHeight());
			Rectangle r5 = new Rectangle(300,200);
			System.out.printf("Area and perimeter of the total rectangles are %s and %s.\n", Rectangle.totalArea(), Rectangle.totalPerimeter());
			r5.setWidth(50);
			r5.setHeight(80);
			System.out.printf("Now, area and perimeter of the total rectangles are %s and %s.\n", Rectangle.totalArea(), Rectangle.totalPerimeter());
			//Triangle and Circle objects also work this way.
			ComposedShape c1 = new ComposedShape(new Rectangle(470,280), new Rectangle(150,50));
			ComposedShape c2 = new ComposedShape(new Rectangle(420,400), new Rectangle(150,45));
			ComposedShape c3 = new ComposedShape(new Rectangle(400,300), new Circle(40));
			ComposedShape c4 = new ComposedShape(new Rectangle(300,400), new Triangle(120));
			ComposedShape c5 = new ComposedShape(new Circle(200), new Rectangle(60,80));
			ComposedShape c6 = new ComposedShape(new Circle(240), new Circle(80));
			ComposedShape c7 = new ComposedShape(new Circle(200), new Triangle(50));
			ComposedShape c8 = new ComposedShape(new Triangle(450), new Rectangle(60,90));
			ComposedShape c9 = new ComposedShape(new Triangle(420), new Circle(30));
			ComposedShape c10 = new ComposedShape(new Triangle(480), new Triangle(75));
			Shape[] sa = new Shape[10];
			sa[0] = c1; sa[1] = c2; sa[2] = c3; sa[3] = c4; sa[4] = c5;
			sa[5] = c6; sa[6] = c7; sa[7] = c8; sa[8] = c9; sa[9] = c10;
			ShapeHelper.printAll(sa);
			ShapeHelper.drawAll(sa);
			PolygonDyn p1 = new PolygonDyn(new Rectangle(200,100,50,50));
			PolygonDyn p2 = new PolygonDyn(new Circle(50,500,100));
			PolygonDyn p3 = new PolygonDyn(new Triangle(150,650,150,800,150,725,20));
			PolygonDyn p4 = new PolygonDyn(new Circle(120,220,320));
			PolygonDyn p5 = new PolygonDyn(new Rectangle(150,250,700,200));
			PolygonDyn p6 = new PolygonDyn(new Triangle(250,350,200,600,200,475,417));
			Shape[] sa2 = new Shape[6];
			sa2[0] = p1; sa2[1] = p2; sa2[2] = p3; sa2[3] = p4; sa2[4] = p5; sa2[5] = p6; 
			ShapeHelper.drawPoly(sa2);
			ShapeHelper.printAll(sa2);
			ComposedShape c11 = new ComposedShape(new Triangle(450), new Circle(110));
			c11.drawComposed();
			ComposedShape c12 = new ComposedShape(new Circle(200), new Triangle(75));
			c12.drawComposed();
			Rectangle rc1 = new Rectangle(10,20,0,120);
			Rectangle rc2 = new Rectangle(40,50,10,120);
			Rectangle rc3 = new Rectangle(100,70,50,120);
			Triangle tr1 = new Triangle(20,0,190);
			Triangle tr2 = new Triangle(40,20,190);
			Triangle tr3 = new Triangle(80,60,190);
			Circle cr1 = new Circle(30,30,300);
			Circle cr2 = new Circle(90,150,360);
			PolygonDyn pd0 = new PolygonDyn(new Circle(120,460,140));
			PolygonDyn pd1 = new PolygonDyn(new Circle(60,60,60));
			PolygonDyn pd2 = new PolygonDyn(new Rectangle(60,80,120,0));
			PolygonDyn pd3 = new PolygonDyn(new Triangle(100,180,0));
			PolygonDyn pd4 = new PolygonDyn(new Triangle(120,300,120,300,240,196,180));
			PolygonDyn pd5 = new PolygonDyn(new Rectangle(150,250,700,200));
			PolygonDyn pd6 = new PolygonDyn(new Triangle(120,720,40,720,160,824,100));
			PolygonDyn pd7 = new PolygonDyn(new Triangle(200,300,300));
			Shape[] sortarr = new Shape[16];
			sortarr[0] = rc1; sortarr[1] = rc2; sortarr[2] = rc3; sortarr[3] = tr1; sortarr[4] = tr2; sortarr[5] = tr3; 
			sortarr[6] = cr1; sortarr[7] = cr2; sortarr[8] = pd0; sortarr[9] = pd1; sortarr[10] = pd2; sortarr[11] = pd3; 
			sortarr[12] = pd4; sortarr[13] = pd5; sortarr[14] = pd6; sortarr[15] = pd7; 
			System.out.println("Area of the shapes with their index order:\n");
			for (int i = 0; i < sortarr.length; ++i)
				System.out.printf("%.2f  ", sortarr[i].area());
			System.out.println("\n\n");
			ShapeHelper.sortShapes(sortarr);
			System.out.println("Now, area of the shapes with their index order after sorting:");
			for (int i = 0; i < sortarr.length; ++i)
				System.out.printf("%.2f  ", sortarr[i].area());
			System.out.println("\n\n");
			ShapeHelper.drawAll(sortarr);
			ShapeHelper.drawPoly(sortarr);
			Polygon[] poly = ShapeHelper.convertAll(sortarr);
			ShapeHelper.drawPoly(poly);
		}
		catch(MyErrors me){
			me.what();
		}
	}
}
