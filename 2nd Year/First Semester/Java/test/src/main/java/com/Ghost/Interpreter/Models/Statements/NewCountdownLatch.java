package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.RunningException;
import com.Ghost.Interpreter.Models.IExpression;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Models.IType;
import com.Ghost.Interpreter.Models.IValue;
import com.Ghost.Interpreter.Models.Types.IntegerType;
import com.Ghost.Interpreter.Models.Values.IntegerValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class NewCountdownLatch implements IStatement {
    String variableName;
    IExpression expression;

    public NewCountdownLatch(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        IValue value = this.expression.evaluate(state);
        if(!value.get_type().equal(new IntegerType()))
            throw new RunningException("Latch value must be an integer");

        if(!state.get_symbol_table().has(this.variableName))
            throw new RuntimeException("Latch variable not declared");

        Integer latchID = state.get_latch_table().next_free();
        
        if(state.get_symbol_table().get(this.variableName).get_type().equal(new IntegerType()))
        {
            state.get_symbol_table().set(this.variableName, new IntegerValue(latchID));
            state.get_latch_table().set(latchID, value);
        }
        else
            throw new RunningException("Latch variable must be an integer");
    }

    public String toString() {
        return "newLatch(" + this.variableName + ", " + this.expression.toString() + ")";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        IType expressionType = this.expression.typeCheck(typeEnvironment);
        if(!expressionType.equal(new IntegerType()))
            throw new CheckingException("Latch value must be an integer");

        if(!typeEnvironment.get(this.variableName).equal(new IntegerType()))
            throw new CheckingException("Latch variable must be an integer");
            
        return typeEnvironment;
    }
}
