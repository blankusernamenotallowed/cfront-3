
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 60_copy_ctor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__60_copy_ctor_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct C;

struct C {	/* sizeof C == 4 */

int v__1C ;
};

extern void *__nw__FUl (unsigned long );


extern int printf (const char *,...);

int main (void ){ _main(); { struct C __1a ;

struct C __1b ;

( (( ((& __1a )-> v__1C = 5 ), 0 ) ), (& __1a )) ;

( (( ((& __1b )-> v__1C = (((*((const struct C *)(& __1a )))). v__1C + 100 )), 0 ) ), (&
__1b )) ;

printf ( (const char *)"%d\n", __1b . v__1C ) ;

return 0 ;

}
} 

/* the end */
