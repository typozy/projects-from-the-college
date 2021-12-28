package com.company;

public class Main {

    public static void main(String[] args) {
            Suit suit = new Dec();
            System.out.println(suit.getDescription() + " ₺" + suit.cost()/1000+"k");
            Suit suit2 = new Tor();
            suit2 = new RocketLauncher(suit2);
            suit2 = new RocketLauncher(suit2);
            suit2 = new Laser(suit2);
            System.out.println(suit2.getDescription() + " ₺" + suit2.cost()/1000+"k");
            Suit suit3 = new Ora();
            suit3 = new AutoRifle(suit3);
            suit3 = new Laser(suit3);
            suit3 = new Flamethrower(suit3);
            System.out.println(suit3.getDescription() + " ₺" + suit3.cost()/1000+"k");
            Suit suit4 = new Tor();
            suit4 = new Laser(suit4);
            suit4 = new AutoRifle(suit4);
            System.out.println(suit4.getDescription() + " ₺" + suit4.cost()/1000+"k");
    }
}