package com.company;

import java.util.Observable;
import java.util.Observer;

public class WebAudio extends Observable{

    private String audio;
    private String webName;

    public WebAudio(){}
    public WebAudio(String name){
        webName = name;
    }

    public void audioChanged(){
        setChanged();
        display();
        notifyObservers();
    }

    public void display(){
        System.out.println(webName+" updated its audio contents.");
    }

    public void setAudio(String newAudio){
        audio = newAudio;
        audioChanged();
    }

    public String getAudio(){
        return audio;
    }

    public String getName(){return webName;}
}