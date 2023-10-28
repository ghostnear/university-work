package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Models.IExpression;
import com.Ghost.Interpreter.Models.IStatement;

public class PrintStatement implements IStatement {
    IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    public String toString() {
        return "print(" + expression.toString() + ");";
    }
}
