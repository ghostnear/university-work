package com.Ghost.Interpreter.Controller;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
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

import javafx.util.Pair;

public class Interpreter {
    ArrayList<ProgramState> programStates;
    String output = "";
    Set<String> files;
    String logFile;
    ExecutorService executorService;

    public Set<String> get_files()
    {
        return files;
    }

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
        this.files = new HashSet<String>();
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
        while(this.programStates.size() != 0)
            stepAll();
    }

    public ArrayList<Pair<Integer, IValue>> get_heap_all()
    {
        if(this.programStates.size() == 0)
            return new ArrayList<Pair<Integer, IValue>>();

        ArrayList<Pair<Integer, IValue>> result = new ArrayList<Pair<Integer, IValue>>();
        for(Integer key : this.programStates.get(0).get_memory_heap().all().keySet())
            result.add(new Pair<Integer, IValue>(key, this.programStates.get(0).get_memory_heap().get(key)));

        return result;
    }

    public void stepAll() throws InterpreterException 
    {
        if(this.programStates.size() == 0)
            return;

        if(executorService == null)
            executorService = Executors.newFixedThreadPool(2);

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

                output = currentProgram.get_output().toString();
                files = programStates.get(0).fileReadTable.all().keySet();

                if(!currentProgram.is_running())
                {
                    idsToRemove.add(currentProgram.get_id());
                    currentProgram.log(this.logFile);
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

        executorService.shutdownNow();
        executorService = null;
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
