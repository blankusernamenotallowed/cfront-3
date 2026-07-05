
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 63_multi_inherit.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__63_multi_inherit_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct A;
struct B;
struct C;

struct A {	/* sizeof A == 1 */

char __W1__1A ;
};

struct B {	/* sizeof B == 1 */

char __W2__1B ;
};

struct C {	/* sizeof C == 2 */

char __W1__1A ;
struct B OB;
};




extern int printf (const char *,...);

int main (void ){ _main(); { struct C __1obj ;

printf ( (const char *)"%d %d %d\n", ( 1 ) , ( 2 ) ,
( 3 ) ) ;

return 0 ;

}
} 

/* the end */
