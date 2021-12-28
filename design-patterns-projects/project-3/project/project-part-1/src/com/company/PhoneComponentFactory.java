package com.company;

public interface PhoneComponentFactory {
    public Display produceDisplay();
    public Battery produceBattery();
    public CPUnRAM produceCPUnRAM();
    public Storage produceStorage();
    public Camera produceCamera();
    public Case produceCase();
}