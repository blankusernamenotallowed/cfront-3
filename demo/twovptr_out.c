#line 1 "demo/twovptr.C"

/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < demo/twovptr.C > */

#line 1 "demo/twovptr.C"
void *__vec_new (void *, int , int , void *);

#line 1 "demo/twovptr.C"
void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

#line 1 "demo/twovptr.C"
extern struct __mptr* __ptbl_vec__demo_twovptr_C_[];

#line 1 "demo/twovptr.C"
struct Base1;

#line 2 "demo/twovptr.C"
struct Base1 {	/* sizeof Base1 == 16 */
int a__5Base1 ;

#line 6 "demo/twovptr.C"
struct __mptr *__vptr__5Base1 ;
};

#line 1 "demo/twovptr.C"
extern void *__nw__FUl (unsigned long );
struct Base2;

#line 8 "demo/twovptr.C"
struct Base2 {	/* sizeof Base2 == 16 */
int b__5Base2 ;

#line 12 "demo/twovptr.C"
struct __mptr *__vptr__5Base2 ;
};
struct Derived;

#line 6 "demo/twovptr.C"

#line 12 "demo/twovptr.C"

#line 14 "demo/twovptr.C"
struct Derived {	/* sizeof Derived == 40 */

#line 3 "demo/twovptr.C"
int a__5Base1 ;

#line 6 "demo/twovptr.C"
struct __mptr *__vptr__5Base1 ;
struct Base2 OBase2;

#line 15 "demo/twovptr.C"
int c__7Derived ;
};

#line 19 "demo/twovptr.C"

#line 5 "demo/twovptr.C"
static int f1__5Base1Fv (struct Base1 *__0this );

#line 11 "demo/twovptr.C"
static int f2__5Base2Fv (struct Base2 *__0this );

#line 21 "demo/twovptr.C"
int main (void ){ _main(); 
#line 22 "demo/twovptr.C"
{ 
#line 23 "demo/twovptr.C"
struct Derived *__1d ;
struct Base1 *__1p1 ;
struct Base2 *__1p2 ;

#line 26 "demo/twovptr.C"
struct Derived *__0__X5 ;

#line 26 "demo/twovptr.C"
struct Base1 *__0__X4 ;

#line 23 "demo/twovptr.C"
__1d = ( (__0__X5 = 0 ), ( ((__0__X5 || (__0__X5 = (struct Derived *)__nw__FUl ( (unsigned long )(sizeof (struct Derived))) ))?(
#line 23 "demo/twovptr.C"
( ( ( (__0__X4 = (((struct Base1 *)__0__X5 ))), ( ((__0__X4 || (__0__X4 = (struct Base1 *)__nw__FUl ( (unsigned long )(sizeof
#line 23 "demo/twovptr.C"
(struct Base1))) ))?(__0__X4 -> __vptr__5Base1 = (struct __mptr *) __ptbl_vec__demo_twovptr_C_[0]):0 ), __0__X4 ) ) , ( (((((struct Base2 *)((((char *)__0__X5 ))+ 16)))|| (__nw__FUl (
#line 23 "demo/twovptr.C"
(unsigned long )(sizeof (struct Base2))) ))?((((struct Base2 *)((((char *)__0__X5 ))+ 16)))-> __vptr__5Base2 = (struct __mptr *) __ptbl_vec__demo_twovptr_C_[1]):0 ), (((struct Base2 *)((((char *)__0__X5 ))+
#line 23 "demo/twovptr.C"
16)))) ) , (__0__X5 -> __vptr__5Base1 = (struct __mptr *) __ptbl_vec__demo_twovptr_C_[2])) , (__0__X5 -> OBase2. __vptr__5Base2 =  __ptbl_vec__demo_twovptr_C_[3])) :0 ), __0__X5 )
#line 23 "demo/twovptr.C"
) ;
__1p1 = (struct Base1 *)__1d ;
__1p2 = (((struct Base2 *)(__1d ?(((struct Derived *)((((char *)__1d ))+ 16))):0 )));
return (((*(((int (*)(struct Base1 *__0this ))(__1p1 -> __vptr__5Base1 [1]).f))))( ((struct Base1 *)((((char *)__1p1 ))+ (__1p1 -> __vptr__5Base1 [1]).d))) + ((*(((int (*)(struct Base2 *__0this ))(__1p2 ->
#line 26 "demo/twovptr.C"
__vptr__5Base2 [1]).f))))( ((struct Base2 *)((((char *)__1p2 ))+ (__1p2 -> __vptr__5Base2 [1]).d))) );
}
} static int f2__7DerivedFv (
#line 18 "demo/twovptr.C"
struct Derived *__0this );
struct __mptr __vtbl__5Base2__7Derived__demo_twovptr_C[] = {0,0,0,
-16,0,(__vptp)f2__7DerivedFv ,
0,0,0};
static int f1__7DerivedFv (
#line 17 "demo/twovptr.C"
struct Derived *__0this );
struct __mptr __vtbl__7Derived__demo_twovptr_C[] = {0,0,0,
0,0,(__vptp)f1__7DerivedFv ,
0,0,(__vptp)f2__7DerivedFv ,
0,0,0};
struct __mptr __vtbl__5Base2__demo_twovptr_C[] = {0,0,0,
0,0,(__vptp)f2__5Base2Fv ,
0,0,0};
struct __mptr __vtbl__5Base1__demo_twovptr_C[] = {0,0,0,
0,0,(__vptp)f1__5Base1Fv ,
0,0,0};
static int f2__7DerivedFv (struct Derived *__0this ){ return 20 ;

#line 18 "demo/twovptr.C"
}

#line 17 "demo/twovptr.C"
static int f1__7DerivedFv (struct Derived *__0this ){ return 10 ;

#line 17 "demo/twovptr.C"
}

#line 11 "demo/twovptr.C"
static int f2__5Base2Fv (struct Base2 *__0this ){ return 2 ;

#line 11 "demo/twovptr.C"
}

#line 5 "demo/twovptr.C"
static int f1__5Base1Fv (struct Base1 *__0this ){ return 1 ;

#line 5 "demo/twovptr.C"
}
struct __mptr* __ptbl_vec__demo_twovptr_C_[] = {
__vtbl__5Base1__demo_twovptr_C,
__vtbl__5Base2__demo_twovptr_C,
__vtbl__7Derived__demo_twovptr_C,
__vtbl__5Base2__7Derived__demo_twovptr_C,

};

#line 27 "demo/twovptr.C"

/* the end */
