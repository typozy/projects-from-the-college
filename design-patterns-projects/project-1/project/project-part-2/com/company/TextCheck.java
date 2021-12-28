package com.company;

import java.util.Observable;
import java.util.Observer;

public class TextCheck implements Observer {

    Observable observable;
    private String text;
    private String subName;

    public TextCheck(){}

    public TextCheck(String name){
        subName = name;
    }

    public void update(Observable obs, Object arg) {
        WebText web = (WebText) obs;
        this.text = web.getText();
        display(web);
    }

    public void display(WebText web){
        System.out.println(subName +" got new text contents from "+web.getName()+".");
    }

    public String getName(){return subName;}
}
