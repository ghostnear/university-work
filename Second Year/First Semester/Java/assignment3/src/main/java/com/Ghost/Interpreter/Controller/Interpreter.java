package com.Ghost.Interpreter.Controller;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Stack.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Statements.CompositeStatement;
import com.Ghost.Interpreter.Repository.*;

public class Interpreter {
    ProgramState programState;

    void log_current_program_status(Boolean trace) {
        try {
            if(trace && !(this.programState.get_execution_stack().size() != 0 && this.programState.get_execution_stack().top() instanceof CompositeStatement))
                this.programState.log("./log.txt");
        }
        catch(InterpreterException e) {
            System.out.println("An error occured while logging the program:\n" + e);
        }
    }

    public void reset_program_state() {
        this.programState.reset();
    }

    public void load_program(IStatement program) throws StackOverflowException {
        this.programState.get_execution_stack().push(program);
        this.programState.start();
    }

    public void step_program(Boolean trace) throws InterpreterException {
        IStatement currentStatement = this.programState.get_execution_stack().pop();
        currentStatement.execute(this.programState);
        log_current_program_status(trace);
    }

    public void run_program(Boolean trace) {
        log_current_program_status(trace);
        while(this.programState.is_running() && !this.programState.get_execution_stack().isEmpty())
            try {
                step_program(trace);
            }
            catch(InterpreterException e) {
                System.out.println("An error occured while executing the program:\n" + e);
                this.programState.stop();
            }
    }

    public Interpreter(ProgramState newProgramState) {
        this.programState = newProgramState;
    }
}
