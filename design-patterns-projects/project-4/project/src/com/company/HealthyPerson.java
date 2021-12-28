package com.company;

import java.awt.*;

public class HealthyPerson implements Paintable {
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

    public HealthyPerson(PersonUseVentilator ven) {
        inCollision = false;
        lastBumped = -1;
        coefficient = ven.coefficient();
        x = (int) (Math.random() * 996);
        y = (int) (Math.random() * 596);
        maskRate = ven.maskRate();
        this.speed = ven.speed();
        randomize();
    }

    public HealthyPerson(int speed) {
        inCollision = false;
        lastBumped = -1;
        coefficient = (int) (Math.random() * 5 + 1);
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

    public void collide() {
        inCollision = true;
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

    public void stopCollision() {
        inCollision = false;
    }

    public void decreaseRemainingTime() {
        remainingTime--;
    }

    public int speed() {
        return speed;
    }

    public void setRemainingTime(int remainingTime) {
        this.remainingTime = remainingTime;
    }

    public int remainingTime() {
        return remainingTime;
    }

    public int coefficient() {
        return coefficient;
    }

    public boolean inCollision() {
        return inCollision;
    }

    public double maskRate() {
        return maskRate;
    }

    public void setLastBumped(int last) {
        lastBumped = last;
    }

    public int lastBumped() {
        return lastBumped;
    }

    @Override
    public void paint(Graphics g) {
        g.setColor(Color.WHITE);
        g.fillRect(x, y, 5, 5);
        g.setColor(Color.BLACK);
        g.drawRect(x, y, 5, 5);
    }
}
