package com.Ghost.Interpreter.View.Commands;

import com.Ghost.Interpreter.Controller.Interpreter;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.View.Command;

public class RunExampleCommand extends Command {
    IStatement command;
    Interpreter interpreter;
    
    public RunExampleCommand(String name, String description, IStatement command, Interpreter interpreter) {
        super(name, description);

        this.command = command;
        this.interpreter = interpreter;
    }

    @Override
    public void execute() {
        this.interpreter.set_log_file("./log" + this.name + ".txt");

        try {
            this.interpreter.reset_program_state();
            this.interpreter.load_program(command);
            this.interpreter.run_program();
        } catch (InterpreterException exception) {
            System.out.println("An error occured while executing the program:\n" + exception);
            this.interpreter.stop();
        }

        // Print the output at the end.
        System.out.println("Program output:");
        System.out.println(this.interpreter.get_output());
    }
}
