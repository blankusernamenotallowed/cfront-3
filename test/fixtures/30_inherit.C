#include <stdio.h>
class Animal {
protected:
    int legs;
public:
    Animal(int l) { legs = l; }
    int numlegs() { return legs; }
};
class Dog : public Animal {
public:
    Dog() : Animal(4) {}
};
main() {
    Dog d;
    printf("legs=%d\n", d.numlegs());
    return 0;
}
