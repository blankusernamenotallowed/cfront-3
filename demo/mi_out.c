#line 1 "demo/mi.C"

/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < demo/mi.C > */

#line 1 "demo/mi.C"
void *__vec_new (void *, int , int , void *);

#line 1 "demo/mi.C"
void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

#line 1 "demo/mi.C"
extern struct __mptr* __ptbl_vec__demo_mi_C_[];

#line 1 "demo/mi.C"
struct IPersist;

#line 2 "demo/mi.C"
struct IPersist {	/* sizeof IPersist == 8 */

#line 4 "demo/mi.C"
struct __mptr *__vptr__8IPersist ;
};

#line 1 "demo/mi.C"
extern void *__nw__FUl (unsigned long );
struct IService;

#line 6 "demo/mi.C"
struct IService {	/* sizeof IService == 8 */

#line 8 "demo/mi.C"
struct __mptr *__vptr__8IService ;
};
struct CSample;

#line 4 "demo/mi.C"

#line 8 "demo/mi.C"

#line 10 "demo/mi.C"
struct CSample {	/* sizeof CSample == 24 */

#line 4 "demo/mi.C"
struct __mptr *__vptr__8IPersist ;
struct IService OIService;

#line 11 "demo/mi.C"
long m_cRef__7CSample ;
};

#line 15 "demo/mi.C"

#line 3 "demo/mi.C"
int GetClassID__8IPersistFv (struct IPersist *__0this );

#line 7 "demo/mi.C"
int QueryService__8IServiceFv (struct IService *__0this );

#line 17 "demo/mi.C"
int main (void ){ _main(); 
#line 18 "demo/mi.C"
{ 
#line 19 "demo/mi.C"
struct CSample *__1c ;
struct IPersist *__1p ;
struct IService *__1q ;

#line 22 "demo/mi.C"
struct CSample *__0__X5 ;

#line 22 "demo/mi.C"
struct IPersist *__0__X4 ;

#line 19 "demo/mi.C"
__1c = ( (__0__X5 = 0 ), ( ((__0__X5 || (__0__X5 = (struct CSample *)__nw__FUl ( (unsigned long )(sizeof (struct CSample))) ))?(
#line 19 "demo/mi.C"
( ( ( (__0__X4 = (((struct IPersist *)__0__X5 ))), ( ((__0__X4 || (__0__X4 = (struct IPersist *)__nw__FUl ( (unsigned long )(sizeof
#line 19 "demo/mi.C"
(struct IPersist))) ))?(__0__X4 -> __vptr__8IPersist = (struct __mptr *) __ptbl_vec__demo_mi_C_[0]):0 ), __0__X4 ) ) , ( (((((struct IService *)((((char *)__0__X5 ))+ 8)))|| (__nw__FUl (
#line 19 "demo/mi.C"
(unsigned long )(sizeof (struct IService))) ))?((((struct IService *)((((char *)__0__X5 ))+ 8)))-> __vptr__8IService = (struct __mptr *) __ptbl_vec__demo_mi_C_[1]):0 ), (((struct IService *)((((char *)__0__X5 ))+
#line 19 "demo/mi.C"
8)))) ) , (__0__X5 -> __vptr__8IPersist = (struct __mptr *) __ptbl_vec__demo_mi_C_[2])) , (__0__X5 -> OIService. __vptr__8IService =  __ptbl_vec__demo_mi_C_[3])) :0 ), __0__X5 )
#line 19 "demo/mi.C"
) ;
__1p = (struct IPersist *)__1c ;
__1q = (((struct IService *)(__1c ?(((struct CSample *)((((char *)__1c ))+ 8))):0 )));
return (((*(((int (*)(struct IPersist *__0this ))(__1p -> __vptr__8IPersist [1]).f))))( ((struct IPersist *)((((char *)__1p ))+ (__1p -> __vptr__8IPersist [1]).d))) + ((*(((int (*)(struct IService *__0this ))(__1q ->
#line 22 "demo/mi.C"
__vptr__8IService [1]).f))))( ((struct IService *)((((char *)__1q ))+ (__1q -> __vptr__8IService [1]).d))) );
}
} static int QueryService__7CSampleFv (
#line 14 "demo/mi.C"
struct CSample *__0this );
struct __mptr __vtbl__8IService__7CSample__demo_mi_C[] = {0,0,0,
-8,0,(__vptp)QueryService__7CSampleFv ,
0,0,0};
static int GetClassID__7CSampleFv (
#line 13 "demo/mi.C"
struct CSample *__0this );
struct __mptr __vtbl__7CSample__demo_mi_C[] = {0,0,0,
0,0,(__vptp)GetClassID__7CSampleFv ,
0,0,(__vptp)QueryService__7CSampleFv ,
0,0,0};
extern struct __mptr __vtbl__8IService[];
extern struct __mptr __vtbl__8IPersist[];
static int QueryService__7CSampleFv (struct CSample *__0this ){ return 2 ;

#line 14 "demo/mi.C"
}

#line 13 "demo/mi.C"
static int GetClassID__7CSampleFv (struct CSample *__0this ){ return 1 ;

#line 13 "demo/mi.C"
}
struct __mptr* __ptbl_vec__demo_mi_C_[] = {
__vtbl__8IPersist,
__vtbl__8IService,
__vtbl__7CSample__demo_mi_C,
__vtbl__8IService__7CSample__demo_mi_C,

};

#line 23 "demo/mi.C"

/* the end */
