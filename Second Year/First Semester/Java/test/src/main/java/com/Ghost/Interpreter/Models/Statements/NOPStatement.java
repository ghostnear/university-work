package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Models.IType;
import com.Ghost.Interpreter.Repository.ProgramState;

public class NOPStatement implements IStatement {
    public void execute(ProgramState state) throws InterpreterException {
        // Do nothing
    }

    public String toString() {
        return "NOP;";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        return typeEnvironment;
    }
}
