package com.company;

public class Select implements Command{

    private Database db;

    public Select(Database db){
        this.db = db;
    }

    public String execute(String query){
        return db.select(query);
    }

    public void undo(){}
}