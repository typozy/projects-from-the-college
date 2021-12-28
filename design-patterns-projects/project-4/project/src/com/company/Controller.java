package com.company;

public class Controller implements ControllerInterface{

    Model model;
    View view;

    Controller(Model model){
        this.model = model;
        view = new View(this,model);
        view.create();
    }

    public void start(int peopleCount, int speed, double mortalityRate, double spreadFactor, int simSpd) throws InterruptedException {
        model.start(peopleCount,speed,mortalityRate,spreadFactor,simSpd);
        view.startSimulation();
    }

    public void stop() {
        model.stop();
        view.stopSimulation();
    }

    public void play() {
        model.play();
        view.playSimulation();
    }

    public void pause() {
        model.pause();
        view.pauseSimulation();
    }
}
