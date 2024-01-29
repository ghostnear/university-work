package com.Ghost.Interpreter.ADTs;

import java.util.HashMap;

public class AtomicHeap<TKey, TData> implements IMemHeap<TKey, TData> {
    Integer size;
    Integer nextClear = 1;
    HashMap<TKey, TData> elements = new HashMap<TKey, TData>();

    void refresh_next() {
        synchronized(this.elements)
        {
            for(Integer index = 1; ; index++)
                if(!elements.containsKey(index))
                {
                    nextClear = index;
                    break;
                }
        }
    }

    public HashMap<TKey, TData> all() {
        synchronized(this.elements)
        {
            return this.elements;
        }
    }

    public void set(TKey key, TData value) {
        synchronized(this.elements)
        {
            this.elements.put(key, value);
            this.size = this.elements.size();
            refresh_next();
        }
    }

    public TData get(TKey key) {
        synchronized(this.elements)
        {
            return this.elements.get(key);
        }
    }

    public Boolean has(TKey key) {
        synchronized(this.elements)
        {
            return this.elements.containsKey(key);
        }
    }

    public Integer next_free() {
        synchronized(this.elements)
        {
            return nextClear;
        }
    }

    public void remove(TKey key) {
        synchronized(this.elements)
        {
            this.elements.remove(key);
            this.size = this.elements.size();
            refresh_next();
        }
    }

    public void clear() {
        synchronized(this.elements)
        {
            this.elements.clear();
            this.size = this.elements.size();
            nextClear = 1;
        }
    }

    public String toString() {
        synchronized(this.elements)
        {
            String result = "";
            for(TKey key : this.elements.keySet())
                result += key.toString() + " : " + this.elements.get(key).toString() + "\n";
            if(result == "")
                result = "<empty>\n";
            return result;
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

