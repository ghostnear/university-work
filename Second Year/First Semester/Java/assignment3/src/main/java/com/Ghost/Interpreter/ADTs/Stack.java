package com.Ghost.Interpreter.ADTs;

import java.util.ArrayList;

import com.Ghost.Interpreter.Exceptions.Stack.*;

public class Stack<TData> implements IStack<TData> {
    Integer size;
    Integer capacity;
    ArrayList<TData> elements;

    public Stack(Integer newCapacity) {
        this.size = 0;
        this.capacity = newCapacity;
        this.elements = new ArrayList<TData>(this.capacity);
    }

    public TData top() throws EmptyStackException {
        if(this.size == 0)
            throw new EmptyStackException();
        return this.elements.get(this.size - 1);
    }

    public TData pop() throws EmptyStackException {
        if(this.size == 0)
            throw new EmptyStackException();

        TData result = this.elements.get(this.size - 1);
        this.elements.remove(this.size - 1);
        this.size--;
        return result;
    }

    public Integer size() {
        return this.size;
    }

    public boolean is_empty() {
        return this.size == 0;
    }

    public String toString() {
        String result = "";
        for(int index = this.size - 1; index >= 0; index--) {
            result += this.elements.get(index).toString() + "\n";
        }
        if(result == "")
            result = "<empty>\n";
        return result;
    }

    public void push(TData newElement) throws StackOverflowException {
        if(this.size >= this.capacity)
            throw new StackOverflowException();
        this.elements.add(newElement);
        this.size++;
    }

    public void clear() {
        this.elements.clear();
        this.size = 0;
    }
}
