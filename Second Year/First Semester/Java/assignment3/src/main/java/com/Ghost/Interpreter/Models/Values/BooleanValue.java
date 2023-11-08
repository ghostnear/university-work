package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.BooleanType;

public class BooleanValue implements IValue {
    Boolean value;

    public BooleanValue(Boolean newValue) {
        this.value = newValue;
    }

    public IType getType() {
        return new BooleanType();
    }

    public boolean equal(Object other) {
        return other instanceof BooleanValue && ((BooleanValue)other).get() == value;
    }

    public Boolean get() {
        return value;
    }

    public String toString() {
        return value.toString();
    }
}
