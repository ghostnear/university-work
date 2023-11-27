package com.Ghost.Interpreter.Exceptions.Expressions;

import com.Ghost.Interpreter.Exceptions.*;

public class TypeMismatchException extends InterpreterException {
    public String toString() {
        return "TypeMismatchException: The specified value is not of the same type as the variable.";
    }
}
