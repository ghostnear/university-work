package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.*;
import com.Ghost.Interpreter.Models.Types.*;
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

        if(resultLeft.get_type() instanceof BooleanType && resultRight.get_type() instanceof BooleanType) {
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

    public IType typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        IType typeLeft = this.left.typeCheck(typeEnvironment);
        IType typeRight = this.right.typeCheck(typeEnvironment);

        if(!(typeLeft instanceof BooleanType))
            throw new CheckingException("LogicExpression: Left operand is not a boolean!");

        if(!(typeRight instanceof BooleanType))
            throw new CheckingException("LogicExpression: Right operand is not a boolean!");

        return new BooleanType();
    }
}
