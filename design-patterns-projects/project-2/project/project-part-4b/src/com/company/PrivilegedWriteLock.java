package com.company;

public class PrivilegedWriteLock {

    private int readCount;
    private int writeCount;
    private int writeThreads;

    public synchronized void readLock() throws InterruptedException {
        while(writeCount > 0 || writeThreads > 0) {
                wait();
        }
        ++readCount;
    }

    public synchronized void readUnlock() {
        --readCount;
        notifyAll();
    }

    public synchronized void writeLock() throws InterruptedException {
        ++writeThreads;
        while(readCount > 0 || writeCount > 0) {
                wait();
        }
        --writeThreads;
        ++writeCount;
    }

    public synchronized void writeUnlock(){
        --writeCount;
        notifyAll();
    }
}