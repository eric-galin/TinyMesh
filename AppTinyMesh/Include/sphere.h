// Sphere

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Sphere {
protected:
    Vector center;
    double radius;

public:
    //! Empty.
    Sphere() {}
    explicit Sphere(const Vector&, double);

    double Radius() const;

    Vector Center() const;

    //! Empty.
    ~Sphere() {}
};



