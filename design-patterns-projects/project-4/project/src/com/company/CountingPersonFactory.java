package com.company;

public class CountingPersonFactory extends PersonFactory{
    @Override
    Paintable createInfectedPerson(int speed, int dieTime) {
        return new PaintableCounter(new InfectedPerson(speed,dieTime));
    }

    @Override
    Paintable createHealthyPerson(int speed) {
        return new PaintableCounter(new HealthyPerson(speed));
    }
}