
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 68_static_local.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__68_static_local_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

int counter__Fv (void ){ static int __1n = 0 ;

return (++ __1n );

}

extern int printf (const char *,...);

int main (void ){ _main(); { int __1a ;

int __1b ;

int __1c ;

__1a = counter__Fv ( ) ;

__1b = counter__Fv ( ) ;

__1c = counter__Fv ( ) ;

printf ( (const char *)"%d %d %d\n", __1a , __1b , __1c ) ;

return 0 ;

}
} 

/* the end */
