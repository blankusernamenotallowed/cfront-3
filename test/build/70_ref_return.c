
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 70_ref_return.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__70_ref_return_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

int arr [3]= { 1 , 2 , 3 } ;
int *at__Fi (int __1i ){ return (& (arr [__1i ]));

}

extern int printf (const char *,...);

int main (void ){ _main(); { ((*at__Fi ( 1 ) ))= 99 ;

printf ( (const char *)"%d\n", arr [1 ]) ;

return 0 ;

}
} 

/* the end */
