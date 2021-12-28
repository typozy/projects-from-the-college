package com.company;

import java.awt.*;

public class PersonInHospital implements Paintable {

    int speed;
    int dieTime;
    int coefficient;
    double maskRate;

    PersonInHospital(InfectedPerson inf){
        this.speed = inf.speed();
        this.dieTime = inf.dieTime();
        this.coefficient = inf.coefficient();
        this.maskRate = inf.maskRate();
    }

    public void decreaseTime(){
        dieTime--;
    }

    public int dieTime(){
        return dieTime;
    }

    @Override
    public void paint(Graphics g) {

    }

    public int speed() {
        return speed;
    }
    public int coefficient(){
        return coefficient;
    }

    public double maskRate(){
        return maskRate;
    }
}
