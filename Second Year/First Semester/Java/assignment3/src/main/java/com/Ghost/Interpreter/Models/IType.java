package com.Ghost.Interpreter.Models;

public interface IType {
    IValue defaultValue();
    boolean equal(Object other);
}