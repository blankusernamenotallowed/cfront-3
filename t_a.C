typedef long unsigned int size_t;
class RECORD {
 inline void* operator new(size_t);
 inline void operator delete(void* p, size_t s);
 unsigned long key;
};
