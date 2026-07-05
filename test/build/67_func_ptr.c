
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 67_func_ptr.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__67_func_ptr_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

int add__FiT1 (int __1a , int __1b ){ return (__1a + __1b );

}
int mul__FiT1 (int __1a , int __1b ){ return (__1a * __1b );

}

extern int printf (const char *,...);

int main (void ){ _main(); { int (*__1f )(int , int );

__1f = (add__FiT1 );

printf ( (const char *)"%d ", (*(__1f ))( 3 , 4 ) ) ;

__1f = (mul__FiT1 );

printf ( (const char *)"%d\n", (*(__1f ))( 3 , 4 ) ) ;

return 0 ;

}
} 

/* the end */
