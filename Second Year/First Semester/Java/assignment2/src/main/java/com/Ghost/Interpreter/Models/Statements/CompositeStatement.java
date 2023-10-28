package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.Models.IStatement;

public class CompositeStatement implements IStatement {
    IStatement current, next;

    public CompositeStatement(IStatement current, IStatement next) {
        this.current = current;
        this.next = next;
    }

    public String toString()
    {
        return current.toString() + "\n" + next.toString();
    }
}
