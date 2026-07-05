
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < 56_operator_plus.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__56_operator_plus_C_[];


typedef char *va_list ;
struct _iobuf;

extern char *sys_errlist [];
extern int sys_nerr ;
extern unsigned char *_bufendtab [];
struct V;

struct V {	/* sizeof V == 8 */

int x__1V ;

int y__1V ;
};

extern void *__nw__FUl (unsigned long );


extern int printf (const char *,...);

int main (void ){ _main(); { struct V __1a ;

struct V __1b ;

struct V __1c ;

struct V __2__X4 ;

int __2__X2 ;

int __2__X3 ;

struct V __0__X__V100akbkaaibke ;

( (( ((& __1a )-> x__1V = 1 ), ((& __1a )-> y__1V = 2 )) ), (& __1a )) ;
( (( ((& __1b )-> x__1V = 3 ), ((& __1b )-> y__1V = 4 )) ), (& __1b )) ;
__1c = ( (__2__X4 = __1b ), ( ( ( (__2__X2 = ((& __1a )-> x__1V + __2__X4 . x__1V )), (
(__2__X3 = ((& __1a )-> y__1V + __2__X4 . y__1V )), ( (( ((& __0__X__V100akbkaaibke )-> x__1V = __2__X2 ), ((& __0__X__V100akbkaaibke )->
y__1V = __2__X3 )) ), (& __0__X__V100akbkaaibke )) ) ) , __0__X__V100akbkaaibke ) ) ) ;

printf ( (const char *)"%d %d\n", __1c . x__1V , __1c . y__1V ) ;

return 0 ;

}
} 

/* the end */
