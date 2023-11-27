package com.Ghost.Interpreter.Models.Statements;

import java.io.IOException;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.VariableUndefinedException;
import com.Ghost.Interpreter.Exceptions.Statements.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.*;
import com.Ghost.Interpreter.Models.Values.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class ReadFromFileStatement implements IStatement {
    IExpression expression;
    String variableID;

    public ReadFromFileStatement(IExpression expression, String variableID) {
        this.expression = expression;
        this.variableID = variableID;
    }

    public void execute(ProgramState state) throws InterpreterException {
        if(!state.get_symbol_table().has(this.variableID))
            throw new VariableUndefinedException();

        if(!(state.get_symbol_table().get(this.variableID).get_type() instanceof IntegerType))
            throw new InvalidTypeException();

        IValue value = this.expression.evaluate(state);
        if(!(value.get_type() instanceof StringType))
            throw new InvalidTypeException();

        String name = ((StringValue)value).get();
        if(!state.get_read_file_table().has(name))
            throw new FileNotOpenedException();
        
        try {
            String line = state.get_read_file_table().get(name).readLine();
            if(line == null)
                state.get_symbol_table().set(this.variableID, new IntegerType().default_value());
            else
                state.get_symbol_table().set(this.variableID, new IntegerValue(Integer.parseInt(line)));
        }
        catch(IOException e) {
            throw new FileCouldNotBeReadException();
        }
    }

    public String toString() {
        return "readFromFile(" + expression.toString() + ", " + this.variableID + ");";
    }
}
