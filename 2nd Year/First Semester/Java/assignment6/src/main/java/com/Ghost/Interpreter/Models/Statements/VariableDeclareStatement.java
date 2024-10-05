package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
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
        if(state.get_symbol_table().has(this.name))
            throw new VariableAlreadyDefinedException();
        
        state.get_symbol_table().set(this.name, this.type.default_value());
    }

    public String toString() {
        return type.toString() + " " + name + ";";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        if(typeEnvironment.has(this.name))
            throw new CheckingException("VariableDeclareStatement: Variable is already defined!");

        typeEnvironment.set(this.name, this.type);
        return typeEnvironment;
    }
}
