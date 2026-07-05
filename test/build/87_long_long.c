
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 87_long_long.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__87_long_long_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

extern int printf (const char *,...);

int main (void ){ _main(); { long long __1big ;

__1big = 10000000000LL ;

printf ( (const char *)"%lld\n", __1big ) ;

return 0 ;

}
} 

/* the end */
