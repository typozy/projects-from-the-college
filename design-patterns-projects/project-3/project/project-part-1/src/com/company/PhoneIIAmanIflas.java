package com.company;

public class PhoneIIAmanIflas extends Phone {
    PhoneComponentFactory factory;
    public PhoneIIAmanIflas(PhoneComponentFactory factory){
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
        System.out.println("Inserting 2.2 Ghz CPU and 4 GB RAM to the mainboard");
    }
    public void insertDisplay(){
        System.out.println("Inserting 4.5 inches display");
    }
    public void insertBattery(){
        System.out.println("Inserting 2000 mAh battery");
    }
    public void insertStorage(){
        System.out.println("Inserting 16 GB storage with microSD support");}
    public void insertCamera(){
        System.out.println("Inserting 8 Mp front and 5 Mp rear camera");}
    public void coverCase(){
        System.out.println("Covering the phone case with 143x69x7.3 mm waterproof, plastic");
    }
}
