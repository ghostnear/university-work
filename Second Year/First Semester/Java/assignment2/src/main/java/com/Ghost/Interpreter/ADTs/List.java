package com.Ghost.Interpreter.ADTs;

import java.util.ArrayList;

import com.Ghost.Interpreter.Exceptions.List.*;

public class List<TData> implements IList<TData> {
    Integer size;
    Integer capacity;
    ArrayList<TData> elements;

    public List(Integer newCapacity) {
        this.size = 0;
        this.capacity = newCapacity;
        this.elements = new ArrayList<TData>(this.capacity);
    }

    public String toString() {
        String result = "";
        for(TData element : this.elements)
            result += element.toString() + "\n";
        return result;
    }

    public void add(TData newElement) throws ListOverflowException {
        if(this.size >= this.capacity)
            throw new ListOverflowException();
        this.elements.add(newElement);
        this.size++;
    }

    public TData get(Integer index) throws ListIndexOutOfBoundsException {
        if(index < 0 || index >= this.size)
            throw new ListIndexOutOfBoundsException();
        return this.elements.get(index);
    }

    public void set(Integer index, TData newElement) throws ListIndexOutOfBoundsException {
        if(index < 0 || index >= this.size)
            throw new ListIndexOutOfBoundsException();
        this.elements.set(index, newElement);
    }

    public void remove(Integer index) throws ListIndexOutOfBoundsException {
        if(index < 0 || index >= this.size)
            throw new ListIndexOutOfBoundsException();
        this.elements.remove(index);
        this.size--;
    }

    public void clear() {
        this.elements.clear();
        this.size = 0;
    }

    public Integer size() {
        return this.size;
    }

    public Boolean isEmpty() {
        return this.size == 0;
    }
}
