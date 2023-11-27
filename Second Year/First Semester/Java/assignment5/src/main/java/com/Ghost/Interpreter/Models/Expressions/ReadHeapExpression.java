package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Exceptions.Statements.InvalidTypeException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.RefferenceType;
import com.Ghost.Interpreter.Models.Values.RefferenceValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class ReadHeapExpression implements IExpression {
    IExpression location;

    public ReadHeapExpression(IExpression location) {
        this.location = location;
    }

    public IValue evaluate(ProgramState state) throws InterpreterException {
        IValue result = this.location.evaluate(state);
        if(!(result.get_type() instanceof RefferenceType))
            throw new InvalidTypeException();

        Integer address = ((RefferenceValue) result).get_address();
        if(!(state.get_memory_heap().has(address)))
            throw new UninitializedAddressException();

        return state.get_memory_heap().get(address);
    }

    public String toString() {
        return "readHeap(" + this.location.toString() + ")";
    }
}
