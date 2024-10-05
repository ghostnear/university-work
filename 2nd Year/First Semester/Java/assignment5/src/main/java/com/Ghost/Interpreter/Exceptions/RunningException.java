package com.Ghost.Interpreter.Exceptions;

public class RunningException extends InterpreterException {
    String message = "";

    public RunningException(String message) {
        this.message = message;
    }

    public String toString() {
        return "RunningException: " + this.message;
    }
}
