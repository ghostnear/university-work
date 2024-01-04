package com.Ghost.Interpreter.ADTs;

import java.util.HashMap;

public class Heap<TKey, TData> implements IMemHeap<TKey, TData> {
    Integer size;
    Integer nextClear = 1;
    HashMap<TKey, TData> elements = new HashMap<TKey, TData>();

    void refresh_next() {
        for(Integer index = 1; ; index++)
            if(!elements.containsKey(index))
            {
                nextClear = index;
                break;
            }
    }

    public HashMap<TKey, TData> all() {
        return elements;
    }

    public void set(TKey key, TData value) {
        this.elements.put(key, value);
        this.size = this.elements.size() + 1;
        refresh_next();
    }

    public TData get(TKey key) {
        return this.elements.get(key);
    }

    public Boolean has(TKey key) {
        return this.elements.containsKey(key);
    }

    public Integer next_free() {
        return nextClear;
    }

    public void remove(TKey key) {
        this.elements.remove(key);
        this.size = this.elements.size();
        refresh_next();
    }

    public void clear() {
        this.elements.clear();
        this.size = this.elements.size();
        nextClear = 1;
    }

    public String toString() {
        String result = "";
        for(TKey key : this.elements.keySet())
            result += key.toString() + " : " + this.elements.get(key).toString() + "\n";
        if(result == "")
            result = "<empty>\n";
        return result;
    }

    public Integer size() {
        return this.size;
    }

    public Boolean is_empty() {
        return this.size == 0;
    }
}

