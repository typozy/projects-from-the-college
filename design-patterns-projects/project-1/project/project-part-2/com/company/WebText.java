package com.company;

import java.util.Observable;
import java.util.Observer;

public class WebText extends Observable {

    private String text;

    private String webName;

    public WebText(){}
    public WebText(String name){
        webName = name;
    }

    public void textChanged() {
        setChanged();
        display();
        notifyObservers();
    }

    public void display(){
        System.out.println(webName+" updated its text contents.");
    }

    public void setText(String newText){
        text = newText;
        textChanged();
    }

    public String getText(){
        return text;
    }

    public String getName(){return webName;}
}