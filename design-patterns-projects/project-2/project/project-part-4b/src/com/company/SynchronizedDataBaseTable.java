package com.company;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class SynchronizedDataBaseTable implements ITable{

    ITable table;

    public static int readNum = 0;
    public static int writeNum = 0;

    PrivilegedWriteLock lock;

    SynchronizedDataBaseTable(ITable table){
        this.table = table;
        lock = new PrivilegedWriteLock();
    }

    public synchronized static int increaseRead(){
        return readNum++;
    }

    public synchronized static int increaseWrite(){
        return writeNum++;
    }

    @Override
    public Object getElementAt(int row, int column) throws InterruptedException, RemoteException {
        int num = increaseRead();
        Object obj;
        System.out.printf("Read thread #%d is waiting.\n",num);
        lock.readLock();
        try {
            System.out.printf("Read thread #%d has started.\n",num);
            Thread.sleep(750);
            obj = table.getElementAt(row,column);
            System.out.printf("Read thread #%d has ended.\n",num);
        } finally {
           lock.readUnlock();
        }
        return obj;
    }

    @Override
    public void setElementAt(int row, int column, Object o) throws InterruptedException, RemoteException {
        int num = increaseWrite();
        System.out.printf("Write thread #%d is waiting.\n",num);
        lock.writeLock();
        try {
            System.out.printf("Write thread #%d has started.\n",num);
            Thread.sleep(1500);
            table.setElementAt(row, column, o);
            System.out.printf("Write thread #%d has ended.\n",num);
        } finally {
            lock.writeUnlock();
        }
    }

    @Override
    public int getNumberOfRows() throws InterruptedException, RemoteException {
        int num = increaseRead();
        int rowNum;
        System.out.printf("Read thread #%d is waiting.\n",num);
        lock.readLock();
        try {
            System.out.printf("Read thread #%d has started.\n",num);
            Thread.sleep(200);
            rowNum = table.getNumberOfRows();
            System.out.printf("Read thread #%d has ended.\n",num);
        } finally {
            lock.readUnlock();
        }
        return rowNum;
    }

    @Override
    public int getNumberOfColumns() throws InterruptedException, RemoteException {
        int num = increaseRead();
        int colNum;
        System.out.printf("Read thread #%d is waiting.\n",num);
        lock.readLock();
        try {
            System.out.printf("Read thread #%d has started.\n",num);
            Thread.sleep(200);
            colNum = table.getNumberOfColumns();
            System.out.printf("Read thread #%d has ended.\n",num);
        } finally {
            lock.readUnlock();
        }
        return colNum;
    }

    public static void main(String[] args) {
        try {
            SynchronizedDataBaseTable obj = new SynchronizedDataBaseTable(new DataBaseTable());
            ITable stub = (ITable) UnicastRemoteObject.exportObject(obj, 1099);
            Registry registry = LocateRegistry.getRegistry();
            registry.bind("DB_161044083", stub);
            System.out.println("\u001B[32m"+"Server ready"+"\u001B[0m");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
