
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < ../new/_vec.C > */

void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec_____new__vec_C_[];


typedef void *PV ;
typedef void (*PF )(PV , int , int , int , int , int , int
, int , int );
typedef void (*PFI )(PV , int ,...);

static PV __cache_key ;
static int __cache_count ;

extern int __insert_new_array__FPvi (PV __0key , int __0count );

extern void *__nw__FUl (unsigned long );

extern void __dl__FPv (void *);

PV __vec_new (PV __1op , int __1n , int __1sz , PV __1f )
{ 
int __1es ;
int __1opf ;

__1opf = (__1op == 0 );

if (__1op == 0 )
__1op = (((void *)(((char *)__nw__FUl ( (unsigned long )((sizeof (char ))* (__1n * __1sz ))) ))));

if (__1op ){ 
__1es = 0 ;
if (__cache_key )
__1es = __insert_new_array__FPvi ( __cache_key , __cache_count ) ;
if (__1es == -1){ 
if (__1opf )
__dl__FPv ( __1op ) ;
return (void *)0 ;
}
__cache_key = __1op ;
__cache_count = __1n ;
}

if (__1op && __1f ){ 
register char *__2p ;
register char *__2lim ;
register PF __2fp ;

__2p = (((char *)__1op ));
__2lim = (__2p + (__1n * __1sz ));
__2fp = (((void (*)(PV , int , int , int , int , int , int
, int , int ))__1f ));
while (__2p < __2lim ){ 
((*__2fp ))( ((void *)__2p ), 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 )
;
__2p += __1sz ;
}
}
return (((void *)__1op ));
}

extern int __remove_old_array__FPv (PV __0key );

void __vec_delete (PV __1op , int __1n , int __1sz , PV __1f , int __1del , int __1__A1 )
{ 
if (__1op ){ 
int
__2ans ;

__2ans = ((__cache_key == __1op )?( (__cache_key = 0 ), __cache_count ) :__remove_old_array__FPv ( __1op ) );

if (__1n == -1)__1n = __2ans ;
if (__1f ){ 
register char *__3cp ;
register char *__3p ;
register PFI __3fp ;

__3cp = (((char *)__1op ));
__3p = __3cp ;
__3fp = (((void (*)(PV , int ,...))__1f ));
__3p += (__1n * __1sz );
while (__3p > __3cp ){ 
__3p -= __1sz ;
((*__3fp ))( ((void *)__3p ), 2 ) ;
}
}
if (__1del )__dl__FPv ( __1op ) ;
}
}


/* the end */
