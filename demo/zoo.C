#include <stdio.h>

// ---- a class hierarchy with virtual functions ----
class Animal {
protected:
    int legs;
public:
    Animal(int l)          { legs = l; }
    virtual ~Animal()      {}
    virtual const char* sound() { return "..."; }
    virtual const char* kind()  { return "animal"; }
    void introduce() {                       // non-virtual, calls virtuals
        printf("A %-4s has %d legs and says '%s'\n", kind(), legs, sound());
    }
};

class Dog : public Animal {
public:
    Dog() : Animal(4) {}                     // base-class init
    const char* sound() { return "woof"; }
    const char* kind()  { return "dog"; }
};

class Bird : public Animal {
public:
    Bird() : Animal(2) {}
    const char* sound() { return "tweet"; }
    const char* kind()  { return "bird"; }
};

// ---- operator overloading + default args ----
class Vec2 {
public:
    double x, y;
    Vec2(double a = 0, double b = 0) { x = a; y = b; }
    Vec2 operator+(Vec2 v) { return Vec2(x + v.x, y + v.y); }
    double dot(Vec2& v)    { return x * v.x + y * v.y; }
};

main()
{
    Animal* zoo[2];
    zoo[0] = new Dog;
    zoo[1] = new Bird;
    for (int i = 0; i < 2; i++)
        zoo[i]->introduce();                 // virtual dispatch

    Vec2 a(1, 2), b(3, 4);
    Vec2 c = a + b;                          // operator+
    printf("a+b = (%g, %g)   a.b = %g\n", c.x, c.y, a.dot(b));
    return 0;
}
