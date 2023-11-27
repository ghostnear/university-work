package com.Ghost.Interpreter.ADTs;

import java.util.HashMap;

public interface IDictionary<TKey, TData> {
    void set(TKey key, TData value);
    TData get(TKey key);
    Boolean has(TKey key);
    void remove(TKey key);
    String toString();
    Integer size();
    Boolean is_empty();
    public HashMap<TKey, TData> all();
    void clear();
}
