
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 20_overload.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__20_overload_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

int maxv__FiT1 (int __1a , int __1b ){ return ((__1a > __1b )?__1a :__1b );

}
double maxv__FdT1 (double __1a , double __1b ){ return ((__1a > __1b )?__1a :__1b );

}
void bump__FRii (int *__1x , int __1by ){ ((*__1x ))+= __1by ;

}

extern int printf (const char *,...);

int main (void ){ _main(); { 
int __1n ;

__1n = 5 ;
bump__FRii ( (int *)(& __1n ), 1 ) ;

bump__FRii ( (int *)(& __1n ), 10 ) ;
printf ( (const char *)"n=%d max=%d %g\n", __1n , maxv__FiT1 ( 3 , 7 ) , maxv__FdT1 (
2.5 , 1.5 ) ) ;
return 0 ;
}
} 

/* the end */
