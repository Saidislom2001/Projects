#include "Triangle.h"
#include <cmath>

Triangle::Triangle(double side1, double side2, double side3)
{
    a = side1;
    b = side2;
    c = side3;
}

double Triangle::perimeter() const
{
    return a + b + c;
}

double Triangle::area() const
{
    double s = perimeter() / 2.0;

    return sqrt(s * (s - a) * (s - b) * (s - c));
}