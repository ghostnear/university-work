package com.Ghost.Interpreter.Models;

public interface IType {
    IValue default_value();
    boolean equal(Object other);
}