package com.Ghost.Interpreter.Exceptions.Stack;

public class StackOverflowException extends Exception {
    public String toString() {
        return "StackOverflowException: Tried to push to a full stack.";
    }
}
