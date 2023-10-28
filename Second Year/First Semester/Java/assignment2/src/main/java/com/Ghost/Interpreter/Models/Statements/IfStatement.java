package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Models.*;

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

    public String toString() {
        return "if(" + this.condition.toString() + ") then\n  " + this.action.toString() + "\n" + "else\n  " + this.elseAction.toString() + "\n" + "end";
    }
}
