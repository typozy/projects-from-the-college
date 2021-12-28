package com.company;

import com.company.AudioCheck;

public class Subscriber {
    private static int numGenerator = 0;
    private String name;
    private AudioCheck audioListener;
    private PhotoCheck photoListener;
    private TextCheck textListener;

    public Subscriber(){
        name = "subscriber" + Integer.toString(numGenerator);
        ++numGenerator;
        audioListener = new AudioCheck(name);
        photoListener = new PhotoCheck(name);
        textListener = new TextCheck(name);
        System.out.println(name+" exists!");
    }

    public Subscriber(String subName){
        name = subName;
        audioListener = new AudioCheck(name);
        photoListener = new PhotoCheck(name);
        textListener = new TextCheck(name);
        System.out.println(name+" exists!");
    }

    public String getName() {
        return name;
    }

    public AudioCheck getAudio() {
        return audioListener;
    }

    public PhotoCheck getPhoto() {
        return photoListener;
    }

    public TextCheck getText() {
        return textListener;
    }

    public void addWebsite(Website web){
        web.addSubscriber(this);
    }

    public void addWebsiteAudio(Website web){
        web.addSubscriberAudio(this);
    }

    public void addWebsitePhoto(Website web){
        web.addSubscriberPhoto(this);
    }

    public void addWebsiteText(Website web){
        web.addSubscriberText(this);
    }

    public void deleteWebsite(Website web){
        web.deleteSubscriber(this);
    }

    public void deleteWebsiteAudio(Website web){
        web.deleteSubscriberAudio(this);
    }

    public void deleteWebsitePhoto(Website web){
        web.deleteSubscriberPhoto(this);
    }

    public void deleteWebsiteText(Website web){
        web.deleteSubscriberText(this);
    }
}
