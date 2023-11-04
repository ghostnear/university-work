package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Arithmetic.VariableNotDefinedException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class VariableExpression implements IExpression {
    String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    public IValue evaluate(ProgramState state) throws InterpreterException {
        if(!state.getSymbolTable().has(id)) {
            throw new VariableNotDefinedException();
        }
        return state.getSymbolTable().get(id);
    }

    public String toString() {
        return id;
    }
}
