package com.me.assignment1.View;

import com.me.assignment1.Models.*;
import com.me.assignment1.Controller.*;

public class View {
    private Controller service;

    public View(Controller newService)
    {
        this.service = newService;
    }

    public void run() {
        // Print all products first.
        int index = 0;
        System.out.println("All products present in the repository:");
        for(IEntity entity : service.getAll())
        {
            index++;
            System.out.println(index + ". " + entity + "\nWith volume: " + entity.getVolume());
        }

        System.out.println("\n-----------------------------------------\n");

        // Then print the filtered products.
        System.out.println("All products with a volume greater than 25cm3:");
        index = 0;
        for(IEntity entity : service.filterByVolume(25))
        {
            index++;
            System.out.println(index + ". " + entity + "\nWith volume: " + entity.getVolume());
        }
    }
}
