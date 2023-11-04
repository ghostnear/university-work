package com.Ghost.Interpreter.Models.Types;

import com.Ghost.Interpreter.Models.IType;
import com.Ghost.Interpreter.Models.IValue;
import com.Ghost.Interpreter.Models.Values.IntegerValue;

public class IntegerType implements IType {
    public IntegerType() {

    }

    public IValue defaultValue() {
        return new IntegerValue(0);
    }

    public String toString() {
        return "Integer";
    }
}
