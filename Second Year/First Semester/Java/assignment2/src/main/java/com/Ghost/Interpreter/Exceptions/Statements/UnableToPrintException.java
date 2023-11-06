package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class UnableToPrintException extends InterpreterException {
    public String toString() {
        return "UnableToPrintException: An error occured while trying to print.";
    }
}
