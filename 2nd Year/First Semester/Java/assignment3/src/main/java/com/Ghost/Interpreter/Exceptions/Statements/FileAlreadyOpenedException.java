package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class FileAlreadyOpenedException extends InterpreterException {
    public String toString() {
        return "FileAlreadyOpenedException: Tried to open a file that already exists.";
    }
}
