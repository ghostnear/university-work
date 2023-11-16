package com.Ghost.Interpreter.ADTs;

public interface IMemHeap<TKey, TData> {
    void set(TKey key, TData value);
    TData get(TKey key);
    Boolean has(TKey key);
    Integer next_free();
    void remove(TKey key);
    void clear();
    Integer size();
    Boolean is_empty();
}
