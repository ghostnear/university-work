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

public class OpenReadFileStatement implements IStatement {
    IExpression expression;

    public OpenReadFileStatement(IExpression expression) {
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        IValue value = this.expression.evaluate(state);
        if(!(value.get_type() instanceof StringType))
            throw new InvalidTypeException();

        String name = ((StringValue)value).get();
        if(state.get_symbol_table().has(name))
            throw new FileAlreadyOpenedException();
        
        try {
            state.get_read_file_table().set(name, new BufferedReader(new FileReader(name)));
        }
        catch(FileNotFoundException e) {
            throw new FileNotExistentException();
        }
    }

    public String toString() {
        return "openReadFile(" + expression.toString() + ");";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        IType type = this.expression.typeCheck(typeEnvironment);
        if(!(type instanceof StringType))
            throw new CheckingException("OpenReadFileStatement: Expression is not of type string!");

        return typeEnvironment;
    }
}
