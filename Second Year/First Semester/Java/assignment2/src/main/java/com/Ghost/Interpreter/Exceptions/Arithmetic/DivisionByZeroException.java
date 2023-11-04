package com.Ghost.Interpreter.Exceptions.Arithmetic;

import com.Ghost.Interpreter.Exceptions.*;

public class DivisionByZeroException extends InterpreterException {
    public String toString() {
        return "DivisionByZeroException: Tried divide a value by 0.";
    }
}
