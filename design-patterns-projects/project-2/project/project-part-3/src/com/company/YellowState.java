package com.company;

public class YellowState implements State{
    TrafficLight trafficLight;
    YellowState(TrafficLight trafficLight){
        this.trafficLight = trafficLight;
    }

    @Override
    public void turnGreen(){
        System.out.println("Yellow can't turn to green");
    }

    @Override
    public void turnYellow(){
        System.out.println("It's already yellow");
    }

    @Override
    public void turnRed() throws InterruptedException {
        System.out.println("The light started flashing yellow.");
        Thread.sleep((long)300);
        if(trafficLight.onWork()) {
            System.out.println("It's turning red");
            trafficLight.setState(trafficLight.getRedState());
            trafficLight.getState().turnGreen();
        }
        else {
            System.out.println("The light stops working.");
        }
    }
}
