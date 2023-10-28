package com.Ghost.Interpreter.Repository;

import com.Ghost.Interpreter.ADTs.*;
import com.Ghost.Interpreter.Models.*;

public class ProgramState {
    Stack<IStatement> executionStack;
    Dictionary<String, IValue> symbolTable;
    List<IValue> output;

    public ProgramState() {
        this.executionStack = new Stack<IStatement>(255);
        this.symbolTable = new Dictionary<String, IValue>();
        this.output = new List<IValue>(255);
    }

    public ProgramState(Stack<IStatement> newExecutionStack, Dictionary<String, IValue> newSymbolTable, List<IValue> newOutput) {
        this.executionStack = newExecutionStack;
        this.symbolTable = newSymbolTable;
        this.output = newOutput;
    }

    public Stack<IStatement> getExecutionStack() {
        return this.executionStack;
    }

    public Dictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public List<IValue> getOutput() {
        return this.output;
    }
}
