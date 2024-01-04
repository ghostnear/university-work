package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class NotBooleanValueException extends InterpreterException {
    public String toString() {
        return "NotBooleanValueException: The If statement condition is not a Boolean value.";
    }
}