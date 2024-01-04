package com.Ghost.Interpreter.ADTs;

import java.util.HashMap;

public interface IMemHeap<TKey, TData> {
    void set(TKey key, TData value);
    TData get(TKey key);
    Boolean has(TKey key);
    Integer next_free();
    void remove(TKey key);
    void clear();
    Integer size();
    public HashMap<TKey, TData> all();
    Boolean is_empty();
}
