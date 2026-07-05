template<class T>
class Stack {
    T data_[16];
    int n_;
public:
    Stack();
    void push(T v);
};

template<class T>
Stack<T>::Stack() {
    n_ = 0;
}

template<class T>
void Stack<T>::push(T v) {
    if (n_ < 16)
        data_[n_++] = v;
}

int main() {
    Stack<int>* s = 0;
    return 0;
}
