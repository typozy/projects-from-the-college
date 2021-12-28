package com.company;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ITable extends Remote {
    Object getElementAt(int row, int column) throws RemoteException, InterruptedException;
    void setElementAt(int row, int column, Object o) throws RemoteException, InterruptedException;
    int getNumberOfRows() throws RemoteException, InterruptedException;
    int getNumberOfColumns() throws RemoteException, InterruptedException;
}