package com.Ghost.Interpreter.ADTs;

import com.Ghost.Interpreter.Exceptions.List.*;

public interface IList<TData> {
    void add(TData newElement) throws ListOverflowException;
    TData get(Integer index) throws ListIndexOutOfBoundsException;
    void set(Integer index, TData newElement) throws ListIndexOutOfBoundsException;
    void remove(Integer index) throws ListIndexOutOfBoundsException;
    Integer size();
    Boolean is_empty();
    String toString();
    void clear();
}
