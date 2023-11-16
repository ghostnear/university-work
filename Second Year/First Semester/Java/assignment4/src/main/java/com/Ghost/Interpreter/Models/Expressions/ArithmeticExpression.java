package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.IntegerType;
import com.Ghost.Interpreter.Models.Types.RefferenceType;
import com.Ghost.Interpreter.Models.Values.IntegerValue;
import com.Ghost.Interpreter.Models.Values.RefferenceValue;
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

        Integer result = 0;
        Integer leftValue;
        Integer rightValue;

        if(resultLeft.get_type() instanceof IntegerType && resultRight.get_type() instanceof IntegerType) {
            leftValue = ((IntegerValue)resultLeft).get();
            rightValue = ((IntegerValue)resultRight).get();

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
        else if(resultLeft.get_type() instanceof IntegerType && resultRight.get_type() instanceof RefferenceType) {
            leftValue = ((IntegerValue)resultLeft).get();
            rightValue = ((RefferenceValue)resultRight).get_address();

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
                default:
                    throw new InvalidOperatorException();
            }

            return new RefferenceValue(result, ((RefferenceValue)resultRight).get_type());
        }
        else if(resultLeft.get_type() instanceof RefferenceType && resultRight.get_type() instanceof IntegerType) {
            leftValue = ((RefferenceValue)resultLeft).get_address();
            rightValue = ((IntegerValue)resultRight).get();

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

            return new RefferenceValue(result, ((RefferenceValue)resultLeft).get_type());
        }      
        else {
            throw new InvalidOperandsException();
        }
    }

    public String toString() {
        return this.left.toString() + ' ' + this.operator + ' ' + this.right.toString();
    }
}
