package com.Ghost.Interpreter.Models.Types;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Values.RefferenceValue;

public class RefferenceType implements IType {
    IType destinationType;

    public RefferenceType(IType innerType) {
        destinationType = innerType;
    }

    public IType getType() {
        return destinationType;
    }

    public boolean equal(Object another) {
        if(!(another instanceof RefferenceType))
            return false;
        return ((RefferenceType) another).getType().equal(destinationType);
    }

    public IValue default_value() {
        return new RefferenceValue(0, destinationType);
    }

    public String toString() {
        return "Refference";
    }
}
