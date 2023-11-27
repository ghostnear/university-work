package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class FileCouldNotBeReadException extends InterpreterException {
    public String toString() {
        return "FileCouldNotBeReadException: Opened file could not be read for some reason.";
    }
}
