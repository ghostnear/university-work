package com.Ghost.Interpreter.Models.Expressions;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class ValueExpression implements IExpression {
    IValue val;

    public ValueExpression(IValue newVal) {
        this.val = newVal;
    }

    public IValue evaluate(ProgramState state) {
        return this.val;
    }

    public String toString() {
        return val.toString();
    }

    public IType typeCheck(Dictionary<String, IType> typeEnvironment) {
        return val.get_type();
    }
}
