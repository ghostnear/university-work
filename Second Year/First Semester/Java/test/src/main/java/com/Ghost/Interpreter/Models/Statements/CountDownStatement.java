package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.RunningException;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Models.IType;
import com.Ghost.Interpreter.Models.IValue;
import com.Ghost.Interpreter.Models.Types.IntegerType;
import com.Ghost.Interpreter.Models.Values.IntegerValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class CountDownStatement implements IStatement {
    String variableName;

    public CountDownStatement(String variableName) {
        this.variableName = variableName;
    }

    public void execute(ProgramState state) throws InterpreterException {
        if(!state.get_symbol_table().has(this.variableName))
            throw new RunningException("Latch variable not defined");

        IValue latchID = state.get_symbol_table().get(this.variableName);
        if(!latchID.get_type().equal(new IntegerType()))
            throw new RunningException("Latch variable must be an integer");

        if(!state.get_latch_table().has(((IntegerValue)latchID).get()))
            throw new RunningException("Latch variable does not exist");

        Integer latchValue = ((IntegerValue)state.get_latch_table().get(((IntegerValue)latchID).get())).get();
        if(latchValue > 0)
            state.get_latch_table().set(((IntegerValue)latchID).get(), new IntegerValue(latchValue - 1));

        state.get_output_table().add(new IntegerValue(state.get_id()));
    }

    public String toString() {
        return "countDown(" + this.variableName + ")";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        if(!typeEnvironment.get(this.variableName).equal(new IntegerType()))
            throw new RunningException("Latch variable must be an integer");
            
        return typeEnvironment;
    }
}
