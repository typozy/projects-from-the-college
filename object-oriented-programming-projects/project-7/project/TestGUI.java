import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class TestGUI {
	
	private static JFrame frame;
	private static JPanel panel;
	private static PaintGUI painter;
	private static JLabel text1;
	private static JLabel text2;
	private static JLabel text3;
	private static JLabel text4;
	private static JLabel text5;
	private static JLabel text6;
	private static JComboBox<String> box1;
	private static JComboBox<String> box2;
	private static JButton button;
	private static ButtonHandler handler;
	private static JTextField field1;
	private static JTextField field2;
	private static JTextField field3;
	private static JTextField field4;
	private static JOptionPane err;
	private static ComposedShape cs;

	private static class PaintGUI extends JPanel{
		
		public void paintComponent(Graphics g){
			
			super.paintComponent(g);
				
			cs.draw(g);
			
		}
	}
	
	private static class ButtonHandler implements ActionListener{
		public void actionPerformed(ActionEvent e){
			try{
				String conType = box1.getSelectedItem().toString();
				String smallType = box2.getSelectedItem().toString();
				int conWidth = Integer.parseInt(field1.getText().toString());
				int conHeight = 2;
				if(conType.equals("Rectangle"))
					conHeight = Integer.parseInt(field2.getText().toString());
				int smallWidth = Integer.parseInt(field3.getText().toString());
				int smallHeight = 2;
				if(smallType.equals("Rectangle"))
					smallHeight = Integer.parseInt(field4.getText().toString());
					
				if(conWidth > 540 || conWidth < 2 || smallWidth > 540 || smallWidth < 2)
					throw new MyErrors();
				if(conType.equals("Rectangle"))
					if(conHeight > 540 || conHeight < 2)
						throw new MyErrors();
				if(smallType.equals("Rectangle"))
					if(smallHeight > 540 || smallHeight < 2)
						throw new MyErrors();
					
				if(conType.equals("Rectangle") && smallType.equals("Rectangle"))
					cs = new ComposedShape(new Rectangle(conWidth,conHeight), new Rectangle(smallWidth,smallHeight));
				
				if(conType.equals("Rectangle") && smallType.equals("Circle"))
					cs = new ComposedShape(new Rectangle(conWidth,conHeight), new Circle(smallWidth/2));
				
				if(conType.equals("Rectangle") && smallType.equals("Triangle"))
					cs = new ComposedShape(new Rectangle(conWidth,conHeight), new Triangle(smallWidth));
				
				if(conType.equals("Circle") && smallType.equals("Rectangle"))
					cs = new ComposedShape(new Circle(conWidth/2), new Rectangle(smallWidth,smallHeight));
				
				if(conType.equals("Circle") && smallType.equals("Circle"))
					cs = new ComposedShape(new Circle(conWidth/2), new Circle(smallWidth/2));
				
				if(conType.equals("Circle") && smallType.equals("Triangle"))
					cs = new ComposedShape(new Circle(conWidth/2), new Triangle(smallWidth));
				
				if(conType.equals("Triangle") && smallType.equals("Rectangle"))
					cs = new ComposedShape(new Triangle(conWidth), new Rectangle(smallWidth,smallHeight));
				
				if(conType.equals("Triangle") && smallType.equals("Circle"))
					cs = new ComposedShape(new Triangle(conWidth), new Circle(smallWidth/2));
				
				if(conType.equals("Triangle") && smallType.equals("Triangle"))
					cs = new ComposedShape(new Triangle(conWidth), new Triangle(smallWidth));
				
				painter = new PaintGUI();
				painter.setLocation(0,111);
				painter.setSize(545,545);
				panel.repaint();
				
			}
			catch(MyErrors me){
				
				err.showMessageDialog(null, "\nPlease enter inputs in requested size!\n\n              ( >1 && <541 )\n ");
				
			}
			catch(Exception ex){
				
				err.showMessageDialog(null, "\nPlease enter numbers as inputs!\n ");
				
			}
		}
		
	}
	
	
	public static void drive(){
		try{
			frame = new JFrame("Draw Shapes");
			panel = new JPanel();
			panel.setLayout(null);
			panel.setBackground(Color.LIGHT_GRAY);
			
			text1 = new JLabel("Container Type");
			text1.setLocation(20,0);
			text1.setSize(100,50);
			box1 = new JComboBox<String>(new String[]{"Rectangle","Circle","Triangle"});
			box1.setLocation(120, 15);
			box1.setSize(85, 20);
			text2 = new JLabel("Small Type");
			text2.setLocation(220,0);
			text2.setSize(100,50);
			box2 = new JComboBox<String>(new String[]{"Rectangle","Circle","Triangle"});
			box2.setLocation(320, 15);
			box2.setSize(85, 20);
			button = new JButton("DRAW!");
			button.setLocation(430,40);
			button.setSize(85,30);
			
			text3 = new JLabel("Width/diameter/edge");
			text3.setLocation(20,30);
			text3.setSize(120,50);
			field1 = new JTextField();
			field1.setLocation(160,45);
			field1.setSize(40,20);
			text4 = new JLabel("Height (if necessary)");
			text4.setLocation(20,60);
			text4.setSize(120,50);
			field2 = new JTextField();
			field2.setLocation(160,75);
			field2.setSize(40,20);
			text5 = new JLabel("Width/diameter/edge");
			text5.setLocation(220,30);
			text5.setSize(120,50);
			field3 = new JTextField();
			field3.setLocation(360,45);
			field3.setSize(40,20);
			text6 = new JLabel("Height (if necessary)");
			text6.setLocation(220,60);
			text6.setSize(120,50);
			field4 = new JTextField();
			field4.setLocation(360,75);
			field4.setSize(40,20);
			
			cs = new ComposedShape(new Triangle(5000), new Circle(2500));
			painter = new PaintGUI();
			painter.setLocation(0,111);
			painter.setSize(545,545);
			
			err = new JOptionPane();
			
			handler = new ButtonHandler();
			button.addActionListener(handler);
			
			panel.add(text1);
			panel.add(box1);
			panel.add(text2);
			panel.add(box2);
			panel.add(button);
			panel.add(text3);
			panel.add(field1);
			panel.add(text4);
			panel.add(field2);
			panel.add(text5);
			panel.add(field3);
			panel.add(text6);
			panel.add(field4);
			panel.add(painter);
			
			frame.add(panel);
			
			frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			frame.setLocation(80,30);
			frame.setSize(547,681);
			frame.setResizable(false);
			frame.setVisible(true);

			
			
			
			
		}
		catch(MyErrors me){
			me.what();
		}
	}
}
