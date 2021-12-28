package com.company;

public interface State {
    void turnGreen() throws InterruptedException;
    void turnYellow() throws InterruptedException;
    void turnRed() throws InterruptedException;
}
