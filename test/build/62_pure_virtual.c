
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 62_pure_virtual.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__62_pure_virtual_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Shape;

struct Shape {	/* sizeof Shape == 8 */

struct __mptr *__vptr__5Shape ;
};

extern void *__nw__FUl (unsigned long );
struct Sq;


struct Sq {	/* sizeof Sq == 16 */

struct __mptr *__vptr__5Shape ;
int s__2Sq ;
};


int area__5ShapeFv (struct Shape *__0this );

extern int printf (const char *,...);

int main (void ){ _main(); { struct Shape *__1p ;

struct Sq *__0__X4 ;

struct Shape *__0__X3 ;

__1p = (struct Shape *)( (__0__X4 = 0 ), ( ((__0__X4 || (__0__X4 = (struct Sq *)__nw__FUl ( (unsigned long )(sizeof (struct Sq)))
))?( ( (__0__X4 = (struct Sq *)( (__0__X3 = (((struct Shape *)__0__X4 ))), ( ((__0__X3 || (__0__X3 = (struct Shape *)__nw__FUl ( (unsigned
long )(sizeof (struct Shape))) ))?(__0__X3 -> __vptr__5Shape = (struct __mptr *) __ptbl_vec__62_pure_virtual_C_[0]):0 ), __0__X3 ) ) ), (__0__X4 -> __vptr__5Shape = (struct __mptr *) __ptbl_vec__62_pure_virtual_C_[1]))
, (__0__X4 -> s__2Sq = 4 )) :0 ), __0__X4 ) ) ;

printf ( (const char *)"%d\n", ((*(((int (*)(struct Shape *__0this ))(__1p -> __vptr__5Shape [1]).f))))( ((struct Shape *)((((char
*)__1p ))+ (__1p -> __vptr__5Shape [1]).d))) ) ;

return 0 ;

}
} static int area__2SqFv (
struct Sq *__0this );
struct __mptr __vtbl__2Sq__62_pure_virtual_C[] = {0,0,0,
0,0,(__vptp)area__2SqFv ,
0,0,0};
char __pure_virtual_called();
struct __mptr __vtbl__5Shape__62_pure_virtual_C[] = {0,0,0,
0,0,(__vptp)__pure_virtual_called,
0,0,0};

static int area__2SqFv (struct Sq *__0this ){ return (__0this -> s__2Sq * __0this -> s__2Sq );

}
struct __mptr* __ptbl_vec__62_pure_virtual_C_[] = {
__vtbl__5Shape__62_pure_virtual_C,
__vtbl__2Sq__62_pure_virtual_C,

};


/* the end */
