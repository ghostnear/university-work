package com.Ghost.Interpreter.Models;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Repository.*;

public interface IStatement {
    String toString();
    void execute(ProgramState programState) throws InterpreterException;
}
