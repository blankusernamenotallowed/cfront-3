
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < lib/static/_dtor.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__lib_static__dtor_C_[];


typedef void (*PFV )(void );
extern PFV _dtors [1];
PFV _dtors [1]= { ((void (*)(void ))0 )} ;


/* the end */
