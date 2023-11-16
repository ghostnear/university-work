package com.Ghost.Interpreter.Repository;

import java.io.*;
import com.Ghost.Interpreter.ADTs.*;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Files.*;
import com.Ghost.Interpreter.Models.*;

public class ProgramState {
    IStack<IStatement> executionStack;
    IDictionary<String, IValue> symbolTable;
    IList<IValue> output;
    IMemHeap<Integer, IValue> heap;

    IDictionary<String, BufferedReader> fileReadTable;
    boolean running;

    public ProgramState() {
        this.executionStack = new Stack<IStatement>(255);
        this.symbolTable = new Dictionary<String, IValue>();
        this.output = new List<IValue>(255);
        this.fileReadTable = new Dictionary<String, BufferedReader>();
        this.heap = new Heap<Integer, IValue>();
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
            file.println("Memory heap:");
            file.println(this.heap);
            file.close();
        }
        catch(IOException e) {
            throw new FileCouldNotBeOpenedException();
        }
    }

    public String get_output() {
        return this.output.toString();
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

    public IStack<IStatement> get_execution_stack() {
        return this.executionStack;
    }

    public IDictionary<String, IValue> get_symbol_table() {
        return this.symbolTable;
    }

    public IList<IValue> get_output_table() {
        return this.output;
    }

    public IMemHeap<Integer, IValue> get_memory_heap() {
        return this.heap;
    }

    public IDictionary<String, BufferedReader> get_read_file_table() {
        return this.fileReadTable;
    }
}
