package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.StringType;

public class StringValue implements IValue {
    String value;

    public StringValue(String newValue) {
        this.value = newValue;
    }

    public IType get_type() {
        return new StringType();
    }

    public String get() {
        return value;
    }
    
    public boolean equal(Object other) {
        return other instanceof StringValue && ((StringValue)other).get() == value;
    }

    public String toString() {
        return value;
    }
}
