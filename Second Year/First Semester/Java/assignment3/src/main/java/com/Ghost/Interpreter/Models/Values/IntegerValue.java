package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.IntegerType;

public class IntegerValue implements IValue {
    Integer value;

    public IntegerValue(Integer newValue) {
        this.value = newValue;
    }

    public IType get_type() {
        return new IntegerType();
    }

    public Integer get() {
        return value;
    }

    public boolean equal(Object other) {
        return other instanceof IntegerValue && ((IntegerValue)other).get() == value;
    }

    public String toString() {
        return value.toString();
    }
}
