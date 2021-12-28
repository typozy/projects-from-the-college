package com.company;

public class Main {

    public static void main(String[] args) {
	    PhoneStore newStore0 = new PhoneStoreTR();
	    Phone newPhone0 = newStore0.orderPhone("maxEffort");
	    Phone newPhone1 = newStore0.orderPhone("iflasDeluxe");
	    Phone newPhone2 = newStore0.orderPhone("amanIflas");
        PhoneStore newStore1 = new PhoneStoreTR();
        Phone newPhone3 = newStore1.orderPhone("maxEffort");
        Phone newPhone4 = newStore1.orderPhone("iflasDeluxe");
        Phone newPhone5 = newStore1.orderPhone("amanIflas");
        PhoneStore newStore2 = new PhoneStoreTR();
        Phone newPhone6 = newStore2.orderPhone("maxEffort");
        Phone newPhone7 = newStore2.orderPhone("iflasDeluxe");
        Phone newPhone8 = newStore2.orderPhone("amanIflas");
    }
}
