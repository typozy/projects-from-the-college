package com.company;

public class Alter implements Command{

    private Database db;
    private String backup;
    private String backupList;

    public Alter(Database db){
        this.db = db;
    }

    public String execute(String query){
        if(query.split("[ ]+")[0].equalsIgnoreCase("add")){
            String[] temp = query.split("[ ]+");
            backup = "remove "+temp[1];
        }
        else{
            String[] temp = query.split("[ ]+");
            backup = "add "+temp[1];
        }
        backupList = db.alter(query);
        return backupList;
    }
    public void undo(){
        db.alter(backup);
        if(backup.split("[ ]+")[0].equalsIgnoreCase("add")){
            db.fillColumn(backup.split("[ ]+")[1],backupList);
        }
    }
}
