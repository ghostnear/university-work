package com.Ghost.Interpreter.Models;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Repository.*;

public interface IStatement {
    String toString();
    void execute(ProgramState programState) throws InterpreterException;
    Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException;
}
