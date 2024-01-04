package com.Ghost.Interpreter.Exceptions;

public class CheckingException extends InterpreterException {
    String message = "";

    public CheckingException(String message) {
        this.message = message;
    }

    public String toString() {
        return "CheckingException: An error occured while checking the program:\n" + this.message;
    }
}
