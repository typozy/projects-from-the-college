package com.company;

public class AutoRifle extends SuitEquipment {

    private Suit suit;

    public AutoRifle(Suit suit) {
        this.suit = suit;
    }

    public String getDescription() {
        return suit.getDescription() + ", AutoRifle";
    }

    public double cost() {
        return 30000.0 + suit.cost();
    }
}
