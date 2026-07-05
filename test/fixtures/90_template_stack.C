#include <stdio.h>
template<class T>
class Stack {
    T data_[16];
    int n_;
public:
    Stack() { n_ = 0; }
    void push(T v) { if (n_ < 16) data_[n_++] = v; }
    T top() { return data_[n_ - 1]; }
    int size() { return n_; }
};
main() {
    Stack<int> s;
    s.push(10); s.push(20); s.push(30);
    printf("size=%d top=%d\n", s.size(), s.top());
    return 0;
}
