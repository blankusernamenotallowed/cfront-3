
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < gtest.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__gtest_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Global;

struct Global {	/* sizeof Global == 4 */

int v__6Global ;
};

extern void *__nw__FUl (unsigned long );


struct Global g = { 0 } ;

extern int printf (const char *,...);

int main (void ){ _main(); { 
printf ( (const char *)"g.v = %d\n", g . v__6Global ) ;

return 0 ;
}
} 
void __sti__gtest_C_main_ (void )
{ 
struct Global *__0__X1 ;

( (__0__X1 = (& g )), ( ((__0__X1 || (__0__X1 = (struct Global *)__nw__FUl ( (unsigned long )(sizeof (struct Global))) ))?(
(__0__X1 -> v__6Global = 12345 ), 0 ) :0 ), __0__X1 ) ) ;

}


/* the end */
