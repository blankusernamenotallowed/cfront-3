// TWO polymorphic bases, each with data + a virtual -> TWO vptrs.
class Base1 {
    int a;
public:
    virtual int f1() { return 1; }
};

class Base2 {
    int b;
public:
    virtual int f2() { return 2; }
};

class Derived : public Base1, public Base2 {
    int c;
public:
    int f1() { return 10; }
    int f2() { return 20; }
};

int main()
{
    Derived* d = new Derived;
    Base1* p1 = d;      // sees vptr #1
    Base2* p2 = d;      // sees vptr #2 (needs +offset)
    return p1->f1() + p2->f2();
}
