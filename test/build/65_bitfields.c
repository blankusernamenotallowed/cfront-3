
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 65_bitfields.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__65_bitfields_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Flags;

struct Flags {	/* sizeof Flags == 4 */

unsigned int a__5Flags :1;

unsigned int b__5Flags :3;

unsigned int c__5Flags :4;
};

extern int printf (const char *,...);

int main (void ){ _main(); { struct Flags __1f ;

__1f . a__5Flags = 1 ;

__1f . b__5Flags = 5 ;

__1f . c__5Flags = 10 ;

printf ( (const char *)"%d %d %d\n", __1f . a__5Flags , __1f . b__5Flags , __1f . c__5Flags )
;

return 0 ;

}
} 

/* the end */
