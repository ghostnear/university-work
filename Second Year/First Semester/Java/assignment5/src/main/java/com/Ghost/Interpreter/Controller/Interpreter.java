package com.Ghost.Interpreter.Controller;

import java.util.ArrayList;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Stack.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Statements.CompositeStatement;
import com.Ghost.Interpreter.Repository.*;

public class Interpreter {
    ArrayList<ProgramState> programStates;
    String output = "";
    String logFile;

    void log_current_program_status(ProgramState currentProgram) {
        try {
            if(this.logFile != null && !(currentProgram.get_execution_stack().size() != 0 && currentProgram.get_execution_stack().top() instanceof CompositeStatement))
                currentProgram.log(this.logFile);
        }
        catch(InterpreterException error) {
            System.out.println("An error occured while logging the program:\n\t");
            error.printStackTrace();
        }
    }

    public ArrayList<ProgramState> get_program_states() {
        return this.programStates;
    }

    public void reset_program_state() {
        this.programStates.clear();
        this.output = "";
    }

    public void load_program(IStatement program) throws StackOverflowException {
        ProgramState newProgram = new ProgramState(this);
        newProgram.get_execution_stack().push(program);
        newProgram.start();
        programStates.add(newProgram);
    }

    public void step(ProgramState currentProgram) throws InterpreterException {
        IStatement currentStatement = currentProgram.get_execution_stack().pop();
        currentStatement.execute(currentProgram);
        log_current_program_status(currentProgram);
    }

    public void run() throws InterpreterException {
        while(this.programStates.size() != 0)
        {
            ArrayList<Integer> idsToRemove = new ArrayList<Integer>();
            
            // This is taken so we don't instantly step on the new program states created by fork().
            Integer numberOfProgramStates = this.programStates.size();

            for(Integer index = 0; index < numberOfProgramStates; index++)
            {
                ProgramState currentProgram = this.programStates.get(index);
                this.step(currentProgram);
                GarbageCollector.collect(currentProgram);

                if(!currentProgram.is_running())
                {
                    output = currentProgram.get_output().toString();
                    idsToRemove.add(currentProgram.get_id());
                }
            }
            
            for(Integer id : idsToRemove)
                for(ProgramState currentProgram : this.programStates)
                    if(currentProgram.get_id() == id)
                    {
                        this.programStates.remove(currentProgram);
                        break;
                    }
        }
    }

    public void stop() {
        this.programStates.clear();
    }

    public void set_log_file(String newLogFile) {
        this.logFile = newLogFile;
    }

    public String get_output() {
        return output;
    }

    public Interpreter() {
        this.programStates = new ArrayList<ProgramState>();
        this.logFile = null;
        this.output = "";
    }

    public Interpreter(String logFile) {
        this.programStates = new ArrayList<ProgramState>();   
        this.logFile = logFile;
        this.output = "";
    }
}
