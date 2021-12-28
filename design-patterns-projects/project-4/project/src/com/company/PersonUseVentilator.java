package com.company;

import java.awt.*;

public class PersonUseVentilator implements Paintable {

    private int speed;
    private double maskRate;
    private int coefficient;
    private int remainingTime;

    PersonUseVentilator(InfectedPerson inf){
        remainingTime = 10;
        this.speed = inf.speed();
        this.maskRate = inf.maskRate();
        this.coefficient = inf.coefficient();
    }

    PersonUseVentilator(PersonInHospital hos){
        remainingTime = 10;
        this.speed = hos.speed();
        this.maskRate = hos.maskRate();
        this.coefficient = hos.coefficient();
    }

    public double maskRate(){
        return maskRate;
    }

    public int coefficient(){
        return coefficient;
    }
    public int speed() {
        return speed;
    }

    public void decreaseRemainingTime(){
        remainingTime--;
    }

    public int remainingTime(){
        return remainingTime;
    }

    @Override
    public void paint(Graphics g) {

    }
}
