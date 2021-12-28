package com.company;

public class PhoneIflasDeluxe extends Phone {
    PhoneComponentFactory factory;
    public PhoneIflasDeluxe(PhoneComponentFactory factory){
        this.factory = factory;
    }
    public void prepare(){
        System.out.println("Preparing "+name);
        cpuNram = factory.produceCPUnRAM();
        display = factory.produceDisplay();
        battery = factory.produceBattery();
        storage = factory.produceStorage();
        camera = factory.produceCamera();
        myCase = factory.produceCase();
    }
    public void insertCPUnRAM(){
        System.out.println("Inserting 2.2 Ghz CPU and 6 GB RAM to the mainboard");
    }
    public void insertDisplay(){
        System.out.println("Inserting 5.3 inches display");
    }
    public void insertBattery(){
        System.out.println("Inserting 2800 mAh battery");
    }
    public void insertStorage(){
        System.out.println("Inserting 32 GB storage with microSD support");}
    public void insertCamera(){
        System.out.println("Inserting 12 Mp front and 5 Mp rear camera");}
    public void coverCase(){
        System.out.println("Covering the phone case with 149x73x7.7 mm waterproof, aluminum");
    }
}
