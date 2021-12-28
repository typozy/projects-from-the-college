package com.company;

public interface ControllerInterface {
    void start(int peopleCount, int speed, double mortalityRate, double spreadFactor, int simSpd) throws InterruptedException;
    void stop();
    void play();
    void pause();
}
