package com.company;

import com.company.*;

public class Website {

    private static int numGenerator = 0;

    String name;
    WebAudio audioChannel;
    WebPhoto photoChannel;
    WebText textChannel;

    public Website(){
        name = "website" + Integer.toString(numGenerator);
        ++numGenerator;
        audioChannel = new WebAudio(name);
        photoChannel = new WebPhoto(name);
        textChannel = new WebText(name);
        System.out.println(name+" exists!");
    }

    public Website(String webName){
        name = webName;
        audioChannel = new WebAudio(name);
        photoChannel = new WebPhoto(name);
        textChannel = new WebText(name);
        System.out.println(name+" exists!");
    }

    public String getAudio(){
        return audioChannel.getAudio();
    }

    public String getPhoto(){
        return photoChannel.getPhoto();
    }

    public String getText(){
        return textChannel.getText();
    }

    public void setAll(String aud,String pho, String txt){
        setAudio(aud);
        setPhoto(pho);
        setText(txt);
    }
    public void setAudio(String newAudio){
        audioChannel.setAudio(newAudio);
    }

    public void setPhoto(String newPhoto){
        photoChannel.setPhoto(newPhoto);
    }

    public void setText(String newText){
        textChannel.setText(newText);
    }

    public void addSubscriber(Subscriber sub){
        addSubscriberAudio(sub);
        addSubscriberPhoto(sub);
        addSubscriberText(sub);
    }

    public void addSubscriberAudio(Subscriber sub){
        audioChannel.addObserver(sub.getAudio());
        System.out.println(name +" added "+sub.getName() +" to its audio subscriber list.");
    }

    public void addSubscriberPhoto(Subscriber sub){
        photoChannel.addObserver(sub.getPhoto());
        System.out.println(name +" added "+sub.getName() +" to its photo subscriber list.");
    }

    public void addSubscriberText(Subscriber sub){
        textChannel.addObserver(sub.getText());
        System.out.println(name +" added "+sub.getName() +" to its text subscriber list.");
    }

    public void deleteSubscriber(Subscriber sub){
        deleteSubscriberAudio(sub);
        deleteSubscriberPhoto(sub);
        deleteSubscriberText(sub);
    }

    public void deleteSubscriberAudio(Subscriber sub){
        audioChannel.deleteObserver(sub.getAudio());
        System.out.println(name +" removed "+sub.getName() +" from its audio subscriber list.");
    }

    public void deleteSubscriberPhoto(Subscriber sub){
        photoChannel.deleteObserver(sub.getPhoto());
        System.out.println(name +" removed "+sub.getName() +" from its photo subscriber list.");
    }

    public void deleteSubscriberText(Subscriber sub){
        textChannel.deleteObserver(sub.getText());
        System.out.println(name +" removed "+sub.getName() +" from its text subscriber list.");
    }
}
