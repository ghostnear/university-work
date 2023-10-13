package com.me.assignment1.Controller;

import java.util.ArrayList;

import com.me.assignment1.Models.IEntity;
import com.me.assignment1.Repository.*;

public class Controller {
    private IRepository repository;

    public Controller(IRepository newRepository)
    {
        repository = newRepository;
    }

    public void add(IEntity newEntity) throws Exception
    {
        repository.add(newEntity);
    }

    public IEntity[] getAll()
    {
        return repository.getAll();
    }

    public IEntity[] filterByVolume(double minVolume)
    {
        ArrayList<IEntity> result = new ArrayList<IEntity>();
        for(IEntity entity : repository.getAll())
            if(entity.getVolume() >= minVolume)
                result.add(entity);
        return result.toArray(new IEntity[result.size()]);
    }
}
