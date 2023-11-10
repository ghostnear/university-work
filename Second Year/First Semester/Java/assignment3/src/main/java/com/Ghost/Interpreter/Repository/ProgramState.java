package com.Ghost.Interpreter.Repository;

import java.io.*;
import com.Ghost.Interpreter.ADTs.*;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Files.*;
import com.Ghost.Interpreter.Models.*;

public class ProgramState {
    Stack<IStatement> executionStack;
    Dictionary<String, IValue> symbolTable;
    List<IValue> output;
    Dictionary<String, BufferedReader> fileReadTable;
    boolean running;

    public ProgramState() {
        this.executionStack = new Stack<IStatement>(255);
        this.symbolTable = new Dictionary<String, IValue>();
        this.output = new List<IValue>(255);
        this.fileReadTable = new Dictionary<String, BufferedReader>();
        running = false;
    }

    public ProgramState(Stack<IStatement> newExecutionStack, Dictionary<String, IValue> newSymbolTable, List<IValue> newOutput, Dictionary<String, BufferedReader> newFileReadTable) {
        this.executionStack = newExecutionStack;
        this.symbolTable = newSymbolTable;
        this.output = newOutput;
        this.fileReadTable = newFileReadTable;
        running = false;
    }

    public void reset() {
        running = false;
        this.executionStack.clear();
        this.symbolTable.clear();
        this.output.clear();
    }

    public void log(String filePath) throws InterpreterException {
        try {
            PrintWriter file = new PrintWriter(new BufferedWriter(new FileWriter(filePath, true)));
            file.println("=============================");
            file.println("Execution stack:");
            file.println(this.executionStack);
            file.println("Symbol table:");
            file.println(this.symbolTable);
            file.println("Output:");
            file.println(this.output);
            file.println("Read file table:");
            file.println(this.fileReadTable);
            file.close();
        }
        catch(IOException e) {
            throw new FileCouldNotBeOpenedException();
        }
    }

    public void start() {
        running = true;
    }

    public void stop() {
        running = false;
    }

    public boolean is_running() {
        return running;
    }

    public Stack<IStatement> get_execution_stack() {
        return this.executionStack;
    }

    public Dictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public List<IValue> getOutput() {
        return this.output;
    }

    public Dictionary<String, BufferedReader> getReadFileTable() {
        return this.fileReadTable;
    }
}
