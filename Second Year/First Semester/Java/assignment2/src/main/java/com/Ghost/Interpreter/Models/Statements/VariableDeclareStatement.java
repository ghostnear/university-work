package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Models.IType;

public class VariableDeclareStatement implements IStatement {
    String name;
    IType type;

    public VariableDeclareStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    public String toString() {
        return type.toString() + " " + name + ";";
    }
}
