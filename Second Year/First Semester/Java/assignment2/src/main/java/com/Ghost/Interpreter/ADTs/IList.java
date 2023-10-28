package com.Ghost.Interpreter.ADTs;

import com.Ghost.Interpreter.Exceptions.List.*;

public interface IList<TData> {
    public void add(TData newElement) throws ListOverflowException;
    public TData get(Integer index) throws ListIndexOutOfBoundsException;
    public void set(Integer index, TData newElement) throws ListIndexOutOfBoundsException;
    public void remove(Integer index) throws ListIndexOutOfBoundsException;
    public Integer size();
    public Boolean isEmpty();
    public String toString();
}
