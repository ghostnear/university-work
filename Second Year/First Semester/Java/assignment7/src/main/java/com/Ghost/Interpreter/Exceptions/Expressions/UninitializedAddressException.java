package com.Ghost.Interpreter.Exceptions.Expressions;

import com.Ghost.Interpreter.Exceptions.*;

public class UninitializedAddressException extends InterpreterException {
    public String toString() {
        return "UninitializedAddressException: The specified address does not exist.";
    }
}
