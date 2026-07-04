
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < /c/Users/Diana/pg/cfront-3/demo/shapes.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec___c_Users_Diana_pg_cfront_3_demo_shapes_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Shape;

struct Shape {	/* sizeof Shape == 8 */

struct __mptr *__vptr__5Shape ;
};

static const char *name__5ShapeFv (struct Shape *__0this );

static double area__5ShapeFv (struct Shape *__0this );

extern int printf (const char *,...);

extern void *__nw__FUl (unsigned long );
struct Circle;


struct Circle {	/* sizeof Circle == 16 */

struct __mptr *__vptr__5Shape ;

double r__6Circle ;
};
struct Square;


struct Square {	/* sizeof Square == 16 */

struct __mptr *__vptr__5Shape ;

double s__6Square ;
};




int main (void ){ _main(); 
{ 
struct Shape *__1shapes [2];

struct Circle *__0__X6 ;

struct Shape *__0__X3 ;

struct Square *__0__X7 ;

struct Shape *__0__X5 ;

(__1shapes [0 ])= (struct Shape *)( (__0__X6 = 0 ), ( ((__0__X6 || (__0__X6 = (struct Circle *)__nw__FUl ( (unsigned long )(sizeof (struct Circle)))
))?( ( (__0__X6 = (struct Circle *)( (__0__X3 = (((struct Shape *)__0__X6 ))), ( ((__0__X3 || (__0__X3 = (struct Shape *)__nw__FUl ( (unsigned
long )(sizeof (struct Shape))) ))?(__0__X3 -> __vptr__5Shape = (struct __mptr *) __ptbl_vec___c_Users_Diana_pg_cfront_3_demo_shapes_C_[0]):0 ), __0__X3 ) ) ), (__0__X6 -> __vptr__5Shape = (struct __mptr *) __ptbl_vec___c_Users_Diana_pg_cfront_3_demo_shapes_C_[1]))
, (__0__X6 -> r__6Circle = 2.0 )) :0 ), __0__X6 ) ) ;
(__1shapes [1 ])= (struct Shape *)( (__0__X7 = 0 ), ( ((__0__X7 || (__0__X7 = (struct Square *)__nw__FUl ( (unsigned long )(sizeof (struct Square)))
))?( ( (__0__X7 = (struct Square *)( (__0__X5 = (((struct Shape *)__0__X7 ))), ( ((__0__X5 || (__0__X5 = (struct Shape *)__nw__FUl ( (unsigned
long )(sizeof (struct Shape))) ))?(__0__X5 -> __vptr__5Shape = (struct __mptr *) __ptbl_vec___c_Users_Diana_pg_cfront_3_demo_shapes_C_[0]):0 ), __0__X5 ) ) ), (__0__X7 -> __vptr__5Shape = (struct __mptr *) __ptbl_vec___c_Users_Diana_pg_cfront_3_demo_shapes_C_[2]))
, (__0__X7 -> s__6Square = 3.0 )) :0 ), __0__X7 ) ) ;
{ { int __1i ;

__1i = 0 ;

for(;__1i < 2 ;__1i ++ ) 
( printf ( (const char *)"%-8s area = %g\n", ((*(((const char
*(*)(struct Shape *__0this ))((__1shapes [__1i ])-> __vptr__5Shape [2]).f))))( ((struct Shape *)((((char *)(__1shapes [__1i ])))+ ((__1shapes [__1i ])-> __vptr__5Shape [2]).d))) , ((*(((double (*)(struct Shape *__0this ))((__1shapes [__1i ])-> __vptr__5Shape [1]).f))))( ((struct
Shape *)((((char *)(__1shapes [__1i ])))+ ((__1shapes [__1i ])-> __vptr__5Shape [1]).d))) ) , (((void )0 ))) ;
return 0 ;

}

}
}
} static double area__6SquareFv (
struct Square *__0this );
static const char *name__6SquareFv (struct Square *__0this );
struct __mptr __vtbl__6Square___c_Users_Diana_pg_cfront_3_demo_shapes_C[] = {0,0,0,
0,0,(__vptp)area__6SquareFv ,
0,0,(__vptp)name__6SquareFv ,
0,0,0};
static double area__6CircleFv (
struct Circle *__0this );
static const char *name__6CircleFv (struct Circle *__0this );
struct __mptr __vtbl__6Circle___c_Users_Diana_pg_cfront_3_demo_shapes_C[] = {0,0,0,
0,0,(__vptp)area__6CircleFv ,
0,0,(__vptp)name__6CircleFv ,
0,0,0};
struct __mptr __vtbl__5Shape___c_Users_Diana_pg_cfront_3_demo_shapes_C[] = {0,0,0,
0,0,(__vptp)area__5ShapeFv ,
0,0,(__vptp)name__5ShapeFv ,
0,0,0};

static const char *name__6SquareFv (struct Square *__0this ){ return (const char *)"square";

}

static double area__6SquareFv (struct Square *__0this ){ return (__0this -> s__6Square * __0this -> s__6Square );

}

static const char *name__6CircleFv (struct Circle *__0this ){ return (const char *)"circle";

}

static double area__6CircleFv (struct Circle *__0this ){ return ((3.14159 * __0this -> r__6Circle )* __0this -> r__6Circle );

}

static const char *name__5ShapeFv (struct Shape *__0this ){ return (const char *)"shape";

}

static double area__5ShapeFv (struct Shape *__0this ){ return (double )0 ;

}
struct __mptr* __ptbl_vec___c_Users_Diana_pg_cfront_3_demo_shapes_C_[] = {
__vtbl__5Shape___c_Users_Diana_pg_cfront_3_demo_shapes_C,
__vtbl__6Circle___c_Users_Diana_pg_cfront_3_demo_shapes_C,
__vtbl__6Square___c_Users_Diana_pg_cfront_3_demo_shapes_C,

};


/* the end */
