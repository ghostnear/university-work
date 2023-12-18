package com.Ghost.Interpreter.Controller;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.RunningException;
import com.Ghost.Interpreter.Exceptions.Stack.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Statements.CompositeStatement;
import com.Ghost.Interpreter.Repository.*;

public class Interpreter {
    ArrayList<ProgramState> programStates;
    String output = "";
    String logFile;
    ExecutorService executorService;

    void log_current_program_status() {
        programStates.forEach(currentProgram -> {
            try {
                if(this.logFile != null && !(currentProgram.get_execution_stack().size() != 0 && currentProgram.get_execution_stack().top() instanceof CompositeStatement))
                    currentProgram.log(this.logFile);
            }
            catch(InterpreterException error) {
                System.out.println("An error occured while logging the program:\n\t");
                error.printStackTrace();
            }           
        });
    }

    public ArrayList<ProgramState> get_program_states() {
        return this.programStates;
    }

    public void reset_program_state() {
        this.programStates.clear();
        ProgramState.reset_last_usable_id();
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
    }

    public void run() throws InterpreterException {
        executorService = Executors.newFixedThreadPool(2);

        while(this.programStates.size() != 0)
        {
            log_current_program_status();

            ArrayList<Integer> idsToRemove = new ArrayList<Integer>();

            List<Callable<Void>> callList = programStates.stream()
                .map((ProgramState currentProgram) -> (Callable<Void>)(() -> {
                    try {
                        this.step(currentProgram);
                    }
                    catch(InterpreterException error) {
                        System.out.println("An error occured while executing the program:");
                        error.printStackTrace();
                        currentProgram.stop();
                    }
                    
                    if(!currentProgram.is_running())
                    {
                        output = currentProgram.get_output().toString();
                        idsToRemove.add(currentProgram.get_id());
                    }
                    else
                        GarbageCollector.collect(currentProgram);
                    
                    return null;
                }))
                .collect(Collectors.toList());
            
            try {
                executorService.invokeAll(callList);
            }
            catch(InterruptedException exception) {
                throw new RunningException("Program execution interrupted.");
            }

            idsToRemove.forEach(id -> {
                for(ProgramState currentProgram : this.programStates)
                    if(currentProgram.get_id() == id)
                    {
                        this.programStates.remove(currentProgram);
                        break;
                    }
            });

            if(this.programStates.size() != 0)
                GarbageCollector.clear(this.programStates.get(0).get_memory_heap());
        }

        executorService.shutdownNow();
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
