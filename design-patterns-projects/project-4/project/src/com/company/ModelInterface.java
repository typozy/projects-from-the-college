package com.company;

public interface ModelInterface {
    void start(int peopleCount, int speed, double mortalityRate, double spreadFactor,int simSpd) throws InterruptedException;
    void stop();
    void play();
    void pause();
    void registerPaintObserver(View observer);
    void removePaintObserver(View observer);
    void registerCountObserver(View observer);
    void removeCountObserver(View observer);
}
