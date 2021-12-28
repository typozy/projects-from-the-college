package com.company;

public class PhoneComponentFactoryEU implements PhoneComponentFactory{
    public Display produceDisplay(){
        return new Display24();
    }
    public Battery produceBattery(){
        return new BatteryLiIo();
    }
    public CPUnRAM produceCPUnRAM(){
        return new CPUnRAM4();
    }
    public Storage produceStorage(){
        return new Storage64();
    }
    public Camera produceCamera(){
        return new Camera3x();
    }
    public Case produceCase(){
        return new Case1();
    }
}
