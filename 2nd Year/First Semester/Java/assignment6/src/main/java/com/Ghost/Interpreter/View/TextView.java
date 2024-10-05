package com.Ghost.Interpreter.View;

import java.util.Map;
import java.util.Scanner;

import com.Ghost.Interpreter.Controller.*;
import com.Ghost.Interpreter.Repository.*;
import com.Ghost.Interpreter.View.Commands.*;

public class TextView {
    Interpreter interpreter;
    HardcodedProgramDB programDB;
    Scanner inputScanner;
    Map<String, Command> commands;

    void add_command(Command command) {
        commands.put(command.get_name(), command);
    }

    public TextView(Interpreter newInterpreter, HardcodedProgramDB newProgramDB) {
        this.interpreter = newInterpreter;
        this.programDB = newProgramDB;

        commands = new java.util.HashMap<String, Command>();

        add_command(new ExitCommand("0", "Exit the program."));
        for(int index = 0; index < this.programDB.size(); index++) {
            add_command(
                new RunExampleCommand(
                    Integer.toString(index + 1),
                    this.programDB.get(index).toString().replace('\n', ' '),
                    this.programDB.get(index),
                    interpreter
                )
            );
        }
    }

    public void show() {
        inputScanner = new Scanner(System.in);

        while(true)
        {
            System.out.println("Available commands:\n");
            for(Command command : commands.values())
                System.out.println(command.get_name() + " - " + command.get_description());

            System.out.print("\nEnter command: ");
            String commandName = inputScanner.nextLine();

            if(commands.containsKey(commandName))
                commands.get(commandName).execute();
            else
                System.out.println("Invalid command!\n");
        }
    }
}
