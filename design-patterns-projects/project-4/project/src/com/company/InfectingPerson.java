package com.company;

import java.awt.*;

public class InfectingPerson implements Paintable {

    private int x;
    private int y;
    private int speed;
    private int coefficient;
    private int remainingTime;
    private int lastBumped;
    private double maskRate;

    public InfectingPerson(HealthyPerson person,int time){
        this.x = person.getX();
        this.y = person.getY();
        this.speed = person.speed();
        this.coefficient = person.coefficient();
        this.remainingTime = time;
        this.lastBumped = person.lastBumped();
        this.maskRate = person.maskRate();
    }

    public int getX(){
        return x;
    }

    public int speed(){
        return speed;
    }

    public int getY(){
        return y;
    }

    public int coefficient(){
        return coefficient;
    }

    public int lastBumped(){
        return lastBumped;
    }

    public int remainingTime(){
        return remainingTime;
    }

    public void decreaseRemainingTime(){
        remainingTime--;
    }

    public double maskRate(){
        return maskRate;
    }
    @Override
    public void paint(Graphics g) {
        g.setColor(Color.PINK);
        g.fillRect(x,y,5,5);
        g.setColor(Color.BLACK);
        g.drawRect(x,y,5,5);
    }
}
