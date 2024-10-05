package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class FileNotExistentException extends InterpreterException {
    public String toString() {
        return "FileNotExistentException: Tried to open a file that does not exist.";
    }
}
