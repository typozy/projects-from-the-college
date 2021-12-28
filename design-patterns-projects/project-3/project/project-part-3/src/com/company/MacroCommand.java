package com.company;

public class MacroCommand implements Command {

    private Command[] commands;

    public MacroCommand(Command[] commands){
        this.commands = new Command[commands.length];
        for (int i = 0; i < commands.length; i++) {
            this.commands[i] = commands[i];
        }
    }

    public String execute(String queryList) {
        String[] qList = queryList.split("[|]+");
        for (int i = commands.length-1; i > -1; --i) {
            commands[i].execute(qList[i]);
        }
        return null;
    }

    public void undo(){
        for (int i = commands.length-1; i > -1; --i) {
            commands[i].undo();
        }
    }
}
