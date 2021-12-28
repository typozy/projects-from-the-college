package com.company;

public abstract class AbstractPersonFactory {
    abstract Paintable createInfectedPerson(int speed, int dieTime);
    abstract Paintable createHealthyPerson(int speed);
}
