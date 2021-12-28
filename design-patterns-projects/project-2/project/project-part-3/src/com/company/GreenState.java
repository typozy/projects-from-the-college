package com.company;

public class GreenState implements State{
    TrafficLight trafficLight;
    GreenState(TrafficLight trafficLight){
        this.trafficLight = trafficLight;
    }

    @Override
    public void turnGreen(){
        System.out.println("It's already green");
    }

    @Override
    public void turnYellow() throws InterruptedException {
        System.out.println("The light started flashing green.");
        Thread.sleep(((long)100)*trafficLight.getTimeout());
        if(trafficLight.onWork()) {
            System.out.println("It's turning yellow");
            trafficLight.setState(trafficLight.getYellowState());
            trafficLight.getState().turnRed();
        }
        else{
            System.out.println("The light stops working.");
        }
    }

    @Override
    public void turnRed() {
        System.out.println("Green can't turn to red");
    }
}
