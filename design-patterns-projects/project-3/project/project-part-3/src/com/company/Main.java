package com.company;

import javax.xml.crypto.Data;

public class Main {

    public static void main(String[] args) {
        Database db = new Database();
        db.alter("add id");
        db.alter("add wealth");
        db.alter("add job");
        db.add("id 1 wealth 5.0 job worker");
        db.add("id 2 wealth 10.0 job fisher");
        db.add("id 3 wealth 20.0 job gambler");
        db.add("id 4 wealth 50.0 job officer");
        db.add("job jobless id 5 wealth 100.0");
        Command select = new Select(db);
        Command alter = new Alter(db);
        Command update = new Update(db);
        Command update2 = new Update(db);
        Command alter2 = new Alter(db);
        Command alter3 = new Alter(db);
        Command macro = new MacroCommand(new Command[]{select,update,alter,update2,alter2,alter3});
        System.out.println("Table before execution:");
        db.print();
        macro.execute("id 1 wealth|"+
                "id 3 wealth add 35|"+
                "add name|"+
                "id 5 wealth remove 70.0|"+
                "add surname|"+
                "drop job");
        System.out.println("Table after a set of executions:");
        db.print();
        macro.undo();
        System.out.println("Table after backing up:");
        db.print();
    }
}
