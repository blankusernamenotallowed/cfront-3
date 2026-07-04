
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < ../generic/generic.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec_____generic_generic_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];

extern struct _iobuf *_get_stderr (void );

extern int fprintf (struct _iobuf *, const char *,...);

extern void abort (void );

int genericerror__FiPc (int __1n , char *__1s )
{ 
fprintf ( _get_stderr ( ) , (const char *)"%s %d\n",
__1s ?__1s :(((char *)"error in generic library function")), __1n ) ;

abort ( ) ;
return 0 ;
}


/* the end */
