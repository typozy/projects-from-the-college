package com.company;

public class PhoneComponentFactoryGL implements PhoneComponentFactory{
    public Display produceDisplay(){
        return new Display24();
    }
    public Battery produceBattery(){
        return new BatteryLiCo();
    }
    public CPUnRAM produceCPUnRAM(){
        return new CPUnRAM2();
    }
    public Storage produceStorage(){
        return new Storage32();
    }
    public Camera produceCamera(){
        return new Camera2x();
    }
    public Case produceCase(){
        return new CaseD5();
    }
}
