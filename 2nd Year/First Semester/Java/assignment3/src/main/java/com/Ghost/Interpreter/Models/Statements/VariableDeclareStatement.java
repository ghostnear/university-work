package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Statements.VariableAlreadyDefinedException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class VariableDeclareStatement implements IStatement {
    String name;
    IType type;

    public VariableDeclareStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    public void execute(ProgramState state) throws InterpreterException {
        if(state.getSymbolTable().has(this.name))
            throw new VariableAlreadyDefinedException();
        
        state.getSymbolTable().set(this.name, this.type.default_value());
    }

    public String toString() {
        return type.toString() + " " + name + ";";
    }
}
