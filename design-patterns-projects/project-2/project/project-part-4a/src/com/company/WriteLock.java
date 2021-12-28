package com.company;

public class WriteLock {

    private int readCount;
    private int writeCount;

    public synchronized void readLock() throws InterruptedException {
        while(writeCount > 0) {
                wait();
        }
        ++readCount;
    }

    public synchronized void readUnlock() {
        --readCount;
        notifyAll();
    }

    public synchronized void writeLock() throws InterruptedException {
        while(readCount > 0 || writeCount > 0) {
                wait();
        }
        ++writeCount;
    }

    public synchronized void writeUnlock(){
        --writeCount;
        notifyAll();
    }
}