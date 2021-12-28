package com.company;

public class Main {

    public static void main(String[] args) {
        TurboPayment turboPayment= new TurboPaymentImplementation();
        ModernPayment modernPayment= new TurboPaymentAdapter(turboPayment);
        modernPayment.pay("123",3.6f,"dest","installments");
    }
}
