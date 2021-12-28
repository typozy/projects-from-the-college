package com.company;

public class DataBaseTable implements ITable{

    Object[][] data;
    int rowNum;
    int colNum;

    DataBaseTable(){
        colNum = (int) (Math.random()*11+10);
        rowNum = (int) (Math.random()*31+20);
        data = new Object[rowNum][];
        for (int i = 0; i < rowNum; i++) {
            data[i] = new Object[colNum];
            for (int j = 0; j < colNum; j++) {
                data[i][j] = i*colNum+j;
            }
        }
    }

    @Override
    public Object getElementAt(int row, int column){
        return data[row][column];
    }

    @Override
    public void setElementAt(int row, int column, Object o){
        data[row][column] = o;
    }

    @Override
    public int getNumberOfRows(){
        return rowNum;
    }

    @Override
    public int getNumberOfColumns(){
        return colNum;
    }
}