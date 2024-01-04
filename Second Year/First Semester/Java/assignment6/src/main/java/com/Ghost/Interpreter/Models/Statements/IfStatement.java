package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Statements.NotBooleanValueException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.BooleanType;
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

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        IType type = this.condition.typeCheck(typeEnvironment);
        if(!(type instanceof BooleanType))
            throw new CheckingException("IfStatement: Condition is not a boolean!");

        this.action.typeCheck(typeEnvironment.clone());
        if(this.elseAction != null)
            this.elseAction.typeCheck(typeEnvironment.clone());

        return typeEnvironment;
    }
}
