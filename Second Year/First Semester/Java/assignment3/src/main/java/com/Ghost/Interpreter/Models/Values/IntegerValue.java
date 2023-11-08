package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.IntegerType;

public class IntegerValue implements IValue {
    Integer value;

    public IntegerValue(Integer newValue) {
        this.value = newValue;
    }

    public IType getType() {
        return new IntegerType();
    }

    public Integer get() {
        return value;
    }

    public String toString() {
        return value.toString();
    }
}
