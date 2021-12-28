package com.company;

import java.util.Observable;
import java.util.Observer;

public class WebPhoto extends Observable {
    private String photo;
    private String webName;

    public WebPhoto(){}
    public WebPhoto(String name){
        webName = name;
    }

    public void photoChanged(){
        setChanged();
        display();
        notifyObservers();
    }
    public void display(){
        System.out.println(webName+" updated its photo contents.");
    }

    public void setPhoto(String newPhoto){
        photo = newPhoto;
        photoChanged();
    }

    public String getPhoto(){
        return photo;
    }

    public String getName(){return webName;}
}