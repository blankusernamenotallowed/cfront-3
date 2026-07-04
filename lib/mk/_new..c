
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < ../new/_new.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec_____new__new_C_[];


typedef void (*PFVV )(void );
extern PFVV _new_handler ;


typedef long ptrdiff_t ;

typedef unsigned long size_t ;

extern char *malloc (unsigned int );

void *__nw__FUl (size_t __1size )
{ 
void *__1_last_allocation ;

if (__1size == 0 )__1size = 1 ;

;

while ((__1_last_allocation = (void *)malloc ( ((unsigned int )__1size )) )== 0 ){ 
if (_new_handler && __1size )
((*_new_handler ))( ) ;
else 
return (void *)0 ;
}
return __1_last_allocation ;
}


/* the end */
