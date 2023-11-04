package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class VariableDeclareStatement implements IStatement {
    String name;
    IType type;

    public VariableDeclareStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    public void execute(ProgramState state) {
        state.getSymbolTable().set(this.name, this.type.defaultValue());
    }

    public String toString() {
        return type.toString() + " " + name + ";";
    }
}
