package com.company;

import java.util.Observable;
import java.util.Observer;

public class PhotoCheck implements Observer {

    Observable observable;
    private String photo;
    private String subName;

    public PhotoCheck(){}
    public PhotoCheck(String name){
        subName = name;
    }
    public void update(Observable obs, Object arg) {
        WebPhoto web = (WebPhoto) obs;
        this.photo = web.getPhoto();
        display(web);
    }

    public void display(WebPhoto web){
        System.out.println(subName +" got new photo contents from "+web.getName()+".");
    }

    public String getName(){return subName;}
}
