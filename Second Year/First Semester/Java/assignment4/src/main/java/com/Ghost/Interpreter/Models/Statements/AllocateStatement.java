package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.RefferenceType;
import com.Ghost.Interpreter.Models.Values.RefferenceValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class AllocateStatement implements IStatement {
    String name;
    IExpression expression;

    public AllocateStatement(String id, IExpression expression) {
        this.name = id;
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        if(!state.get_symbol_table().has(this.name))
            throw new VariableUndefinedException();
        
        Integer address = state.get_memory_heap().next_free();
        IValue result = this.expression.evaluate(state);

        if(!(state.get_symbol_table().get(this.name).get_type().equal(new RefferenceType(result.get_type()))))
            throw new TypeMismatchException();

        state.get_memory_heap().set(address, result);
        state.get_symbol_table().set(this.name, new RefferenceValue(address, result.get_type()));
    }

    public String toString() {
        return "new(" + this.name + ", " + this.expression + ");";
    }
}
