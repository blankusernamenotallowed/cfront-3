
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 72_virtual_dtor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__72_virtual_dtor_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Base;

extern int printf (const char *,...);

extern void __dl__FPv (void *);

struct Base {	/* sizeof Base == 8 */

struct __mptr *__vptr__4Base ;
};

extern void *__nw__FUl (unsigned long );
struct Der;

static void __dt__4BaseFv (struct Base *__0this , int __0__free );
struct Der {	/* sizeof Der == 8 */

struct __mptr *__vptr__4Base ;
};



int main (void ){ _main(); { struct Base *__1p ;

struct Der *__0__X4 ;

struct Base *__0__X3 ;

__1p = (struct Base *)( (__0__X4 = 0 ), ( ((__0__X4 || (__0__X4 = (struct Der *)__nw__FUl ( (unsigned long )(sizeof (struct Der)))
))?( (__0__X4 = (struct Der *)( (__0__X3 = (((struct Base *)__0__X4 ))), ( ((__0__X3 || (__0__X3 = (struct Base *)__nw__FUl ( (unsigned long
)(sizeof (struct Base))) ))?(__0__X3 -> __vptr__4Base = (struct __mptr *) __ptbl_vec__72_virtual_dtor_C_[0]):0 ), __0__X3 ) ) ), (__0__X4 -> __vptr__4Base = (struct __mptr *) __ptbl_vec__72_virtual_dtor_C_[1])) :0 ),
__0__X4 ) ) ;

__1p ?( ((*(((void (*)(struct Base *__0this , int __0__free ))(__1p -> __vptr__4Base [1]).f))))( ((struct Base *)((((char *)__1p ))+ (__1p -> __vptr__4Base [1]).d)), 3) ,
0 ) :0 ;

return 0 ;

}
} static void __dt__3DerFv (
struct Der *__0this , 
int __0__free );
struct __mptr __vtbl__3Der__72_virtual_dtor_C[] = {0,0,0,
0,0,(__vptp)__dt__3DerFv ,
0,0,0};
struct __mptr __vtbl__4Base__72_virtual_dtor_C[] = {0,0,0,
0,0,(__vptp)__dt__4BaseFv ,
0,0,0};
static void __dt__3DerFv (struct Der *__0this , 
int __0__free ){ 
if (__0this ){ __0this -> __vptr__4Base = (struct __mptr *) __ptbl_vec__72_virtual_dtor_C_[1];

printf ( (const char *)"~Der\n") ;

if (__0this ){ ( ((((struct Base *)__0this ))?(((void )( ((((struct Base *)__0this ))-> __vptr__4Base = (struct __mptr *) __ptbl_vec__72_virtual_dtor_C_[0]), ( printf ( (const
char *)"~Base\n") , ((((struct Base *)__0this ))?(((void )(((void )0 )))):(((void )0 )))) ) )):(((void
)0 )))) ;

if (__0__free & 1)__dl__FPv ( (void *)__0this ) ;
} } 
}

static void __dt__4BaseFv (struct Base *__0this , 
int __0__free ){ 
if (__0this ){ __0this -> __vptr__4Base = (struct __mptr *) __ptbl_vec__72_virtual_dtor_C_[0];
printf ( (const char *)"~Base\n") ;

if (__0this )if (__0__free & 1)__dl__FPv ( (void *)__0this ) ;
} 
}
struct __mptr* __ptbl_vec__72_virtual_dtor_C_[] = {
__vtbl__4Base__72_virtual_dtor_C,
__vtbl__3Der__72_virtual_dtor_C,

};


/* the end */
