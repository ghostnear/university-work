package com.Ghost.Interpreter.ADTs;

import java.util.HashMap;

public class Dictionary<TKey, TData> implements IDictionary<TKey, TData> {
    Integer size;
    HashMap<TKey, TData> elements = new HashMap<TKey, TData>();

    public void set(TKey key, TData value)
    {
        this.elements.put(key, value);
        this.size = this.elements.size();
    }

    public TData get(TKey key)
    {
        return this.elements.get(key);
    }

    public Boolean has(TKey key)
    {
        return this.elements.containsKey(key);
    }

    public void remove(TKey key)
    {
        this.elements.remove(key);
        this.size = this.elements.size();
    }

    public void clear()
    {
        this.elements.clear();
        this.size = this.elements.size();
    }

    public String toString()
    {
        String result = "";
        for(TKey key : this.elements.keySet())
        {
            result += key.toString() + " : " + this.elements.get(key).toString() + "\n";
        }
        return result;
    }

    public Integer size()
    {
        return this.size;
    }

    public Boolean isEmpty()
    {
        return this.size == 0;
    }
}
