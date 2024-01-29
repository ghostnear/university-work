package com.Ghost.Interpreter.ADTs;

import java.util.ArrayList;

import com.Ghost.Interpreter.Exceptions.List.*;

public class AtomicList<TData> implements IList<TData> {
    Integer size;
    Integer capacity;
    ArrayList<TData> elements;

    public AtomicList(Integer newCapacity) {
        this.size = 0;
        this.capacity = newCapacity;
        this.elements = new ArrayList<TData>(this.capacity);
    }

    public String toString() {
        synchronized(this.elements)
        {
            String result = "";
            for(TData element : this.elements)
                result += element.toString() + "\n";
            if(result == "")
                result = "<empty>\n";
            return result;
        }
    }

    public void add(TData newElement) throws ListOverflowException {
        synchronized(this.elements)
        {
            if(this.size >= this.capacity)
                throw new ListOverflowException();
            this.elements.add(newElement);
            this.size++;
        }
    }

    public TData get(Integer index) throws ListIndexOutOfBoundsException {
        synchronized(this.elements)
        {
            if(index < 0 || index >= this.size)
                throw new ListIndexOutOfBoundsException();
            return this.elements.get(index);
        }
    }

    public void set(Integer index, TData newElement) throws ListIndexOutOfBoundsException {
        synchronized(this.elements)
        {
            if(index < 0 || index >= this.size)
                throw new ListIndexOutOfBoundsException();
            this.elements.set(index, newElement);
        }
    }

    public void remove(Integer index) throws ListIndexOutOfBoundsException {
        synchronized(this.elements)
        {
            if(index < 0 || index >= this.size)
                throw new ListIndexOutOfBoundsException();
            this.elements.remove(index);
            this.size--;
        }
    }

    public void clear() {
        synchronized(this.elements)
        {
            this.elements.clear();
            this.size = 0;
        }
    }

    public Integer size() {
        synchronized(this.size)
        {
            return this.size;
        }
    }

    public Boolean is_empty() {
        synchronized(this.size)
        {
            return this.size == 0;
        }
    }
}
