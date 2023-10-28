package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Models.IExpression;
import com.Ghost.Interpreter.Models.IValue;

public class ValueExpression implements IExpression {
    IValue val;

    public ValueExpression(IValue newVal) {
        this.val = newVal;
    }

    public String toString() {
        return val.toString();
    }
}
