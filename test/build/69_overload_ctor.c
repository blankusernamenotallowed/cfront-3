
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 69_overload_ctor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__69_overload_ctor_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct P;

struct P {	/* sizeof P == 8 */

int x__1P ;

int y__1P ;
};

extern void *__nw__FUl (unsigned long );


extern int printf (const char *,...);

int main (void ){ _main(); { struct P __1p1 ;

struct P __1p2 ;

struct P __1p3 ;

( (( ((& __1p1 )-> x__1P = 0 ), ((& __1p1 )-> y__1P = 0 )) ), (& __1p1 )) ;
( (( ((& __1p2 )-> x__1P = 5 ), ((& __1p2 )-> y__1P = 0 )) ), (& __1p2 )) ;
( (( ((& __1p3 )-> x__1P = 3 ), ((& __1p3 )-> y__1P = 4 )) ), (& __1p3 )) ;
printf ( (const char *)"%d %d %d %d %d %d\n", __1p1 . x__1P , __1p1 . y__1P , __1p2 . x__1P ,
__1p2 . y__1P , __1p3 . x__1P , __1p3 . y__1P ) ;

return 0 ;

}
} 

/* the end */
