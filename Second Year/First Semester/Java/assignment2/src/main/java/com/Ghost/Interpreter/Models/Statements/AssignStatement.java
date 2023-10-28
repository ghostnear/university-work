package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Models.IExpression;
import com.Ghost.Interpreter.Models.IStatement;

public class AssignStatement implements IStatement {
    String name;
    IExpression expression;

    public AssignStatement(String id, IExpression expression) {
        this.name = id;
        this.expression = expression;
    }

    public String toString() {
        return name + " = " + expression.toString() + ";";
    }
}
