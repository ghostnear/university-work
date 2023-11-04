package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Arithmetic.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.BooleanValue;
import com.Ghost.Interpreter.Models.Values.IntegerValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class ArithmeticExpression implements IExpression {
    String operator;
    IExpression left;
    IExpression right;

    public ArithmeticExpression(String newOperator, IExpression newLeft, IExpression newRight) {
        this.operator = newOperator;
        this.left = newLeft;
        this.right = newRight;
    }

    public IValue evaluate(ProgramState state) throws InterpreterException {
        IValue resultLeft = left.evaluate(state);
        IValue resultRight = right.evaluate(state);

        if(resultLeft instanceof IntegerValue && resultRight instanceof IntegerValue) {
            int result = 0;
            int leftValue = ((IntegerValue)resultLeft).get();
            int rightValue = ((IntegerValue)resultRight).get();

            switch(this.operator) {
                case "+":
                    result = leftValue + rightValue;
                    break;
                case "-":
                    result = leftValue - rightValue;
                    break;
                case "*":
                    result = leftValue * rightValue;
                    break;
                case "/":
                    if(rightValue == 0) {
                        throw new DivisionByZeroException();
                    }
                    result = leftValue / rightValue;
                    break;
                default:
                    throw new InvalidOperatorException();
            }

            return new IntegerValue(result);
        }
        else if(resultLeft instanceof BooleanValue && resultRight instanceof BooleanValue) {
            boolean result = false;
            boolean leftValue = ((BooleanValue)resultLeft).get();
            boolean rightValue = ((BooleanValue)resultRight).get();

            switch(this.operator) {
                case "&&":
                    result = leftValue && rightValue;
                    break;
                case "||":
                    result = leftValue || rightValue;
                    break;
                case "==":
                    result = leftValue == rightValue;
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
