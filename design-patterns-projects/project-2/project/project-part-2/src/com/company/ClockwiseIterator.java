package com.company;

import java.util.Iterator;

public class ClockwiseIterator implements Iterator {

    Object[][] data;
    int[][] path;
    int currentI;
    int currentJ;
    Object nextData;
    String way = "right";

    ClockwiseIterator(Object[][] data){
        this.data = data;
        path = new int[data.length+2][];
        for (int i = 0; i < data.length+2; i++) {
            path[i] =  new int[data[0].length+2];
            for (int j = 0; j < data[0].length+2; j++) {
                if(i==0 || i==data.length+1 || j==0 || j==data[0].length+1){
                    path[i][j] = 1;
                }
                else{
                    path[i][j] = 0;
                }
            }
        }
        currentI = 1;
        currentJ = 1;
    }
    @Override
    public boolean hasNext() {
        if (path[currentI][currentJ] == 0){
            path[currentI][currentJ] = 1;
            nextData = data[currentI-1][currentJ-1];
            if(way.equals("right")){
                if(path[currentI][currentJ+1] == 0){
                    ++currentJ;
                }
                else if(path[currentI+1][currentJ] == 0){
                    ++currentI;
                    way = "down";
                }
            }
            else if(way.equals("down")){
                if(path[currentI+1][currentJ] == 0){
                    ++currentI;
                }
                else if(path[currentI][currentJ-1] == 0){
                    --currentJ;
                    way = "left";
                }
            }
            else if(way.equals("left")){
                if(path[currentI][currentJ-1] == 0){
                    --currentJ;
                }
                else if(path[currentI-1][currentJ] == 0){
                    --currentI;
                    way = "up";
                }
            }
            else{
                if(path[currentI-1][currentJ] == 0){
                    --currentI;
                }
                else if(path[currentI][currentJ+1] == 0){
                    ++currentJ;
                    way = "right";
                }
            }
            return true;
        }
        return false;
    }

    @Override
    public Object next() {
        return nextData;
    }

    @Override
    public void remove() {
        System.err.println("Not supported");
    }
}
