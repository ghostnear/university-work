package com.Ghost.Interpreter.View.Commands;

import com.Ghost.Interpreter.View.Command;

public class ExitCommand extends Command {
    public ExitCommand(String name, String description) {
        super(name, description);
    }

    @Override
    public void execute() {
        System.out.println("\nExiting now...");
        System.exit(0);
    }
}
