package com.Ghost.Interpreter.Repository;

import java.io.*;
import java.util.ArrayList;

import com.Ghost.Interpreter.ADTs.*;
import com.Ghost.Interpreter.Controller.Interpreter;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Files.*;
import com.Ghost.Interpreter.Models.*;

import javafx.util.Pair;

public class ProgramState {
    IStack<IStatement> executionStack;
    IDictionary<String, IValue> symbolTable;
    IList<IValue> output;
    IMemHeap<Integer, IValue> heap;
    IMemHeap<Integer, IValue> latchTable;
    final Integer id;
    final Interpreter interpreter;
    static Integer lastUsableID = 1;

    public IDictionary<String, BufferedReader> fileReadTable;
    boolean running;

    public ArrayList<Pair<String, IValue>> get_symbol_table_all()
    {
        ArrayList<Pair<String, IValue>> result = new ArrayList<Pair<String, IValue>>();
        for(String key : symbolTable.all().keySet())
            result.add(new Pair<String, IValue>(key, symbolTable.get(key)));

        return result;
    }

    public static void reset_last_usable_id() {
        lastUsableID = 1;
    }

    private static Integer get_new_id() {
        return lastUsableID++;
    }

    public ProgramState(Interpreter interpreter) {
        this.executionStack = new Stack<IStatement>(255);
        this.symbolTable = new Dictionary<String, IValue>();
        this.output = new List<IValue>(255);
        this.fileReadTable = new Dictionary<String, BufferedReader>();
        this.heap = new Heap<Integer, IValue>();
        this.latchTable = new AtomicHeap<Integer, IValue>();
        this.running = false;
        this.id = get_new_id();
        this.interpreter = interpreter;
    }

    public ProgramState(Interpreter interpreter, ProgramState mainState)
    {
        this.executionStack = new Stack<IStatement>(255);
        this.symbolTable = mainState.symbolTable.deepCopy();
        this.output = mainState.output;
        this.fileReadTable = mainState.fileReadTable;
        this.heap = mainState.heap;
        this.latchTable = mainState.latchTable;
        this.running = false;
        this.id = get_new_id();
        this.interpreter = interpreter;        
    }

    public Interpreter get_interpreter() {
        return this.interpreter;
    }

    public Integer get_id() {
        return this.id;
    }

    public void reset() {
        running = false;
        this.executionStack.clear();
        this.symbolTable.clear();
        this.output.clear();
        this.heap.clear();
    }

    public void log(String filePath) throws InterpreterException {
        try {
            PrintWriter file = new PrintWriter(new BufferedWriter(new FileWriter(filePath, true)));
            file.println("=============================");
            file.println("Thread ID #" + this.id);
            file.println("Execution stack:");
            file.println(this.executionStack);
            file.println("Symbol table:");
            file.println(this.symbolTable);
            file.println("Output:");
            file.println(this.output);
            file.println("File table:");
            file.println(this.fileReadTable);
            file.println("Memory heap:");
            file.println(this.heap);
            file.println("Latch table:");
            file.println(this.latchTable);
            file.close();
        }
        catch(IOException e) {
            throw new FileCouldNotBeOpenedException();
        }
    }

    public IMemHeap<Integer, IValue> get_latch_table() {
        synchronized(this.latchTable)
        {
            return this.latchTable;
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
        return running && !this.executionStack.is_empty();
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
