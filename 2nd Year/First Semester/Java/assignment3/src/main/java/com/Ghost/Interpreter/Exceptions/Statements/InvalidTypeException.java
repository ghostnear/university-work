package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class InvalidTypeException extends InterpreterException {
    public String toString() {
        return "InvalidTypeException: Tried to use values with different types than what is required.";
    }
}
