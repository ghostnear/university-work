package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class AssignStatement implements IStatement {
    String name;
    IExpression expression;

    public AssignStatement(String id, IExpression expression) {
        this.name = id;
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        state.getSymbolTable().set(this.name, this.expression.evaluate(state));
    }

    public String toString() {
        return name + " = " + expression.toString() + ";";
    }
}
