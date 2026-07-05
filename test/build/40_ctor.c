
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 40_ctor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__40_ctor_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Counter;

struct Counter {	/* sizeof Counter == 4 */
int n__7Counter ;
};

extern void *__nw__FUl (unsigned long );




extern int printf (const char *,...);

int main (void ){ _main(); { 
struct Counter __1c ;

( (( ((& __1c )-> n__7Counter = 0 ), 0 ) ), (& __1c )) ;
( ((& __1c )-> n__7Counter += 3 ), (((void )0 ))) ;

( ((& __1c )-> n__7Counter += 4 ), (((void )0 ))) ;
printf ( (const char *)"count=%d\n", ( (& __1c )-> n__7Counter ) ) ;

return 0 ;
}
} 

/* the end */
