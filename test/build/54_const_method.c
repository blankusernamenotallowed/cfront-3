
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 54_const_method.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__54_const_method_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct C;

struct C {	/* sizeof C == 4 */

int x__1C ;
};

extern void *__nw__FUl (unsigned long );


extern int printf (const char *,...);

int main (void ){ _main(); { struct C __1c ;

( (( ((& __1c )-> x__1C = 9 ), 0 ) ), (& __1c )) ;

printf ( (const char *)"%d\n", ( ((const struct C *)(& __1c ))-> x__1C )
) ;

return 0 ;

}
} 

/* the end */
