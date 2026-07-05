#include <stdio.h>

class Shape {
public:
    virtual double area()      { return 0; }
    virtual const char* name() { return "shape"; }
};
class Circle : public Shape {
    double r;
public:
    Circle(double x) { r = x; }
    double area()      { return 3.14159 * r * r; }
    const char* name() { return "circle"; }
};
class Square : public Shape {
    double s;
public:
    Square(double x) { s = x; }
    double area()      { return s * s; }
    const char* name() { return "square"; }
};

main() {
    Shape* zoo[2];
    zoo[0] = new Circle(2.0);
    zoo[1] = new Square(3.0);
    for (int i = 0; i < 2; i++)
        printf("%-6s %g\n", zoo[i]->name(), zoo[i]->area());
    return 0;
}
