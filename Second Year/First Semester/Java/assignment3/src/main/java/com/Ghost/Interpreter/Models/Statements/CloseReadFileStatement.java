package com.Ghost.Interpreter.Models.Statements;

import java.io.*;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Statements.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.StringType;
import com.Ghost.Interpreter.Models.Values.StringValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class CloseReadFileStatement implements IStatement {
    IExpression expression;

    public CloseReadFileStatement(IExpression expression) {
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        IValue value = this.expression.evaluate(state);
        if(!(value.getType() instanceof StringType))
            throw new InvalidTypeException();

        String name = ((StringValue)value).get();
        if(!state.getReadFileTable().has(name))
            throw new FileNotOpenedException();
        
        try {
            state.getReadFileTable().get(name).close();
            state.getReadFileTable().remove(name);
        }
        catch(IOException e) {
            throw new FileCouldNotBeClosedException();
        }
    }

    public String toString() {
        return "closeReadFile(" + expression.toString() + ");";
    }
}
