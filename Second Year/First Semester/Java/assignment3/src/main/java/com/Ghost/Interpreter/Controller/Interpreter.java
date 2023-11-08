package com.Ghost.Interpreter.Controller;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Stack.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.*;

public class Interpreter {
    ProgramState programState;

    public void reset_program_state() {
        this.programState.reset();
    }

    public void load_program(IStatement program) throws StackOverflowException {
        this.programState.getExecutionStack().push(program);
    }

    public void step_program(Boolean trace) throws InterpreterException {
        IStatement currentStatement = this.programState.getExecutionStack().pop();
        if(trace) {
            System.out.println("====================================");
            System.out.println("Current statement:");
            System.out.println(currentStatement);
            System.out.println("Execution stack:");
            System.out.println(programState.getExecutionStack());
            System.out.println("Symbol table:");
            System.out.println(programState.getSymbolTable());
            System.out.println("Output:");
            System.out.println(programState.getOutput());
        }
        currentStatement.execute(this.programState);
    }

    public void run_program(Boolean trace) {
        while(!this.programState.getExecutionStack().isEmpty()) {
            try {
                step_program(trace);
            }
            catch(InterpreterException e) {
                System.out.println(e);
            }
        }
        if(trace) {
            System.out.println("====================================");
            System.out.println("Final execution stack:");
            System.out.println(this.programState.getExecutionStack());
            System.out.println("Final symbol table:");
            System.out.println(this.programState.getSymbolTable());
            System.out.println("Final output:");
            System.out.println(this.programState.getOutput());
        }
    }

    public Interpreter(ProgramState newProgramState) {
        this.programState = newProgramState;
    }
}
