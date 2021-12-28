package com.company;
import java.util.Observable;

public class HiTech extends Observable {
    boolean crowded;

    public void changeDetected(boolean flag){
        if((crowded == true && flag == false)||(crowded == false && flag == true)) {
            crowded = flag;
            setChanged();
            notifyObservers();
        }
    }

    public boolean getCrowdInfo(){
        return crowded;
    }
}