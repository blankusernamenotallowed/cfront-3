typedef long unsigned int size_t;
class RECORD {
 void* operator new(size_t);
 void operator delete(void* p, size_t s);
 unsigned long key;
};
