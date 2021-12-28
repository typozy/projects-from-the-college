package com.company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class View implements ActionListener, CountObserver, PaintObserver {
    private Controller controller;
    private Model model;
    private JFrame viewFrame;
    private JPanel viewPanel;
    private JPanel paintPanel;
    private JOptionPane err;

    private JLabel text1;
    private JLabel text2;
    private JLabel text3;
    private JLabel text4;
    private JLabel text5;
    private JLabel text6;
    private JLabel text7;
    private JLabel text8;
    private JLabel text9;
    private JLabel text10;
    private JLabel text11;
    private JLabel text12;
    private JLabel text13;
    private JLabel text14;
    private JLabel text15;
    private JLabel text16;
    private JLabel text17;
    private JLabel text18;
    private JLabel text19;
    private JLabel text20;
    private JLabel text21;
    private JComboBox<String> box2;
    private JComboBox<String> box3;
    private JComboBox<String> box4;
    private JButton button1;
    private JButton button2;
    private JTextField field1;
    private JTextField field2;

    public View(Controller controller, Model model) {
        this.controller = controller;
        this.model = model;
        model.registerPaintObserver(this);
        model.registerCountObserver(this);
    }

    public void create() {
        viewFrame = new JFrame("ViewFrame");
        viewPanel = new JPanel();
        viewPanel.setLayout(null);
        viewPanel.setBackground(Color.LIGHT_GRAY);
        paintPanel = new JPanel();
        paintPanel.setLocation(5, 5);
        paintPanel.setSize(1000, 600);
        paintPanel.setLayout(null);


        text1 = new JLabel("Speed (pxs/sec)");
        text1.setLocation(1020, 0);
        text1.setSize(100, 50);
        field2 = new JTextField();
        field2.setLocation(1120, 15);
        field2.setSize(85, 20);
        text2 = new JLabel("Spreading Factor");
        text2.setLocation(1020, 30);
        text2.setSize(100, 50);
        box2 = new JComboBox<String>(new String[]{"0.5", "0.6", "0.7", "0.8", "0.9", "1.0"});
        box2.setLocation(1120, 45);
        box2.setSize(85, 20);
        text3 = new JLabel("Mortality Rate");
        text3.setLocation(1020, 60);
        text3.setSize(120, 50);
        box3 = new JComboBox<String>(new String[]{"0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9"});
        box3.setLocation(1120, 75);
        box3.setSize(85, 20);
        text4 = new JLabel("Population Count");
        text4.setLocation(1020, 90);
        text4.setSize(120, 50);
        field1 = new JTextField();
        field1.setLocation(1120, 105);
        field1.setSize(85, 20);

        text5 = new JLabel("Simulation Speed");
        text5.setLocation(1020, 120);
        text5.setSize(100, 50);
        box4 = new JComboBox<String>(new String[]{"1x", "2x", "4x", "5x", "10x", "20x", "25x", "50x", "100x"});
        box4.setLocation(1120, 135);
        box4.setSize(85, 20);

        button1 = new JButton("START");
        button1.setLocation(1020, 165);
        button1.setSize(80, 35);
        button1.addActionListener(this::actionPerformed);
        button2 = new JButton("PAUSE");
        button2.setLocation(1120, 165);
        button2.setSize(80, 35);
        button2.setEnabled(false);
        button2.addActionListener(this::actionPerformed);

        text6 = new JLabel("Healthy People:");
        text6.setLocation(1020, 210);
        text6.setSize(160, 50);
        text7 = new JLabel("0");
        text7.setLocation(1180, 210);
        text7.setSize(120, 50);
        text8 = new JLabel("Infecting People:");
        text8.setLocation(1020, 240);
        text8.setSize(160, 50);
        text9 = new JLabel("0");
        text9.setLocation(1180, 240);
        text9.setSize(120, 50);
        text10 = new JLabel("Infected People:");
        text10.setLocation(1020, 270);
        text10.setSize(160, 50);
        text11 = new JLabel("0");
        text11.setLocation(1180, 270);
        text11.setSize(120, 50);
        text12 = new JLabel("Patients Waits In Hospital:");
        text12.setLocation(1020, 300);
        text12.setSize(160, 50);
        text13 = new JLabel("0");
        text13.setLocation(1180, 300);
        text13.setSize(120, 50);
        text14 = new JLabel("Patients Using Ventilator:");
        text14.setLocation(1020, 330);
        text14.setSize(160, 50);
        text15 = new JLabel("0");
        text15.setLocation(1180, 330);
        text15.setSize(120, 50);
        text16 = new JLabel("Dead People (RIP):");
        text16.setLocation(1020, 360);
        text16.setSize(160, 50);
        text17 = new JLabel("0");
        text17.setLocation(1180, 360);
        text17.setSize(120, 50);

        text18 = new JLabel("Total Instances:");
        text18.setLocation(1020, 420);
        text18.setSize(160, 50);
        text19 = new JLabel("0");
        text19.setLocation(1180, 420);
        text19.setSize(120, 50);
        text20 = new JLabel("Time Consumed:");
        text20.setLocation(1020, 450);
        text20.setSize(160, 50);
        text21 = new JLabel("0");
        text21.setLocation(1180, 450);
        text21.setSize(120, 50);

        viewPanel.add(text1);
        viewPanel.add(field2);
        viewPanel.add(text2);
        viewPanel.add(box2);
        viewPanel.add(text3);
        viewPanel.add(box3);
        viewPanel.add(text4);
        viewPanel.add(field1);
        viewPanel.add(text5);
        viewPanel.add(box4);
        viewPanel.add(button1);
        viewPanel.add(button2);
        viewPanel.add(text6);
        viewPanel.add(text7);
        viewPanel.add(text8);
        viewPanel.add(text9);
        viewPanel.add(text10);
        viewPanel.add(text11);
        viewPanel.add(text12);
        viewPanel.add(text13);
        viewPanel.add(text14);
        viewPanel.add(text15);
        viewPanel.add(text16);
        viewPanel.add(text17);
        viewPanel.add(text18);
        viewPanel.add(text19);
        viewPanel.add(text20);
        viewPanel.add(text21);
        paintPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                g.setColor(Color.GRAY);
                g.fillRect(0, 0, 1000, 600);
            }
        };
        paintPanel.setLocation(5, 5);
        paintPanel.setSize(1000, 600);
        viewPanel.add(paintPanel);
        viewFrame.add(viewPanel);
        viewFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        viewFrame.setLocation(80, 30);
        viewFrame.setSize(1250, 650);
        viewFrame.setResizable(false);
        viewFrame.setVisible(true);
    }

    public void startSimulation() {
        button1.setText("STOP");
        button2.setText("PAUSE");
        button2.setEnabled(true);
    }

    public void stopSimulation() {
        button2.setEnabled(false);
        button1.setText("START");
    }

    public void playSimulation() {
        button2.setText("PAUSE");
    }

    public void pauseSimulation() {
        button2.setText("PLAY");
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == button1) {
            String text = button1.getText();
            if (text.equalsIgnoreCase("start")) {
                try {
                    int spd = Integer.parseInt(field2.getText());
                    if (spd > 500 || spd < 1)
                        throw new SpeedException();
                    double sprFac = Double.parseDouble(box2.getSelectedItem().toString());
                    double mrtRat = Double.parseDouble(box3.getSelectedItem().toString());
                    String temp = box4.getSelectedItem().toString();
                    String[] str = temp.split("[x]");
                    int simSpd = Integer.parseInt(str[0]);
                    int cnt = Integer.parseInt(field1.getText());
                    if (cnt < 0)
                        throw new InstanceException();
                    controller.start(cnt, spd, mrtRat, sprFac, simSpd);
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                } catch (NumberFormatException exception) {
                    err.showMessageDialog(null, "\nPlease enter all inputs as integers");
                } catch (SpeedException exception) {
                    err.showMessageDialog(null, "\nPlease enter speed between 1 and 500");
                } catch (InstanceException exception) {
                    err.showMessageDialog(null, "\nPlease enter instance count as nonnegative number");
                }
            } else {
                controller.stop();
            }
        } else if (e.getSource() == button2) {
            String text = button2.getText();
            if (text.equalsIgnoreCase("play")) {
                controller.play();
            } else {
                controller.pause();
            }
        }
    }

    public void updatePaint() {
        viewPanel.remove(paintPanel);
        paintPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                model.paint(g);
            }
        };
        paintPanel.setLayout(null);
        paintPanel.setLocation(5, 5);
        paintPanel.setSize(1000, 600);
        viewPanel.add(paintPanel);
        viewPanel.repaint();
    }

    public void updateCount() {
        text7.setText(Integer.toString(model.getHealthy()));
        text9.setText(Integer.toString(model.getInfecting()));
        text11.setText(Integer.toString(model.getInfected()));
        text13.setText(Integer.toString(model.getHospitalized()));
        text15.setText(Integer.toString(model.getIntubated()));
        text17.setText(Integer.toString(model.getDead()));
        text19.setText(Integer.toString(model.getTotal()));
        text21.setText(Integer.toString(model.getTime()));
        viewPanel.repaint();
    }
}
