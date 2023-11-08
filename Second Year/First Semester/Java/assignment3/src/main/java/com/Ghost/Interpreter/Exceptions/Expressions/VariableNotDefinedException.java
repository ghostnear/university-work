package com.Ghost.Interpreter.Exceptions.Expressions;

import com.Ghost.Interpreter.Exceptions.*;

public class VariableNotDefinedException extends InterpreterException {
    public String toString() {
        return "VariableNotDefinedException: Tried to use an undefined variable.";
    }
}
