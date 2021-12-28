package com.company;

public class PhoneComponentFactoryTR implements PhoneComponentFactory{
    public Display produceDisplay(){
        return new Display32();
    }
    public Battery produceBattery(){
        return new BatteryLiBo();
    }
    public CPUnRAM produceCPUnRAM(){
        return new CPUnRAM8();
    }
    public Storage produceStorage(){
        return new Storage128();
    }
    public Camera produceCamera(){
        return new Camera4x();
    }
    public Case produceCase(){
        return new Case2();
    }
}
