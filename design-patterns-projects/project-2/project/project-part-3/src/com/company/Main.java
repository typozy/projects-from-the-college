package com.company;

public class Main {

    public static void main(String[] args) {
        try {
            HiTech mobese = new HiTech();
            TrafficLight light = new TrafficLight(mobese);
            new Thread(()->{
                try {
                    light.run();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }).start();
            while (true) {
                Thread.sleep(16000);
                mobese.changeDetected(true);
                Thread.sleep(22000);
                mobese.changeDetected(false);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
