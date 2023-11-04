package com.Ghost.Interpreter.Models;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Repository.ProgramState;

public interface IExpression {
    IValue evaluate(ProgramState state) throws InterpreterException;
}
