package com.company;

public abstract class Phone {
    String name;
    CPUnRAM cpuNram;
    Display display;
    Battery battery;
    Storage storage;
    Camera camera;
    Case myCase;
    public abstract void prepare();
    public abstract void insertCPUnRAM();
    public abstract void insertDisplay();
    public abstract void insertBattery();
    public abstract void insertStorage();
    public abstract void insertCamera();
    public abstract void coverCase();
    public void setName(String name){
        this.name = name;
    }

    public String getName(){
        return name;
    }
}
