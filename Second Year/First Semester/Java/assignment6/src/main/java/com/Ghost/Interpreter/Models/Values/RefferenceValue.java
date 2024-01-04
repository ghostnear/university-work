package com.Ghost.Interpreter.Models.Values;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.RefferenceType;

public class RefferenceValue implements IValue {
    Integer address;
    IType type;

    public RefferenceValue(IType type) {
        this.address = 0;
        this.type = type;
    }

    public RefferenceValue(Integer address, IType type) {
        this.type = type;
        this.address = address;
    }

    public IType get_type() {
        return new RefferenceType(type);
    }

    public IType get_refferenced_type() {
        return type;
    }

    public Integer get_address() {
        return address;
    }

    public boolean equal(Object other) {
        return other instanceof RefferenceValue && ((RefferenceValue)other).get_address() == address && ((RefferenceValue)other).get_type().equal(type);
    }

    public String toString() {
        return "Refference<" + this.type.toString() + ">(" + address.toString() + ")";
    }
}
