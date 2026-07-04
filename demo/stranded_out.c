#line 1 "demo/stranded.C"

/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < demo/stranded.C > */

#line 1 "demo/stranded.C"
void *__vec_new (void *, int , int , void *);

#line 1 "demo/stranded.C"
void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

#line 1 "demo/stranded.C"
extern struct __mptr* __ptbl_vec__demo_stranded_C_[];

#line 1 "demo/stranded.C"
struct Animal;

#line 3 "demo/stranded.C"
struct Animal {	/* sizeof Animal == 16 */

#line 5 "demo/stranded.C"
int legs__6Animal ;

#line 8 "demo/stranded.C"
struct __mptr *__vptr__6Animal ;
};

#line 1 "demo/stranded.C"
extern void *__nw__FUl (unsigned long );
struct Dog;

#line 8 "demo/stranded.C"

#line 10 "demo/stranded.C"
struct Dog {	/* sizeof Dog == 24 */

#line 5 "demo/stranded.C"
int legs__6Animal ;

#line 8 "demo/stranded.C"
struct __mptr *__vptr__6Animal ;

#line 11 "demo/stranded.C"
int tail_length__3Dog ;
};

#line 14 "demo/stranded.C"

#line 7 "demo/stranded.C"
static int sound__6AnimalFv (struct Animal *__0this );

#line 16 "demo/stranded.C"
int main (void ){ _main(); 
#line 17 "demo/stranded.C"
{ 
#line 18 "demo/stranded.C"
struct Dog *__1d ;
struct Animal *__1a ;

#line 20 "demo/stranded.C"
struct Dog *__0__X4 ;

#line 20 "demo/stranded.C"
struct Animal *__0__X3 ;

#line 18 "demo/stranded.C"
__1d = ( (__0__X4 = 0 ), ( ((__0__X4 || (__0__X4 = (struct Dog *)__nw__FUl ( (unsigned long )(sizeof (struct Dog))) ))?(
#line 18 "demo/stranded.C"
(__0__X4 = (struct Dog *)( (__0__X3 = (((struct Animal *)__0__X4 ))), ( ((__0__X3 || (__0__X3 = (struct Animal *)__nw__FUl ( (unsigned long )(sizeof
#line 18 "demo/stranded.C"
(struct Animal))) ))?(__0__X3 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_stranded_C_[0]):0 ), __0__X3 ) ) ), (__0__X4 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_stranded_C_[1])) :0 ), __0__X4 )
#line 18 "demo/stranded.C"
) ;
__1a = (struct Animal *)__1d ;
return ((*(((int (*)(struct Animal *__0this ))(__1a -> __vptr__6Animal [1]).f))))( ((struct Animal *)((((char *)__1a ))+ (__1a -> __vptr__6Animal [1]).d))) ;
}
} static int sound__3DogFv (
#line 13 "demo/stranded.C"
struct Dog *__0this );
struct __mptr __vtbl__3Dog__demo_stranded_C[] = {0,0,0,
0,0,(__vptp)sound__3DogFv ,
0,0,0};
struct __mptr __vtbl__6Animal__demo_stranded_C[] = {0,0,0,
0,0,(__vptp)sound__6AnimalFv ,
0,0,0};

#line 13 "demo/stranded.C"
static int sound__3DogFv (struct Dog *__0this ){ return 1 ;

#line 13 "demo/stranded.C"
}

#line 7 "demo/stranded.C"
static int sound__6AnimalFv (struct Animal *__0this ){ return 0 ;

#line 7 "demo/stranded.C"
}
struct __mptr* __ptbl_vec__demo_stranded_C_[] = {
__vtbl__6Animal__demo_stranded_C,
__vtbl__3Dog__demo_stranded_C,

};

#line 21 "demo/stranded.C"

/* the end */
