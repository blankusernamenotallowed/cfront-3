
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 71_array_of_obj.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__71_array_of_obj_C_[];


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

static struct C *__ct__1CFv (struct C *__0this );
int main (void ){ _main(); { struct C *__1a ;

__1a = (((struct C *)__vec_new ( ((void *)0 ), 3, sizeof (struct C ), ((void *)__ct__1CFv )) ));

printf ( (const char *)"%d %d\n", (__1a [0 ]). v__1C , (__1a [2 ]). v__1C ) ;

return 0 ;

}
} 
static struct C *__ct__1CFv (struct C *__0this ){ if (__0this || (__0this = (struct C *)__nw__FUl ( (unsigned long )(sizeof (struct C)))
))__0this -> v__1C = 7 ;

return __0this ;

}


/* the end */
