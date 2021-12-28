package com.company;

public class Main {

    public static void main(String[] args) {
        Website web = new Website("google.com");
        Subscriber sub0 = new Subscriber();
        Subscriber sub1 = new Subscriber();
        Subscriber sub2 = new Subscriber();
        Subscriber sub3 = new Subscriber();
        Subscriber sub4 = new Subscriber();
        Subscriber sub5 = new Subscriber();
        web.addSubscriber(sub0);
        web.addSubscriberAudio(sub1);
        web.addSubscriberPhoto(sub2);
        web.addSubscriberAudio(sub3);
        web.addSubscriberText(sub4);
        web.addSubscriberPhoto(sub5);
        web.setPhoto("pic");
        web.deleteSubscriberPhoto(sub2);
        web.setPhoto("pic");
        web.deleteSubscriberPhoto(sub5);
        web.setPhoto("pic");
        web.addSubscriberPhoto(sub2);
        web.setAll("aud","pic","txt");
        web.deleteSubscriberText(sub0);
        web.deleteSubscriberText(sub4);
        web.setAudio("aud");
        web.setText("txt");
    }
}
