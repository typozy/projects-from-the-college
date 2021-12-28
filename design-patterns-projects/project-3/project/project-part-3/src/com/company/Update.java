package com.company;

import javax.xml.crypto.Data;

public class Update implements Command{

    private Database db;
    private String backup;

    public Update(Database db){
        this.db = db;
    }

    public String execute(String query) {
        String [] temp = query.split("[ ]+");
        if(temp.length > 4){
            if(temp[3].equalsIgnoreCase("add")){
                backup = temp[0]+" "+temp[1]+" "+temp[2]+" remove "+temp[4];
            }
            else{
                backup = temp[0]+" "+temp[1]+" "+temp[2]+" add "+temp[4];
            }
        }
        else{
            temp[3] = db.select(temp[0]+" "+temp[1]+" "+temp[2]);
            backup = temp[0]+" "+temp[1]+" "+temp[2]+" "+temp[3];
        }
        return db.update(query);
    }

    public void undo(){
        db.update(backup);
    }
}
