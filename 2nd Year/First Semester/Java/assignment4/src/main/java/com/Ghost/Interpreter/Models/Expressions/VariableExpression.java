package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.VariableUndefinedException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class VariableExpression implements IExpression {
    String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    public IValue evaluate(ProgramState state) throws InterpreterException {
        if(!state.get_symbol_table().has(id)) {
            throw new VariableUndefinedException();
        }
        return state.get_symbol_table().get(id);
    }

    public String toString() {
        return id;
    }
}
