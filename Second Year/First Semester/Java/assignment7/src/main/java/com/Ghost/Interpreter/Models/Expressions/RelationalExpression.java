package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.BooleanType;
import com.Ghost.Interpreter.Models.Types.IntegerType;
import com.Ghost.Interpreter.Models.Values.BooleanValue;
import com.Ghost.Interpreter.Models.Values.IntegerValue;
import com.Ghost.Interpreter.Repository.ProgramState;

public class RelationalExpression implements IExpression {
    String operator;
    IExpression left;
    IExpression right;

    public RelationalExpression(String newOperator, IExpression newLeft, IExpression newRight) {
        this.operator = newOperator;
        this.left = newLeft;
        this.right = newRight;
    }

    public IValue evaluate(ProgramState state) throws InterpreterException {
        IValue resultLeft = left.evaluate(state);
        IValue resultRight = right.evaluate(state);

        if(resultLeft.get_type() instanceof IntegerType && resultRight.get_type() instanceof IntegerType) {
            boolean result = false;
            Integer leftValue = ((IntegerValue)resultLeft).get();
            Integer rightValue = ((IntegerValue)resultRight).get();

            switch(this.operator) {
                case "<":
                    result = leftValue < rightValue;
                    break;
                case "<=":
                    result = leftValue <= rightValue;
                    break;
                case "==":
                    result = leftValue == rightValue;
                    break;
                case "!=":
                    result = leftValue != rightValue;
                    break;
                case ">":
                    result = leftValue > rightValue;
                    break;
                case ">=":
                    result = leftValue >= rightValue;
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
        IType typeLeft, typeRight;
        typeLeft = left.typeCheck(typeEnvironment);
        typeRight = right.typeCheck(typeEnvironment);

        if(typeLeft.equals(new IntegerType())) {
            if(typeRight.equals(new IntegerType())) {
                return new BooleanType();
            }
            else {
                throw new CheckingException("RelationalExpression: Right operand is not an integer.");
            }
        }
        else {
            throw new InvalidOperandsException();
        }
    }
}
