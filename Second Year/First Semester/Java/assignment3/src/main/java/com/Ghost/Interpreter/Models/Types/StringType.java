package com.Ghost.Interpreter.Models.Types;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.StringValue;

public class StringType implements IType {
    public boolean equal(Object another) {
        return another instanceof StringType;
    }

    public IValue defaultValue() {
        return new StringValue("");
    }

    public String toString() {
        return "String";
    }
}
