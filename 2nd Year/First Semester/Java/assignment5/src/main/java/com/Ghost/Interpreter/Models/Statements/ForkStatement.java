package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Repository.ProgramState;

public class ForkStatement implements IStatement {
    IStatement threadStatement;

    public ForkStatement(IStatement threadStatement) {
        this.threadStatement = threadStatement;
    }

    public void execute(ProgramState state) throws InterpreterException {
        ProgramState newThread = new ProgramState(state.get_interpreter(), state);
        newThread.get_execution_stack().push(this.threadStatement);
        newThread.start();
        newThread.get_interpreter().get_program_states().add(newThread);
    }

    public String toString() {
        return "fork(" + threadStatement.toString().replace("\n", "") + ");";
    }
}
