package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class FileCouldNotBeClosedException extends InterpreterException {
    public String toString() {
        return "FileCouldNotBeClosedException: Opened file could not be closed for some reason.";
    }
}
