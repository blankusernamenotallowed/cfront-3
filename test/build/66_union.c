
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 66_union.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__66_union_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
union U;

union U {	/* sizeof U == 4 */

int i__1U ;

char c__1U [4];
};

extern int printf (const char *,...);

int main (void ){ _main(); { union U __1u ;

__1u . i__1U = 0x41424344 ;

printf ( (const char *)"%c%c\n", __1u . c__1U [0 ], __1u . c__1U [3 ]) ;

return 0 ;

}
} 

/* the end */
