package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.IValue;

public class BooleanValue implements IValue {
    Boolean value;

    public BooleanValue(Boolean newValue) {
        this.value = newValue;
    }

    public Boolean get() {
        return value;
    }

    public String toString() {
        return value.toString();
    }
}
