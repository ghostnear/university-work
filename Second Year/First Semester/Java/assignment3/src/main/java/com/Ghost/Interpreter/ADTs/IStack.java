package com.Ghost.Interpreter.ADTs;

import com.Ghost.Interpreter.Exceptions.Stack.*;

public interface IStack<TData> {
    void push(TData newElement) throws StackOverflowException;
    TData pop() throws EmptyStackException;
    TData top() throws EmptyStackException;
    Integer size();
    boolean is_empty();
    String toString();
    void clear();
}
