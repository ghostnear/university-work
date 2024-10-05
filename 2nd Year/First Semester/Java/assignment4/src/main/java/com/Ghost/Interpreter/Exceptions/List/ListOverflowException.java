package com.Ghost.Interpreter.Exceptions.List;

import com.Ghost.Interpreter.Exceptions.*;

public class ListOverflowException extends InterpreterException {
    public String toString() {
        return "ListOverflowException: Tried to append to a full list.";
    }
}
