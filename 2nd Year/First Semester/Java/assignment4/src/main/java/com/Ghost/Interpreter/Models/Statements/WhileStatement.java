package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Statements.InvalidTypeException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.BooleanType;
import com.Ghost.Interpreter.Models.Values.BooleanValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class WhileStatement implements IStatement {
    IExpression condition;
    IStatement blockCode;
    IStatement nextStatement;

    public WhileStatement(IExpression condition, IStatement blockCode, IStatement nextStatement) {
        this.condition = condition;
        this.blockCode = blockCode;
        this.nextStatement = nextStatement;
    }

    public void execute(ProgramState state) throws InterpreterException {
        IValue conditionResult = condition.evaluate(state);
        if(!conditionResult.get_type().equal(new BooleanType()))
            throw new InvalidTypeException();

        BooleanValue result = (BooleanValue) conditionResult;
        if(result.get())
        {
            state.get_execution_stack().push(this);
            state.get_execution_stack().push(blockCode);
        }
        else
            state.get_execution_stack().push(nextStatement);  
    }

    public String toString() {
        return "while " + this.condition + " do\n" + this.blockCode + "\nend\n" + this.nextStatement;
    }
}
