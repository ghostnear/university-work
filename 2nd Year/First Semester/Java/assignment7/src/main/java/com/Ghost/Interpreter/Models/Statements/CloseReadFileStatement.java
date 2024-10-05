package com.Ghost.Interpreter.Models.Statements;

import java.io.*;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
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
        if(!(value.get_type() instanceof StringType))
            throw new InvalidTypeException();

        String name = ((StringValue)value).get();
        if(!state.get_read_file_table().has(name))
            throw new FileNotOpenedException();
        
        try {
            state.get_read_file_table().get(name).close();
            state.get_read_file_table().remove(name);
        }
        catch(IOException e) {
            throw new FileCouldNotBeClosedException();
        }
    }

    public String toString() {
        return "closeReadFile(" + expression.toString() + ");";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        if(!(this.expression.typeCheck(typeEnvironment) instanceof StringType))
            throw new CheckingException("CloseReadFileStatement: Expression is not a string!");

        return typeEnvironment;
    }
}
