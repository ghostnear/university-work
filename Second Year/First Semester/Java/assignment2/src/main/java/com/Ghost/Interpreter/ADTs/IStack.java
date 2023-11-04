package com.Ghost.Interpreter.ADTs;

import com.Ghost.Interpreter.Exceptions.Stack.*;

public interface IStack<TData> {
    void push(TData newElement) throws StackOverflowException;
    TData pop() throws EmptyStackException;
    Integer size();
    boolean isEmpty();
    String toString();
    void clear();
}
