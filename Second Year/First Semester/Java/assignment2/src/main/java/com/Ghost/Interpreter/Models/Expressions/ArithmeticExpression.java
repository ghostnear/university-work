package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Models.IExpression;

public class ArithmeticExpression implements IExpression {
    char operator;
    IExpression left;
    IExpression right;

    public ArithmeticExpression(char newOperator, IExpression newLeft, IExpression newRight) {
        this.operator = newOperator;
        this.left = newLeft;
        this.right = newRight;
    }

    public String toString()
    {
        return this.left.toString() + ' ' + this.operator + ' ' + this.right.toString();
    }
}
