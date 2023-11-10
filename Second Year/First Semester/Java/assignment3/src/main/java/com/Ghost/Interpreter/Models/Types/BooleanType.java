package com.Ghost.Interpreter.Models.Types;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.BooleanValue;

public class BooleanType implements IType {
    public boolean equal(Object another) {
        return another instanceof BooleanType;
    }

    public IValue default_value() {
        return new BooleanValue(false);
    }

    public String toString() {
        return "Boolean";
    }
}
