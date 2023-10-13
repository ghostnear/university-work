package com.me.assignment1.Repository;

import com.me.assignment1.Models.*;

public interface IRepository {
    void add(IEntity newEntity) throws Exception;
    Integer getSize();
    IEntity[] getAll();
}
