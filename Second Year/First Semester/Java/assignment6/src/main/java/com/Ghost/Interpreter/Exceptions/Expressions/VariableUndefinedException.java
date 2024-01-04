package com.Ghost.Interpreter.Exceptions.Expressions;

import com.Ghost.Interpreter.Exceptions.*;

public class VariableUndefinedException extends InterpreterException {
    public String toString() {
        return "VariableUndefinedException: The specified variable was not defined.";
    }
}
