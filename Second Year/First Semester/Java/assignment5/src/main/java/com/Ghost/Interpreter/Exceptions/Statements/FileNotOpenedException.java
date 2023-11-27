package com.Ghost.Interpreter.Exceptions.Statements;

import com.Ghost.Interpreter.Exceptions.*;

public class FileNotOpenedException extends InterpreterException {
    public String toString() {
        return "FileNotOpenedException: Tried to use a file that was not opened.";
    }
}
