package com.Ghost.Interpreter.ADTs;

import java.util.HashMap;

public class Dictionary<TKey, TData> implements IDictionary<TKey, TData> {
    Integer size;
    HashMap<TKey, TData> elements = new HashMap<TKey, TData>();

    public Dictionary<TKey, TData> deepCopy() {
        Dictionary<TKey, TData> newDictionary = new Dictionary<TKey, TData>();
        for(TKey key : this.elements.keySet())
            newDictionary.set(key, this.elements.get(key));
        return newDictionary;
    }

    public void set(TKey key, TData value) {
        this.elements.put(key, value);
        this.size = this.elements.size();
    }

    public TData get(TKey key) {
        return this.elements.get(key);
    }

    public Boolean has(TKey key) {
        return this.elements.containsKey(key);
    }

    public void remove(TKey key) {
        this.elements.remove(key);
        this.size = this.elements.size();
    }

    public HashMap<TKey, TData> all() {
        return this.elements;
    }

    public void clear() {
        this.elements.clear();
        this.size = this.elements.size();
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
