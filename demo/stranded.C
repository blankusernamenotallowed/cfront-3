// Show the vptr getting STRANDED in the middle when a derived
// class adds its own data (the wrinkle that killed vptr-at-end).
class Animal {
protected:
    int legs;                 // base data
public:
    virtual int sound() { return 0; }
};

class Dog : public Animal {
    int tail_length;          // DERIVED data — where does it go?
public:
    int sound() { return 1; }
};

int main()
{
    Dog* d = new Dog;
    Animal* a = d;            // single-inheritance upcast
    return a->sound();
}
