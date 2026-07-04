
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < demo/zoo.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__demo_zoo_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Animal;

struct Animal {	/* sizeof Animal == 16 */

int legs__6Animal ;

struct __mptr *__vptr__6Animal ;
};

extern void *__nw__FUl (unsigned long );

extern void __dl__FPv (void *);

static const char *kind__6AnimalFv (struct Animal *__0this );

static const char *sound__6AnimalFv (struct Animal *__0this );

extern int printf (const char *,...);
struct Dog;


struct Dog {	/* sizeof Dog == 16 */

int legs__6Animal ;

struct __mptr *__vptr__6Animal ;
};

static void __dt__6AnimalFv (struct Animal *__0this , int __0__free );
struct Bird;


struct Bird {	/* sizeof Bird == 16 */

int legs__6Animal ;

struct __mptr *__vptr__6Animal ;
};
struct Vec2;

struct Vec2 {	/* sizeof Vec2 == 16 */

double x__4Vec2 ;

double y__4Vec2 ;
};








int main (void ){ _main(); 
{ 
struct Animal *__1zoo [2];

struct Dog *__0__X9 ;

struct Animal *__0__X3 ;

struct Bird *__0__X10 ;

struct Animal *__0__X5 ;

(__1zoo [0 ])= (struct Animal *)( (__0__X9 = 0 ), ( ((__0__X9 || (__0__X9 = (struct Dog *)__nw__FUl ( (unsigned long )(sizeof (struct Dog)))
))?( (__0__X9 = (struct Dog *)( (__0__X3 = (((struct Animal *)__0__X9 ))), ( ((__0__X3 || (__0__X3 = (struct Animal *)__nw__FUl ( (unsigned long
)(sizeof (struct Animal))) ))?( (__0__X3 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[0]), (__0__X3 -> legs__6Animal = 4 )) :0 ), __0__X3 ) ) ),
(__0__X9 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[1])) :0 ), __0__X9 ) ) ;
(__1zoo [1 ])= (struct Animal *)( (__0__X10 = 0 ), ( ((__0__X10 || (__0__X10 = (struct Bird *)__nw__FUl ( (unsigned long )(sizeof (struct Bird)))
))?( (__0__X10 = (struct Bird *)( (__0__X5 = (((struct Animal *)__0__X10 ))), ( ((__0__X5 || (__0__X5 = (struct Animal *)__nw__FUl ( (unsigned long
)(sizeof (struct Animal))) ))?( (__0__X5 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[0]), (__0__X5 -> legs__6Animal = 2 )) :0 ), __0__X5 ) ) ),
(__0__X10 -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[2])) :0 ), __0__X10 ) ) ;
{ { int __1i ;

__1i = 0 ;

for(;__1i < 2 ;__1i ++ ) 
( printf ( (const char *)"A %-4s has %d legs and says '%s'\n", ((*(((const char
*(*)(struct Animal *__0this ))((__1zoo [__1i ])-> __vptr__6Animal [3]).f))))( ((struct Animal *)((((char *)(__1zoo [__1i ])))+ ((__1zoo [__1i ])-> __vptr__6Animal [3]).d))) , (__1zoo [__1i ])-> legs__6Animal , ((*(((const char *(*)(struct
Animal *__0this ))((__1zoo [__1i ])-> __vptr__6Animal [2]).f))))( ((struct Animal *)((((char *)(__1zoo [__1i ])))+ ((__1zoo [__1i ])-> __vptr__6Animal [2]).d))) ) , (((void )0 ))) ;

{ struct Vec2 __1a ;

struct Vec2 __1b ;
struct Vec2 __1c ;

struct Vec2 __2__X11 ;

double __2__X7 ;

double __2__X8 ;

struct Vec2 __0__X__V600qowqaaibnh ;

( (( ((& __1a )-> x__4Vec2 = ((double )1 )), ((& __1a )-> y__4Vec2 = ((double )2 ))) ), (&
__1a )) ;

( (( ((& __1b )-> x__4Vec2 = ((double )3 )), ((& __1b )-> y__4Vec2 = ((double )4 ))) ), (&
__1b )) ;
__1c = ( (__2__X11 = __1b ), ( ( ( (__2__X7 = ((& __1a )-> x__4Vec2 + __2__X11 . x__4Vec2 )), (
(__2__X8 = ((& __1a )-> y__4Vec2 + __2__X11 . y__4Vec2 )), ( (( ((& __0__X__V600qowqaaibnh )-> x__4Vec2 = __2__X7 ), ((& __0__X__V600qowqaaibnh )->
y__4Vec2 = __2__X8 )) ), (& __0__X__V600qowqaaibnh )) ) ) , __0__X__V600qowqaaibnh ) ) ) ;
printf ( (const char *)"a+b = (%g, %g)   a.b = %g\n", __1c . x__4Vec2 , __1c . y__4Vec2 , ( (((&
__1a )-> x__4Vec2 * ((*((struct Vec2 *)(& __1b )))). x__4Vec2 )+ ((& __1a )-> y__4Vec2 * ((*((struct Vec2 *)(& __1b )))). y__4Vec2 ))) )
;
return 0 ;

}

}

}
}
} static void __dt__4BirdFv (
struct Bird *__0this , 
int __0__free );
static const char *sound__4BirdFv (
struct Bird *__0this );
static const char *kind__4BirdFv (struct Bird *__0this );
struct __mptr __vtbl__4Bird__demo_zoo_C[] = {0,0,0,
0,0,(__vptp)__dt__4BirdFv ,
0,0,(__vptp)sound__4BirdFv ,
0,0,(__vptp)kind__4BirdFv ,
0,0,0};
static void __dt__3DogFv (
struct Dog *__0this , 
int __0__free );
static const char *sound__3DogFv (
struct Dog *__0this );
static const char *kind__3DogFv (struct Dog *__0this );
struct __mptr __vtbl__3Dog__demo_zoo_C[] = {0,0,0,
0,0,(__vptp)__dt__3DogFv ,
0,0,(__vptp)sound__3DogFv ,
0,0,(__vptp)kind__3DogFv ,
0,0,0};
struct __mptr __vtbl__6Animal__demo_zoo_C[] = {0,0,0,
0,0,(__vptp)__dt__6AnimalFv ,
0,0,(__vptp)sound__6AnimalFv ,
0,0,(__vptp)kind__6AnimalFv ,
0,0,0};

