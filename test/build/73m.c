
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 73.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__73_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Global;

struct Global {	/* sizeof Global == 4 */
int v__6Global ;
};

extern int printf (const char *,...);

extern void *__nw__FUl (unsigned long );

extern void __dl__FPv (void *);



struct Global g = { 0 } ;


int main (void ){ _main(); { 
struct Global *__0__X1 ;

printf ( (const char *)"main sees %d\n", ( (__0__X1 = (& g )), ( __0__X1 ->
v__6Global ) ) ) ;
return 0 ;
}
} 
void __sti__73_C_main_ (void )
{ 
struct Global *__0__X2 ;

( (__0__X2 = (& g )), ( ((__0__X2 || (__0__X2 = (struct Global *)__nw__FUl ( (unsigned long )(sizeof (struct Global))) ))?(
(__0__X2 -> v__6Global = 42 ), printf ( (const char *)"ctor\n") ) :0 ), __0__X2 )
) ;

}

void __std__73_C_main_ (void )
{ 
struct Global *__0__X3 ;

( (__0__X3 = (& g )), ( (__0__X3 ?(((void )( printf ( (const char *)"dtor\n")
, (__0__X3 ?(((void )(((void )0 )))):(((void )0 )))) )):(((void )0 )))) ) ;

}


/* the end */
