
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 58_functor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__58_functor_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Adder;

struct Adder {	/* sizeof Adder == 4 */

int base__5Adder ;
};

extern void *__nw__FUl (unsigned long );


extern int printf (const char *,...);

int main (void ){ _main(); { struct Adder __1add5 ;

( (( ((& __1add5 )-> base__5Adder = 5 ), 0 ) ), (& __1add5 )) ;

printf ( (const char *)"%d\n", ( ((& __1add5 )-> base__5Adder + 3 )) )
;

return 0 ;

}
} 

/* the end */
