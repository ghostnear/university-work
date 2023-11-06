package com.Ghost.Interpreter.Exceptions.Expressions;

import com.Ghost.Interpreter.Exceptions.*;

public class InvalidOperatorException extends InterpreterException {
    public String toString() {
        return "InvalidOperatorException: Tried to use an invalid operator.";
    }
}
