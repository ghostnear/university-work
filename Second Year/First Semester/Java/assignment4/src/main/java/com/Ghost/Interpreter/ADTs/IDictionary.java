package com.Ghost.Interpreter.ADTs;

public interface IDictionary<TKey, TData> {
    void set(TKey key, TData value);
    TData get(TKey key);
    Boolean has(TKey key);
    void remove(TKey key);
    String toString();
    Integer size();
    Boolean is_empty();
    void clear();
}
