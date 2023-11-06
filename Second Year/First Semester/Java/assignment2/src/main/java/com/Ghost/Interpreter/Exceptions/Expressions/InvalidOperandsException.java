package com.Ghost.Interpreter.Exceptions.Expressions;

import com.Ghost.Interpreter.Exceptions.*;

public class InvalidOperandsException extends InterpreterException {
    public String toString() {
        return "InvalidOperandsException: Tried to use invalid operands with the specified operator.";
    }
}