static void __dt__4BirdFv (struct Bird *__0this , 
int __0__free ){ 
if (__0this ){ __0this -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[2];

if (__0this ){ ( ((((struct Animal *)__0this ))?(((void )( ((((struct Animal *)__0this ))-> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[0]), ((((struct Animal *)__0this ))?(((void )(((void
)0 )))):(((void )0 )))) )):(((void )0 )))) ;

if (__0__free & 1)__dl__FPv ( (void *)__0this ) ;
} } 
}

static const char *kind__4BirdFv (struct Bird *__0this ){ return (const char *)"bird";
}

static const char *sound__4BirdFv (struct Bird *__0this ){ return (const char *)"tweet";

}

static void __dt__3DogFv (struct Dog *__0this , 
int __0__free ){ 
if (__0this ){ __0this -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[1];

if (__0this ){ ( ((((struct Animal *)__0this ))?(((void )( ((((struct Animal *)__0this ))-> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[0]), ((((struct Animal *)__0this ))?(((void )(((void
)0 )))):(((void )0 )))) )):(((void )0 )))) ;

if (__0__free & 1)__dl__FPv ( (void *)__0this ) ;
} } 
}

static const char *kind__3DogFv (struct Dog *__0this ){ return (const char *)"dog";
}

static const char *sound__3DogFv (struct Dog *__0this ){ return (const char *)"woof";

}

static const char *kind__6AnimalFv (struct Animal *__0this ){ return (const char *)"animal";

}

static const char *sound__6AnimalFv (struct Animal *__0this ){ return (const char *)"...";

}

static void __dt__6AnimalFv (struct Animal *__0this , 
int __0__free ){ 
if (__0this ){ 
__0this -> __vptr__6Animal = (struct __mptr *) __ptbl_vec__demo_zoo_C_[0];

if (__0this )if (__0__free & 1)__dl__FPv ( (void *)__0this ) ;
} 
}
struct __mptr* __ptbl_vec__demo_zoo_C_[] = {
__vtbl__6Animal__demo_zoo_C,
__vtbl__3Dog__demo_zoo_C,
__vtbl__4Bird__demo_zoo_C,

};


/* the end */
