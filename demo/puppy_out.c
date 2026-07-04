#line 1 "demo/puppy.C"

/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < demo/puppy.C > */

#line 1 "demo/puppy.C"
void *__vec_new (void *, int , int , void *);

#line 1 "demo/puppy.C"
void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

#line 1 "demo/puppy.C"
extern struct __mptr* __ptbl_vec__demo_puppy_C_[];

#line 1 "demo/puppy.C"
struct Animal;

#line 2 "demo/puppy.C"
struct Animal {	/* sizeof Animal == 16 */

#line 4 "demo/puppy.C"
int legs__6Animal ;

#line 7 "demo/puppy.C"
struct __mptr *__vptr__6Animal ;
};

#line 1 "demo/puppy.C"
extern void *__nw__FUl (unsigned long );
struct Dog;

#line 7 "demo/puppy.C"

#line 9 "demo/puppy.C"
struct Dog {	/* sizeof Dog == 24 */

#line 4 "demo/puppy.C"
int legs__6Animal ;

#line 7 "demo/puppy.C"
struct __mptr *__vptr__6Animal ;

#line 10 "demo/puppy.C"
int tail_length__3Dog ;
};
struct Puppy;

#line 13 "demo/puppy.C"

#line 15 "demo/puppy.C"
struct Puppy {	/* sizeof Puppy == 32 */

#line 4 "demo/puppy.C"
int legs__6Animal ;

#line 7 "demo/puppy.C"
struct __mptr *__vptr__6Animal ;

#line 10 "demo/puppy.C"
int tail_length__3Dog ;
char __W6[4];

#line 16 "demo/puppy.C"
int cuteness__5Puppy ;
};

#line 19 "demo/puppy.C"

#line 6 "demo/puppy.C"
static int sound__6AnimalFv (struct Animal *__0this );

#line 21 "demo/puppy.C"
int main (void ){ _main(); 
#line 22 "demo/puppy.C"
{ 
#line 23 "demo/puppy.C"
struct Puppy *__1p ;
struct Animal *__1a ;

#line 25 "demo/puppy.C"
struct Puppy *__0__X7 ;

#line 25 "demo/puppy.C"
struct Dog *__0__X5 ;

#line 25 "demo/puppy.C"
struct Animal *__0__X3 ;

#line 23 "demo/puppy.C"
__1p = ( (__0__X7 = 0 ), ( ((__0__X7 || (__0__X7 = (struct Puppy *)__nw__FUl ( (unsigned long )(sizeof (struct Puppy))) ))?(
#line 23 "demo/puppy.C"
(__0__X7 = (struct Puppy *)( (__0__X5 = (((struct Dog *)__0__X7 ))), ( ((__0__X5 || (__0__X5 = (struct Dog *)__nw__FUl ( (unsigned long )(sizeof
#line 23 "demo/puppy.C"
(struct Dog))) ))?( (__0__X5 = (struct Dog *)( (__0__X3 = (((struct Animal *)__0__X5 ))), ( ((__0__X3 || (__0__X3 = (struct Animal *)__nw__FUl ( (unsigned
#line 23 "demo/puppy.C"
long )(sizeof (struct Animal))) ))?(__0__X3 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_puppy_C_[0]):0 ), __0__X3 ) ) ), (__0__X5 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_puppy_C_[1]))
#line 23 "demo/puppy.C"
:0 ), __0__X5 ) ) ), (__0__X7 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_puppy_C_[2])) :0 ), __0__X7 ) ) ;
__1a = (struct Animal *)__1p ;
return ((*(((int (*)(struct Animal *__0this ))(__1a -> __vptr__6Animal [1]).f))))( ((struct Animal *)((((char *)__1a ))+ (__1a -> __vptr__6Animal [1]).d))) ;
}
} static int sound__5PuppyFv (
#line 18 "demo/puppy.C"
struct Puppy *__0this );
struct __mptr __vtbl__5Puppy__demo_puppy_C[] = {0,0,0,
0,0,(__vptp)sound__5PuppyFv ,
0,0,0};
static int sound__3DogFv (
#line 12 "demo/puppy.C"
struct Dog *__0this );
struct __mptr __vtbl__3Dog__demo_puppy_C[] = {0,0,0,
0,0,(__vptp)sound__3DogFv ,
0,0,0};
struct __mptr __vtbl__6Animal__demo_puppy_C[] = {0,0,0,
0,0,(__vptp)sound__6AnimalFv ,
0,0,0};

#line 18 "demo/puppy.C"
static int sound__5PuppyFv (struct Puppy *__0this ){ return 2 ;

#line 18 "demo/puppy.C"
}

#line 12 "demo/puppy.C"
static int sound__3DogFv (struct Dog *__0this ){ return 1 ;

#line 12 "demo/puppy.C"
}

#line 6 "demo/puppy.C"
static int sound__6AnimalFv (struct Animal *__0this ){ return 0 ;

#line 6 "demo/puppy.C"
}
struct __mptr* __ptbl_vec__demo_puppy_C_[] = {
__vtbl__6Animal__demo_puppy_C,
__vtbl__3Dog__demo_puppy_C,
__vtbl__5Puppy__demo_puppy_C,

};

#line 26 "demo/puppy.C"

/* the end */
