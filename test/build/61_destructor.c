
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 61_destructor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__61_destructor_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Noisy;

struct Noisy {	/* sizeof Noisy == 4 */

int id__5Noisy ;
};

extern int printf (const char *,...);

extern void *__nw__FUl (unsigned long );

extern void __dl__FPv (void *);


int main (void ){ _main(); { { struct Noisy __2a ;

struct Noisy __2b ;

( (( ((& __2a )-> id__5Noisy = 1 ), printf ( (const char *)"ctor %d\n",
(& __2a )-> id__5Noisy ) ) ), (& __2a )) ;

( (( ((& __2b )-> id__5Noisy = 2 ), printf ( (const char *)"ctor %d\n",
(& __2b )-> id__5Noisy ) ) ), (& __2b )) ;

( (((void )( printf ( (const char *)"dtor %d\n", (& __2b )-> id__5Noisy )
, (((void )(((void )0 ))))) ))) ;

( (((void )( printf ( (const char *)"dtor %d\n", (& __2a )-> id__5Noisy )
, (((void )(((void )0 ))))) ))) ;

}

printf ( (const char *)"done\n") ;

return 0 ;

}
} 

/* the end */
