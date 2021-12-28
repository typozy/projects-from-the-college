package com.company;

public class Laser extends SuitEquipment {

    private Suit suit;

    public Laser(Suit suit) {
        this.suit = suit;
    }

    public String getDescription() {
        return suit.getDescription() + ", Laser";
    }

    public double cost() {
        return 200000.0 + suit.cost();
    }

}
