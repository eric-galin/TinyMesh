// Sphere

// Self include
#include "sphere.h"

Sphere::Sphere(const Vector & c, double r) : center(c), radius(r){

}


double Sphere::Radius() const{
    return radius;
}

Vector Sphere::Center() const{
    return center;
}