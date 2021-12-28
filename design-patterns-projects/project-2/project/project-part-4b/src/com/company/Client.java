package com.company;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    public static int threadNum = 0;
    public static int writeNum = 1;
    public static boolean first = true;

    public Client() {}

    public synchronized static void message(){
        if(first){
            System.err.println("All clients has already started processing!");
            first = false;
        }
    }

    public synchronized static int increaseNum(){
        return threadNum++;
    }
    public synchronized static int increaseWriteNum(){ return writeNum++; }

    public static void main(String[] args) {
        String host = (args.length < 1) ? null : args[0];
        int num = increaseNum();
        try {
            if(num == 0) {
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                stub.setElementAt(0,0,increaseWriteNum());
            }
            else if(num == 1){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                stub.setElementAt(0,0,increaseWriteNum());
            }
            else if(num == 2){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                Object response = stub.getElementAt(0,0);
                System.out.printf("response: %s\n",response);
            }
            else if(num == 3){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                Object response = stub.getElementAt(0,0);
                System.out.printf("response: %s\n",response);
            }
            else if(num == 4){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                stub.setElementAt(0,0,increaseWriteNum());
            }
            else if(num == 5){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                Object response = stub.getElementAt(0,0);
                System.out.printf("response: %s\n",response);
            }
            else if(num == 6){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                Object response = stub.getElementAt(0,0);
                System.out.printf("response: %s\n",response);

            }
            else if(num == 7){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                stub.setElementAt(0,0,increaseWriteNum());
            }
            else if(num == 8){
                Thread.sleep(250);
                Registry registry = LocateRegistry.getRegistry(host);
                ITable stub = (ITable) registry.lookup("DB_161044083");
                Object response = stub.getElementAt(0,0);
                System.out.printf("response: %s\n",response);
            }
            else{
                message();
            }
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}