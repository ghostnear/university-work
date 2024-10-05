package com.me.assignment1.View;

import com.me.assignment1.Models.*;
import com.me.assignment1.Repository.*;
import com.me.assignment1.Controller.*;

public class Entry {
    public static void main(String[] args) {
        IRepository repository = new MemoryRepository(15);
        try {
            // Generate some stuff idk.
            for(int i = 1; i <= 5; i++)
            {
                repository.add(new Cube(i * 1.0));
                repository.add(new Sphere(i / 2.0));
                repository.add(new Cylinder(i / 2.0, i / 4.0));
            }

            // These shouldn't be added.
            repository.add(new Cube(25));
        } catch (Exception e) {
            System.out.println("[ERROR]: " + e.getMessage());
        }

        Controller service = new Controller(repository);
        View ui = new View(service);
        ui.run();
    }
}