package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class VariableAlreadyDefinedException extends InterpreterException {
    public String toString() {
        return "VariableAlreadyDefinedException: The variable that was trying to be defined already exists.";
    }
}

