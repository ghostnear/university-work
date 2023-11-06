package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.List.ListOverflowException;
import com.Ghost.Interpreter.Exceptions.Statements.UnableToPrintException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class PrintStatement implements IStatement {
    IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        try {
            state.getOutput().add(expression.evaluate(state));
        }
        catch(ListOverflowException e) {
            throw new UnableToPrintException();
        }
    }

    public String toString() {
        return "print(" + expression.toString() + ");";
    }
}
