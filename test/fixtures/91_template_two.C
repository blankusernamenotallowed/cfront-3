#include <stdio.h>
template<class T>
class Box {
    T v_;
public:
    Box(T v) { v_ = v; }
    T get() { return v_; }
};
main() {
    Box<int> a(42);
    Box<double> b(3.5);
    printf("%d %g\n", a.get(), b.get());
    return 0;
}
