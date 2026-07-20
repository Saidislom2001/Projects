#include <iostream>

#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

using namespace std;

int main()
{
    Circle circle(5);

    Rectangle rectangle(4, 6);

    Triangle triangle(3, 4, 5);

    cout << "Circle" << endl;
    cout << "Area: " << circle.area() << endl;
    cout << "Perimeter: " << circle.perimeter() << endl;

    cout << endl;

    cout << "Rectangle" << endl;
    cout << "Area: " << rectangle.area() << endl;
    cout << "Perimeter: " << rectangle.perimeter() << endl;

    cout << endl;

    cout << "Triangle" << endl;
    cout << "Area: " << triangle.area() << endl;
    cout << "Perimeter: " << triangle.perimeter() << endl;

    return 0;
}