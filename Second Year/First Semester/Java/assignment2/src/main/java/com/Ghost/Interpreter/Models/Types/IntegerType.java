package com.Ghost.Interpreter.Models.Types;

import com.Ghost.Interpreter.Models.IType;
import com.Ghost.Interpreter.Models.IValue;
import com.Ghost.Interpreter.Models.Values.IntegerValue;

public class IntegerType implements IType {
    public boolean equals(Object another) {
        return another instanceof IntegerType;
    }

    public IValue defaultValue() {
        return new IntegerValue(0);
    }

    public String toString() {
        return "Integer";
    }
}
