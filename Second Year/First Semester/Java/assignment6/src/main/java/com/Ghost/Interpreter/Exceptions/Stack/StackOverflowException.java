package com.Ghost.Interpreter.Exceptions.Stack;

import com.Ghost.Interpreter.Exceptions.InterpreterException;

public class StackOverflowException extends InterpreterException {
    public String toString() {
        return "StackOverflowException: Tried to push to a full stack.";
    }
}
