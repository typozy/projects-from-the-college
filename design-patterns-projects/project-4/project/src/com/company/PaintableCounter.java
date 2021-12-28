package com.company;

import java.awt.*;

public class PaintableCounter implements Paintable {

    Paintable person;
    static int numberOfPrints = 0;

    public PaintableCounter(Paintable person){
        this.person = person;
    }

    @Override
    public void paint(Graphics g) {
        person.paint(g);
        numberOfPrints++;
    }

    public static int getPrints(){
        return numberOfPrints;
    }
}
