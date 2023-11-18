package com.Ghost.Interpreter.Controller;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Stack.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Statements.CompositeStatement;
import com.Ghost.Interpreter.Repository.*;

public class Interpreter {
    ProgramState programState;
    String logFile;

    void log_current_program_status() {
        try {
            if(this.logFile != null && !(this.programState.get_execution_stack().size() != 0 && this.programState.get_execution_stack().top() instanceof CompositeStatement))
                this.programState.log(this.logFile);
        }
        catch(InterpreterException error) {
            System.out.println("An error occured while logging the program:\n\t");
            error.printStackTrace();
        }
    }

    public void reset_program_state() {
        this.programState.reset();
    }

    public void load_program(IStatement program) throws StackOverflowException {
        this.programState.get_execution_stack().push(program);
        this.programState.start();
    }

    public void step_program() throws InterpreterException {
        IStatement currentStatement = this.programState.get_execution_stack().pop();
        currentStatement.execute(this.programState);
        log_current_program_status();
    }

    public void run_program() throws InterpreterException {
        log_current_program_status();
        while(this.programState.is_running() && !this.programState.get_execution_stack().is_empty()) {
            step_program();
            UnsafeGarbageCollector.collect(programState);
        }
    }

    public void stop() {
        this.programState.stop();
    }

    public void set_log_file(String newLogFile) {
        this.logFile = newLogFile;
    }

    public String get_output() {
        return this.programState.get_output().toString();
    }

    public Interpreter(ProgramState newProgramState) {
        this.programState = newProgramState;
        this.logFile = null;
    }

    public Interpreter(ProgramState newProgramState, String logFile) {
        this.programState = newProgramState;
        this.logFile = logFile;
    }
}
