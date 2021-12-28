package com.company;

public class RocketLauncher extends SuitEquipment {
    private Suit suit;

    public RocketLauncher(Suit suit) {
        this.suit = suit;
    }

    public String getDescription() {
        return suit.getDescription() + ", RocketLauncher";
    }

    public double cost() {
        return 150000.0 + suit.cost();
    }
}
