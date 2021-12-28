package com.company;

import java.util.Observable;
import java.util.Observer;

public class AudioCheck implements Observer {

    Observable observable;
    private String audio;
    private String subName;
    public AudioCheck(){}

    public AudioCheck(String name){
        subName = name;
    }
    public void update(Observable obs, Object arg) {
        WebAudio web = (WebAudio) obs;
        this.audio = web.getAudio();
        display(web);
    }

    public void display(WebAudio web){
        System.out.println(subName +" got new audio contents from "+web.getName()+".");
    }

    public String getName(){return subName;}
}
