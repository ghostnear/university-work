package com.me.assignment1.Models;

public class Cylinder implements IEntity {
    double radius, height;

    // This creates a unit cylinder.
    public Cylinder() {
        this.radius = 1;
        this.height = 1;
    }

    // This creates a cylinder with the specified radius and height.
    public Cylinder(double newRadius, double newHeight) {
        this.radius = newRadius;
        this.height = newHeight;
    }

    public double getVolume() {
        return Math.PI * radius * radius * height;
    }

    public String toString() {
        return "Cylinder (radius: " + radius + ", height: " + height + ")";
    }
}
