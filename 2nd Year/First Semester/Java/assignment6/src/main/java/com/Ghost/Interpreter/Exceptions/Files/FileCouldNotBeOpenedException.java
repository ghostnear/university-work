package com.Ghost.Interpreter.Exceptions.Files;

import com.Ghost.Interpreter.Exceptions.*;

public class FileCouldNotBeOpenedException extends InterpreterException {
    public String toString() {
        return "FileCouldNotBeOpenedException: The attempt to open the specified file failed.";
    }
}
