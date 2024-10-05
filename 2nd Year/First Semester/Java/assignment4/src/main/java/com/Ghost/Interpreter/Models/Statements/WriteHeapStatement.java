package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Exceptions.Statements.InvalidTypeException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.RefferenceType;
import com.Ghost.Interpreter.Models.Values.RefferenceValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class WriteHeapStatement implements IStatement {
    String name;
    IExpression expression;

    public WriteHeapStatement(String id, IExpression expression) {
        this.name = id;
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        if(!state.get_symbol_table().has(this.name))
            throw new VariableUndefinedException();

        IValue value = state.get_symbol_table().get(this.name);
        if(!(value.get_type() instanceof RefferenceType))
            throw new InvalidTypeException();

        Integer address = ((RefferenceValue)value).get_address();
        if(!(state.get_memory_heap().has(address)))
            throw new UninitializedAddressException();
        
        IValue result = this.expression.evaluate(state);
        if(!(state.get_symbol_table().get(this.name).get_type().equal(new RefferenceType(result.get_type()))))
            throw new TypeMismatchException();

        state.get_memory_heap().set(address, result);
    }

    public String toString() {
        return "writeHeap(" + this.name + ", " + this.expression + ");";
    }
}
