
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 64_mi_virtual.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__64_mi_virtual_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct A;

struct A {	/* sizeof A == 8 */

struct __mptr *__vptr__1A ;
};

extern void *__nw__FUl (unsigned long );
struct B;

struct B {	/* sizeof B == 8 */

struct __mptr *__vptr__1B ;
};
struct C;



struct C {	/* sizeof C == 16 */

struct __mptr *__vptr__1A ;
struct B OB;
};


static int who__1AFv (struct A *__0this );
static int what__1BFv (struct B *__0this );

extern int printf (const char *,...);

int main (void ){ _main(); { struct C __1obj ;

struct A *__1pa ;

struct B *__1pb ;

struct A *__0__X4 ;

( (( ( ( ( (__0__X4 = (((struct A *)(& __1obj )))), ( ((__0__X4 || (__0__X4 = (struct A *)__nw__FUl (
(unsigned long )(sizeof (struct A))) ))?(__0__X4 -> __vptr__1A = (struct __mptr *) __ptbl_vec__64_mi_virtual_C_[0]):0 ), __0__X4 ) ) , ( (((((struct B *)((((char
*)(& __1obj )))+ 8)))|| (__nw__FUl ( (unsigned long )(sizeof (struct B))) ))?((((struct B *)((((char *)(& __1obj )))+ 8)))-> __vptr__1B =
(struct __mptr *) __ptbl_vec__64_mi_virtual_C_[1]):0 ), (((struct B *)((((char *)(& __1obj )))+ 8)))) ) , ((& __1obj )-> __vptr__1A = (struct __mptr *) __ptbl_vec__64_mi_virtual_C_[2]))
, ((& __1obj )-> OB. __vptr__1B =  __ptbl_vec__64_mi_virtual_C_[3])) ), (& __1obj )) ;

__1pa = (struct A *)(& __1obj );

__1pb = (((struct B *)(((struct C *)((((char *)(& __1obj )))+ 8)))));

printf ( (const char *)"%d %d\n", ((*(((int (*)(struct A *__0this ))(__1pa -> __vptr__1A [1]).f))))( ((struct A *)((((char
*)__1pa ))+ (__1pa -> __vptr__1A [1]).d))) , ((*(((int (*)(struct B *__0this ))(__1pb -> __vptr__1B [1]).f))))( ((struct B *)((((char *)__1pb ))+ (__1pb -> __vptr__1B [1]).d))) )
;

return 0 ;

}
} static int what__1CFv (
struct C *__0this );
struct __mptr __vtbl__1B__1C__64_mi_virtual_C[] = {0,0,0,
-8,0,(__vptp)what__1CFv ,
0,0,0};
static int who__1CFv (
struct C *__0this );
struct __mptr __vtbl__1C__64_mi_virtual_C[] = {0,0,0,
0,0,(__vptp)who__1CFv ,
0,0,(__vptp)what__1CFv ,
0,0,0};
struct __mptr __vtbl__1B__64_mi_virtual_C[] = {0,0,0,
0,0,(__vptp)what__1BFv ,
0,0,0};
struct __mptr __vtbl__1A__64_mi_virtual_C[] = {0,0,0,
0,0,(__vptp)who__1AFv ,
0,0,0};

static int what__1CFv (struct C *__0this ){ return 20 ;

}

static int who__1CFv (struct C *__0this ){ return 10 ;

}

static int what__1BFv (struct B *__0this ){ return 2 ;

}

static int who__1AFv (struct A *__0this ){ return 1 ;

}
struct __mptr* __ptbl_vec__64_mi_virtual_C_[] = {
__vtbl__1A__64_mi_virtual_C,
__vtbl__1B__64_mi_virtual_C,
__vtbl__1C__64_mi_virtual_C,
__vtbl__1B__1C__64_mi_virtual_C,

};


/* the end */
