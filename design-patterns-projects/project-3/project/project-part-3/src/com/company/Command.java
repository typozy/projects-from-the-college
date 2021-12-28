package com.company;

public interface Command {
    String execute(String query);
    void undo();
}
