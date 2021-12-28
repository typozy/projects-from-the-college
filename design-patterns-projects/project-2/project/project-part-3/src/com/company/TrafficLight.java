package com.company;

import java.util.Observable;
import java.util.Observer;

public class TrafficLight implements Observer {
    private Observable observable;
    private boolean crowded;

    private State red;
    private State green;
    private State yellow;

    private State state;
    private long timeout;
    private boolean onWork;

    TrafficLight(Observable observable) throws InterruptedException {
        this.observable = observable;
        observable.addObserver(this);
        red = new RedState(this);
        green = new GreenState(this);
        yellow = new YellowState(this);
        state = red;
        onWork = false;
        timeout = 60;
    }

    public long getTimeout(){
        return timeout;
    }
    public void setState(State state){
        this.state = state;
    }
    public State getGreenState(){
        return green;
    }

    public State getYellowState(){
        return yellow;
    }

    public State getRedState(){
        return red;
    }

    public State getState() {
        return state;
    }

    @Override
    public void update(Observable o, Object arg) {
        if(o instanceof HiTech) {
            HiTech mobeseData = (HiTech) o;
            this.crowded = mobeseData.getCrowdInfo();
            if (crowded) {
                timeout = 90;
            } else {
                timeout = 60;
            }
            this.display();
        }
    }

    public void display(){
        System.out.printf("Timeout changed to %d seconds\n",timeout/10);
    }

    public void run() throws InterruptedException {
        System.out.println("The light starts working.");
        State temp = state;
        onWork = true;
        if(temp instanceof RedState){
            state.turnGreen();
        }
        else if(temp instanceof GreenState){
            state.turnYellow();
        }
        else{
            state.turnRed();
        }
    }

    public boolean onWork(){
        return onWork;
    }

    public void stop(){
        onWork = false;
    }
}
