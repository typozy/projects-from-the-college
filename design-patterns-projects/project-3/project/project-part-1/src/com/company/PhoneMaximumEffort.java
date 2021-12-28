package com.company;

public class PhoneMaximumEffort extends Phone {
    PhoneComponentFactory factory;
    public PhoneMaximumEffort(PhoneComponentFactory factory){
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
        System.out.println("Inserting 2.8 Ghz CPU and 8 GB RAM to the mainboard");
    }
    public void insertDisplay(){
        System.out.println("Inserting 5.5 inches display");
    }
    public void insertBattery(){
        System.out.println("Inserting 3600 mAh battery");
    }
    public void insertStorage(){
        System.out.println("Inserting 64 GB storage with microSD support");
    }
    public void insertCamera(){
        System.out.println("Inserting 12 Mp front and 8 Mp rear camera");
    }
    public void coverCase(){
        System.out.println("Covering the phone case with 151x73x7.7 mm dustproof, waterproof, aluminum");
    }
}
