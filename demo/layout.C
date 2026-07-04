class B { public: int x; virtual void f(); };
class D : public B { public: int y; };   // derived ADDS data after inherited vptr
