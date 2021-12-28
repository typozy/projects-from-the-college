package com.company;

public class Flamethrower extends SuitEquipment {

    private Suit suit;

    public Flamethrower(Suit suit) {
        this.suit = suit;
    }

    public String getDescription() {
        return suit.getDescription() + ", Flamethrower";
    }

    public double cost() {
        return 50000.0 + suit.cost();
    }
}
