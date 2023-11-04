package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.*;

public class IntegerValue implements IValue {
    Integer value;

    public IntegerValue(Integer newValue) {
        this.value = newValue;
    }

    public Integer get() {
        return value;
    }

    public String toString() {
        return value.toString();
    }
}
