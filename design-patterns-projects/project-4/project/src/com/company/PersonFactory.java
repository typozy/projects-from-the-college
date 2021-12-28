package com.company;

public class PersonFactory extends AbstractPersonFactory{
    @Override
    Paintable createInfectedPerson(int speed, int dieTime) {
        return new InfectedPerson(speed,dieTime);
    }

    @Override
    Paintable createHealthyPerson(int speed) {
        return new HealthyPerson(speed);
    }
}