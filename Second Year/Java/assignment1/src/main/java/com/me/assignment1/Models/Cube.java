package com.me.assignment1.Models;

public class Cube implements IEntity {
    double side;
    
    // This creates a unit cube.
    public Cube() {
        this.side = 1;
    }

    // This creates a cube with the specified side length.
    public Cube(double newSide) {
        this.side = newSide;
    }

    public double getVolume() {
        return side * side * side;
    }

    public String toString() {
        return "Cube (side: " + side + ")";
    }
}
