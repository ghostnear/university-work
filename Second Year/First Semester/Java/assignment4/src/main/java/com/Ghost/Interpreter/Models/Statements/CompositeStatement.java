package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Exceptions.Stack.StackOverflowException;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Repository.ProgramState;

public class CompositeStatement implements IStatement {
    IStatement current, next;

    public CompositeStatement(IStatement current, IStatement next) {
        this.current = current;
        this.next = next;
    }

    public void execute(ProgramState state) {
        try {
            state.get_execution_stack().push(next);
            state.get_execution_stack().push(current);
        }
        catch(StackOverflowException e) {
            System.out.println(e);
        }
    }

    public String toString() {
        return current.toString() + "\n" + next.toString();
    }
}
