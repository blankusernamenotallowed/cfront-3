// Three levels, each adding data. Does a SECOND vptr gap appear?
class Animal {
protected:
    int legs;
public:
    virtual int sound() { return 0; }
};

class Dog : public Animal {
    int tail_length;          // Dog's data
public:
    int sound() { return 1; }
};

class Puppy : public Dog {
    int cuteness;             // Puppy's data
public:
    int sound() { return 2; }
};

int main()
{
    Puppy* p = new Puppy;
    Animal* a = p;
    return a->sound();
}
