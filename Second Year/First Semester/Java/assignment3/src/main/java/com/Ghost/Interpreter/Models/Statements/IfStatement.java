package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Statements.NotBooleanValueException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.BooleanValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class IfStatement implements IStatement {
    IExpression condition;
    IStatement action;
    IStatement elseAction;

    public IfStatement(IExpression newCondition, IStatement newAction, IStatement newElse)
    {
        this.condition = newCondition;
        this.action = newAction;
        this.elseAction = newElse;
    }

    public void execute(ProgramState state) throws InterpreterException {
        IValue conditionValue = this.condition.evaluate(state);
        if(!(conditionValue instanceof BooleanValue)) {
            throw new NotBooleanValueException();
        }

        if(((BooleanValue)conditionValue).get()) {
            this.action.execute(state);
        }
        else if(this.elseAction != null) {
            this.elseAction.execute(state);
        }
    }

    public String toString() {
        if(this.elseAction == null)
            return "if(" + this.condition.toString() + ") then\n  " + this.action.toString() + "\n" + "end";
        else
            return "if(" + this.condition.toString() + ") then\n  " + this.action.toString() + "\n" + "else\n  " + this.elseAction.toString() + "\n" + "end";
    }
}
