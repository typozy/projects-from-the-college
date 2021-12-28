package com.company;

import java.awt.*;

public class InfectedPerson implements Paintable {

    private int x;
    private int y;
    private int speed;
    private int xspeed;
    private int yspeed;
    private int coefficient;
    private int remainingTime;
    private double maskRate;
    private boolean inCollision;
    private int lastBumped;
    private int hospitalTime;
    private int dieTime;

    public InfectedPerson(InfectingPerson person, int dieTime) {
        this.lastBumped = person.lastBumped();
        this.inCollision = false;
        this.dieTime = dieTime;
        this.hospitalTime = 25;
        this.x = person.getX();
        this.y = person.getY();
        this.speed = person.speed();
        randomize();
        this.coefficient = person.coefficient();
        this.maskRate = person.maskRate();
    }

    public InfectedPerson(int speed, int dieTime) {
        this.lastBumped = -1;
        this.inCollision = false;
        this.dieTime = dieTime;
        this.hospitalTime = 25;
        this.coefficient = (int) (Math.random() * 5 + 1);
        x = (int) (Math.random() * 996);
        y = (int) (Math.random() * 596);
        this.speed = speed;
        randomize();
        if (Math.random() < 0.5) {
            maskRate = 0.2;
        } else {
            maskRate = 1.0;
        }
    }

    public int speed() {
        return speed;
    }

    public void move() {
        x = x + xspeed;
        y = y + yspeed;
        if (x < 0) {
            x = -x;
            xspeed = -xspeed;
        }
        if (y < 0) {
            y = -y;
            yspeed = -yspeed;
        }
        if (x > 995) {
            x = 995 - (x - 995);
            xspeed = -xspeed;
        }
        if (y > 595) {
            y = 595 - (y - 595);
            yspeed = -yspeed;
        }
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void collide() {
        inCollision = true;
    }

    public boolean inCollision() {
        return inCollision;
    }

    public int coefficient() {
        return coefficient;
    }

    public int remainingTime() {
        return remainingTime;
    }

    public void decreaseRemainingTime() {
        remainingTime--;
    }

    public void stopCollision() {
        inCollision = false;
    }

    public void randomize() {
        xspeed = ((int) (Math.random() * (speed + 1)));
        yspeed = speed - xspeed;
        if (Math.random() < 0.5) {
            xspeed = -xspeed;
        }
        if (Math.random() < 0.5) {
            yspeed = -yspeed;
        }
    }

    public void decreaseTime() {
        hospitalTime--;
        dieTime--;
    }

    public int dieTime() {
        return dieTime;
    }

    public int hospitalTime() {
        return hospitalTime;
    }

    public int lastBumped() {
        return lastBumped;
    }

    public void setLastBumped(int last) {
        lastBumped = last;
    }

    public void setRemainingTime(int remainingTime) {
        this.remainingTime = remainingTime;
    }

    public double maskRate() {
        return maskRate;
    }

    @Override
    public void paint(Graphics g) {
        g.setColor(Color.RED);
        g.fillRect(x, y, 5, 5);
        g.setColor(Color.BLACK);
        g.drawRect(x, y, 5, 5);
    }
}
