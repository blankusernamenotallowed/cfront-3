#include <stdio.h>

class Shape {
public:
    virtual double area()       { return 0; }
    virtual const char* name()  { return "shape"; }
    void describe() { printf("%-8s area = %g\n", name(), area()); }
};

class Circle : public Shape {
    double r;
public:
    Circle(double radius) { r = radius; }
    double area()      { return 3.14159 * r * r; }
    const char* name() { return "circle"; }
};

class Square : public Shape {
    double s;
public:
    Square(double side) { s = side; }
    double area()      { return s * s; }
    const char* name() { return "square"; }
};

main()
{
    Shape* shapes[2];
    shapes[0] = new Circle(2.0);
    shapes[1] = new Square(3.0);
    for (int i = 0; i < 2; i++)
        shapes[i]->describe();          // virtual dispatch
    return 0;
}
