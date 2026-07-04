
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < ../new/_handler.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec_____new__handler_C_[];


typedef void (*PFVV )(void );
extern PFVV _new_handler ;
PFVV _new_handler = 0 ;
PFVV set_new_handler__FPFv_v (PFVV __1handler )
{ 
PFVV __1rr ;

__1rr = _new_handler ;
_new_handler = __1handler ;
return __1rr ;
}


/* the end */
