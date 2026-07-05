
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 30_inherit.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__30_inherit_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct Animal;

struct Animal {	/* sizeof Animal == 4 */

int legs__6Animal ;
};

extern void *__nw__FUl (unsigned long );
struct Dog;


struct Dog {	/* sizeof Dog == 4 */

int legs__6Animal ;
};



extern int printf (const char *,...);

int main (void ){ _main(); { 
struct Dog __1d ;

struct Animal *__0__X1 ;

( (( (__0__X1 = (((struct Animal *)(& __1d )))), ( ((__0__X1 || (__0__X1 = (struct Animal *)__nw__FUl ( (unsigned long )(sizeof
(struct Animal))) ))?( (__0__X1 -> legs__6Animal = 4 ), 0 ) :0 ), __0__X1 ) ) ), (& __1d )) ;
printf ( (const char *)"legs=%d\n", ( ((struct Animal *)(& __1d ))-> legs__6Animal ) )
;
return 0 ;
}
} 

/* the end */
