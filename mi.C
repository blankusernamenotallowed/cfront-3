struct IX { virtual int fx(); };
struct IY { virtual int fy(); };
struct C : IX, IY {
    int data;
    int fx();
    int fy();
};
int C::fx() { return data + 1; }
int C::fy() { return data + 2; }
int main() {
    C c;
    IX* px = &c;
    IY* py = &c;
    return px->fx() + py->fy();
}
