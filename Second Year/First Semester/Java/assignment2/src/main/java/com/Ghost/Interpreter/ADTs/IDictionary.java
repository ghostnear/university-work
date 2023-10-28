package com.Ghost.Interpreter.ADTs;

public interface IDictionary<TKey, TData> {
    public void set(TKey key, TData value);
    public TData get(TKey key);
    public Boolean has(TKey key);
    public void remove(TKey key);
    public String toString();
    public Integer size();
    public Boolean isEmpty();
}
