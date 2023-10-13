package com.me.assignment1.Models;

public class Sphere implements IEntity {
    double radius;

    // This creates a unit sphere.
    public Sphere() {
        this.radius = 1;
    }

    // This creates a sphere with the specified radius.
    public Sphere(double newRadius) {
        this.radius = newRadius;
    }

    public double getVolume() {
        return 4 * Math.PI * radius * radius * radius / 3;
    }

    public String toString() {
        return "Sphere (radius: " + radius + ")";
    }
}
