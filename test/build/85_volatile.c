
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 85_volatile.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__85_volatile_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

extern int printf (const char *,...);

int main (void ){ _main(); { int __1x ;

__1x = 5 ;

__1x = (__1x + 1 );

printf ( (const char *)"%d\n", __1x ) ;

return 0 ;

}
} 

/* the end */
