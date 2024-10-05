package com.Ghost.Interpreter.Exceptions.Stack;

import com.Ghost.Interpreter.Exceptions.*;

public class EmptyStackException extends InterpreterException {
    public String toString() {
        return "EmptyStackException: Tried to pop from an empty stack.";
    }
}
