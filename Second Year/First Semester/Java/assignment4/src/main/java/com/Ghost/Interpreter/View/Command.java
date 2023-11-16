package com.Ghost.Interpreter.View;

public abstract class Command {
    protected String name, description;

    public Command(String name, String description) {
        this.name = name;
        this.description = description;
    }
    
    public abstract void execute();
    public String get_name() { return name; }
    public String get_description() { return description; }
}
