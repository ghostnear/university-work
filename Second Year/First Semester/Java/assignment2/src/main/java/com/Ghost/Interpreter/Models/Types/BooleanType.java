package com.Ghost.Interpreter.Models.Types;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.BooleanValue;

public class BooleanType implements IType {
    public IValue defaultValue() {
        return new BooleanValue(false);
    }

    public String toString() {
        return "Boolean";
    }
}
