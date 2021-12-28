package com.company;

public class Database {
    private static int id = 0;
    private String[][] db;
    private String name;



    public Database(){
        name = "database"+Integer.toString(id);
        ++id;
    }

    public void add(String account){
        int len = db.length;
        String[][] temp = db;
        String[] accountList = account.split("[ ]+");
        String[] newAccount = new String[accountList.length/2];
        for (int i = 0; i < db[0].length; i++) {
            for (int j = 0; j < db[0].length; j++) {
                if (db[0][j].equalsIgnoreCase(accountList[2*i])){
                    newAccount[j] = accountList[2*i+1];
                    break;
                }
            }
        }
        db = new String[len+1][];
        for (int i=0;i<len;++i)
            db[i] = temp[i];
        db[len] = newAccount;
    }

    public String select(String query){
        String[] qList = query.split("[ ]+");
        int src = 0;
        for (int i = 0; i < db[0].length; ++i) {
            if(db[0][i].equalsIgnoreCase(qList[0])) {
                src = i;
            }
        }
        int des = 0;
        for (int i = 0; i < db[0].length; ++i) {
            if(db[0][i].equalsIgnoreCase(qList[2])) {
                des = i;
            }
        }
        int line = 0;
        for (int i = 1; i < db.length; i++) {
            if (db[i][src].equalsIgnoreCase(qList[1])){
                line = i;
            }
        }
        return db[line][des];
    }

    public String update(String query){
        String[] qList = query.split("[ ]+");
        if(qList.length > 4){
            String temp = qList[3];
            qList[3] = qList[4];
            qList[4] = temp;
        }
        int src = 0;
        for (int i = 0; i < db[0].length; ++i) {
            if(db[0][i].equalsIgnoreCase(qList[0])) {
                src = i;
            }
        }
        int des = 0;
        for (int i = 0; i < db[0].length; ++i) {
            if(db[0][i].equalsIgnoreCase(qList[2])) {
                des = i;
            }
        }
        int line = 0;
        for (int i = 1; i < db.length; i++) {
            if (db[i][src].equalsIgnoreCase(qList[1])){
                line = i;
            }
        }
        if(qList.length > 4){
            if(qList[4].equalsIgnoreCase("add")){
                Double temp = Double.parseDouble(db[line][des]);
                temp = temp + Double.parseDouble(qList[3]);
                db[line][des] = String.valueOf(temp);
            }
            else {
                Double temp = Double.parseDouble(db[line][des]);
                temp = temp - Double.parseDouble(qList[3]);
                db[line][des] = String.valueOf(temp);
            }
        }
        else{
            db[line][des] = qList[3];
        }
        return null;
    }

    public String alter(String query){
        String[] qList = query.split("[ ]+");
        if(qList[0].equalsIgnoreCase("add")){
            if(db == null){
                db = new String[1][];
                db[0] = new String[1];
                db[0][0] = qList[1];
            }
            else{
                for (int i = 0; i < db.length; i++) {
                    String[] temp = new String[db[i].length+1];
                    for (int j = 0; j < db[i].length ; j++) {
                        temp[j] = db[i][j];
                    }
                    if(i==0){
                        temp[db[i].length] = qList[1];
                    }
                    else {
                        temp[db[i].length] = "null";
                    }
                    db[i] = temp;
                }
            }
        }
        else{
            String removeList = "";
            int src = 0;
            for (int i = 0; i < db[0].length; ++i) {
                if(db[0][i].equalsIgnoreCase(qList[1])) {
                    src = i;
                }
            }
            for (int i = 0; i < db.length; i++) {
                if(i>0){
                    removeList = removeList+db[i][src]+" ";
                }
                String[] temp = new String[db[i].length-1];
                for (int j = 0; j < temp.length ; j++) {
                    if(j<src){
                        temp[j] = db[i][j];
                    }
                    else{
                        temp[j] = db[i][j+1];
                    }
                }
                db[i] = temp;
            }
            return removeList;
        }
        return null;
    }

    public void fillColumn(String columnName,String itemList){
        int src = 0;
        for (int i = 0; i < db[0].length; i++) {
            if(columnName.equalsIgnoreCase(db[0][i])){
               src = i;
               break;
            }
        }
        String[] tempList = itemList.split("[ ]+");
        for (int i = 1; i < db.length; i++) {
            db[i][src] = tempList[i-1];
        }
    }
    public void print(){
        for (int i = 0; i < db.length; i++) {
            for (int j = 0; j < db[0].length; j++) {
                System.out.printf("%8s ",db[i][j]);
            }
            System.out.println();
        }
    }
}
