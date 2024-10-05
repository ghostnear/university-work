package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.BooleanValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class LogicExpression implements IExpression {
    String operator;
    IExpression left;
    IExpression right;

    public LogicExpression(String newOperator, IExpression newLeft, IExpression newRight) {
        this.operator = newOperator;
        this.left = newLeft;
        this.right = newRight;
    }

    public IValue evaluate(ProgramState state) throws InterpreterException {
        IValue resultLeft = left.evaluate(state);
        IValue resultRight = right.evaluate(state);

        if(resultLeft instanceof BooleanValue && resultRight instanceof BooleanValue) {
            boolean result = false;
            Boolean leftValue = ((BooleanValue)resultLeft).get();
            Boolean rightValue = ((BooleanValue)resultRight).get();

            switch(this.operator) {
                case "&&":
                    result = leftValue && rightValue;
                    break;
                case "||":
                    result = leftValue || rightValue;
                    break;
                default:
                    throw new InvalidOperatorException();
            }

            return new BooleanValue(result);
        }
        else {
            throw new InvalidOperandsException();
        }
    }

    public String toString() {
        return this.left.toString() + ' ' + this.operator + ' ' + this.right.toString();
    }
}
