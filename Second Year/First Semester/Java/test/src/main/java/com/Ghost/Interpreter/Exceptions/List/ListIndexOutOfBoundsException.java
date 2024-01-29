package com.Ghost.Interpreter.Exceptions.List;

import com.Ghost.Interpreter.Exceptions.*;

public class ListIndexOutOfBoundsException extends InterpreterException {
    public String toString() {
        return "ListIndexOutOfBoundsException: Tried to access an element outside of the list.";
    }
}
