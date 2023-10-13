package com.me.assignment1.Repository;

import com.me.assignment1.Models.*;

public class MemoryRepository implements IRepository {
    private Integer size;
    private Integer capacity;
    private IEntity[] elements;

    public MemoryRepository() {
        this.size = 0;
        this.capacity = 0;
        this.elements = new IEntity[this.capacity];
    }

    public MemoryRepository(Integer newCapacity) {
        this.size = 0;
        this.capacity = newCapacity;
        this.elements = new IEntity[this.capacity];
    }

    public void add(IEntity newEntity) throws Exception {
        if(this.size >= this.capacity)
            throw new Exception("Repository is full");

        this.elements[this.size] = newEntity;
        this.size++;
    }
    
    public Integer getSize() {
        return this.size;
    }

    public IEntity[] getAll() {
        return this.elements;
    }
}
