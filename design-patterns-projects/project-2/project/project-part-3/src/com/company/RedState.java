package com.company;

public class RedState implements State {
    TrafficLight trafficLight;
    RedState(TrafficLight trafficLight){
        this.trafficLight = trafficLight;
    }

    @Override
    public void turnGreen() throws InterruptedException {
        System.out.println("The light started flashing red.");
        Thread.sleep((long)1500);
        if(trafficLight.onWork()) {
            System.out.println("It's turning green");
            trafficLight.setState(trafficLight.getGreenState());
            trafficLight.getState().turnYellow();
        }
        else{
            System.out.println("The light stops working.");
        }
    }

    @Override
    public void turnYellow() {
        System.out.println("Red can't turn to yellow");
    }

    @Override
    public void turnRed() {
        System.out.println("It's already red");
    }
}
