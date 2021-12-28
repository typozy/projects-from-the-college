package com.company;

public class Main {

    public static int clientCount = 9;

    public static void main(String[] args) {
        try {
            //Starting RMI registry
            new Thread(()-> RMIregistry.main(args)).start();
            Thread.sleep(1000);
            //Server side
            new Thread(()-> SynchronizedDataBaseTable.main(args)).start();
            Thread.sleep(1000);
            //Client side
            for (int i = 0; i < clientCount; i++) {
                new Thread(()->Client.main(args)).start();
            }
        }
        catch (Exception e){
            System.err.println("An error occured");
        }
    }
}
