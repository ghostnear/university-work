package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Models.IExpression;

public class VariableExpression implements IExpression {
    String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    public String toString() {
        return id;
    }
}
