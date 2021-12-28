package com.company;

public class TurboPaymentAdapter implements ModernPayment{

    TurboPayment turboPayment;

    public TurboPaymentAdapter(TurboPayment turboPayment){
        this.turboPayment = turboPayment;
    }

    public int pay(String cardNo, float amount, String destination, String installments){
        System.out.println("Delivering pay method to TurboPayment class");
        return turboPayment.payInTurbo(cardNo,amount,destination,installments);
    }
}
