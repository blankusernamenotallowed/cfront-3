
/* <<AT&T C++ Language System <3.0.3> 05/05/94>> */
char __cfront_version_303_xxxxxxxx;
/* < lib/new/_arr_map.C > */


void *__vec_new (void *, int , int , void *);

void __vec_delete (void *, int , int , void *, int , int );
typedef int (*__vptp)(void);
struct __mptr {short d; short i; __vptp f; };

extern struct __mptr* __ptbl_vec__lib_new__arr_map_C_[];


typedef long ptrdiff_t ;

typedef unsigned long size_t ;

typedef void *KEYTYP ;
struct __pnd;
struct __pnd_internal_node;
struct RECORD;


struct __Record_Pool;
struct Record_shell;

struct RECORD {	/* sizeof RECORD == 16 */

unsigned long key__6RECORD ;
int count__6RECORD ;
};

struct Record_shell {	/* sizeof Record_shell == 16 */

struct Record_shell *next__12Record_shell ;
char dummy__12Record_shell [8];
};

struct __Record_Pool {	/* sizeof __Record_Pool == 2400 */

struct Record_shell slot__13__Record_Pool [150];
};

extern struct Record_shell *top__13__Record_Pool ;
struct __Record_Pool *__ct__13__Record_PoolFv (struct __Record_Pool *__0this );

extern void *__nw__FUl (unsigned long );

struct Record_shell *top__13__Record_Pool = 0 ;




struct pnd_internal_item;
union __Q2_17pnd_internal_item4__C1;

union  __Q2_17pnd_internal_item4__C1 {	/* sizeof __Q2_17pnd_internal_item4__C1 == 8 */
struct RECORD *ext_leaf ;
struct __pnd_internal_node *nodep ;
};

struct pnd_internal_item {	/* sizeof pnd_internal_item == 16 */

union  __Q2_17pnd_internal_item4__C1 __O1__17pnd_internal_item ;
int this_is_leaf__17pnd_internal_item ;
};
struct __Node_Pool;


struct Node_shell;

struct __pnd_internal_node {	/* sizeof __pnd_internal_node == 520 */

struct pnd_internal_item item__19__pnd_internal_node [32];
int busy_count__19__pnd_internal_node ;
};

struct Node_shell {	/* sizeof Node_shell == 520 */

struct Node_shell *next__10Node_shell ;
char dummy__10Node_shell [512];
};

struct __Node_Pool {	/* sizeof __Node_Pool == 5200 */

struct Node_shell slot__11__Node_Pool [10];
};

extern struct Node_shell *top__11__Node_Pool ;
struct __Node_Pool *__ct__11__Node_PoolFv (struct __Node_Pool *__0this );

struct Node_shell *top__11__Node_Pool = 0 ;




struct __pnd {	/* sizeof __pnd == 16 */

struct pnd_internal_item contents__5__pnd ;
};

extern struct __pnd *the_table__5__pnd ;

struct __pnd *the_table__5__pnd = 0 ;

void initialize__5__pndSFv (void );
int insert__5__pndFPvi (struct __pnd *__0this , KEYTYP , int );

int __insert_new_array__FPvi (KEYTYP __1key , int __1count )
{ 
if (the_table__5__pnd == 0 )
initialize__5__pndSFv ( ) ;
if (the_table__5__pnd == 0 )
return -1;
if (insert__5__pndFPvi ( the_table__5__pnd , __1key , __1count ) == -1)
return -1;
return 0 ;
}

int remove__5__pndFPv (struct __pnd *__0this , KEYTYP );

int __remove_old_array__FPv (KEYTYP __1key )
{ 
return ((the_table__5__pnd == 0 )?-1:remove__5__pndFPv ( the_table__5__pnd , __1key ) );
}



struct __pnd_internal_node *__ct__19__pnd_internal_nodeFv (register struct __pnd_internal_node *__0this )
{ 
register struct pnd_internal_item *__1itemp ;
register int __1i ;

struct pnd_internal_item *__0__X5 ;

void *__2__Xans00qvzpaaibic ;

if (__0this || (__0this = (struct __pnd_internal_node *)( (((void *)( (__2__Xans00qvzpaaibic = 0 ), ( ((top__11__Node_Pool == 0 )?__ct__11__Node_PoolFv ( (struct __Node_Pool *)0 )
:0 ), ( ((top__11__Node_Pool != 0 )?( (__2__Xans00qvzpaaibic = (void *)top__11__Node_Pool ), (top__11__Node_Pool = top__11__Node_Pool -> next__10Node_shell )) :0 ), (((void *)__2__Xans00qvzpaaibic ))) )
) ))) )){ 
__1itemp = (& (__0this -> item__19__pnd_internal_node [0 ]));
__1i = 32;
while (__1i -- )
( (__0__X5 = (__1itemp ++ )), ( ( (__0__X5 -> this_is_leaf__17pnd_internal_item = 0 ), (__0__X5 -> __O1__17pnd_internal_item.nodep = 0 ))
, (((void )0 ))) ) ;
__0this -> busy_count__19__pnd_internal_node = 0 ;
} 
return __0this ;
}

















int insert__5__pndFPvi (register struct __pnd *__0this , KEYTYP __1addr , int __1cnt )
{ 
register unsigned long __1mask ;
register unsigned long __1key ;

__1mask = 31;
__1key = ((((unsigned long )__1addr ))& 3);
if (__1key )
__1key <<= ((8 * (((int )(sizeof (long )))))- 2 );
__1key |= ((((unsigned long )__1addr ))>> 2 );
{ struct RECORD *__1new_rec ;
register int __1unshift ;
register struct pnd_internal_item *__1itemp ;
register struct __pnd_internal_node *__1nodep ;

struct RECORD *__0__X8 ;

void *__2__Xans00q5ukaaibaa ;

__1new_rec = ( (__0__X8 = 0 ), ( ((__0__X8 || (__0__X8 = (struct RECORD *)( (((void *)( (__2__Xans00q5ukaaibaa = 0 ), (
((top__13__Record_Pool == 0 )?__ct__13__Record_PoolFv ( (struct __Record_Pool *)0 ) :0 ), ( ((top__13__Record_Pool != 0 )?( (__2__Xans00q5ukaaibaa = (void *)top__13__Record_Pool ), (top__13__Record_Pool = top__13__Record_Pool -> next__12Record_shell ))
:0 ), (((void *)__2__Xans00q5ukaaibaa ))) ) ) ))) ))?( (__0__X8 -> key__6RECORD = __1key ), (__0__X8 -> count__6RECORD = __1cnt )) :0 ),
__0__X8 ) ) ;
__1unshift = 0 ;
__1itemp = (& __0this -> contents__5__pnd );
__1nodep = 0 ;
if (__1new_rec == 0 )
return -1;
for(;;( (__1mask <<= 5 ), (__1unshift += 5 )) ) { 
if (( (! __1itemp -> __O1__17pnd_internal_item.nodep )) )
break ;

if (( __1itemp -> this_is_leaf__17pnd_internal_item ) ){ 
if (( __1itemp -> __O1__17pnd_internal_item.ext_leaf ) -> key__6RECORD == __1key ){ 
( __1itemp ->
__O1__17pnd_internal_item.ext_leaf ) -> count__6RECORD = __1cnt ;
( (__1new_rec ?(((void )(__1new_rec ?(((void )(((void )( ( ( ((((struct Record_shell *)(((struct Record_shell *)((void *)__1new_rec )))))-> next__12Record_shell = top__13__Record_Pool ), (top__13__Record_Pool =
(((struct Record_shell *)(((struct Record_shell *)((void *)__1new_rec ))))))) , (((void )0 ))) ) )))):(((void )0 ))))):(((void )0 )))) ;
return 0 ;
}
break ;
}
__1nodep = ( __1itemp -> __O1__17pnd_internal_item.nodep ) ;

__1itemp = (& (__1nodep -> item__19__pnd_internal_node [((__1key & __1mask )>> __1unshift )]));
}

if (( (! __1itemp -> __O1__17pnd_internal_item.nodep )) ){ 
( ( (__1itemp -> this_is_leaf__17pnd_internal_item = 1 ), (__1itemp -> __O1__17pnd_internal_item.ext_leaf = __1new_rec ))
, (((void )0 ))) ;
if (__1nodep )
__1nodep -> busy_count__19__pnd_internal_node ++ ;
return 0 ;
}

{ struct RECORD *__1temp ;
unsigned long __1other_key ;

unsigned long __1ind1 ;

unsigned long __1ind2 ;

struct pnd_internal_item *__0__X6 ;

struct pnd_internal_item *__0__X7 ;

__1temp = ( __1itemp -> __O1__17pnd_internal_item.ext_leaf ) ;
__1other_key = __1temp -> key__6RECORD ;

for(;;( (__1mask <<= 5 ), (__1unshift += 5 )) ) { 
__1nodep = __ct__19__pnd_internal_nodeFv ( (struct __pnd_internal_node *)0 ) ;
if (__1nodep == 0 )
return -1;
( ( (__1itemp -> this_is_leaf__17pnd_internal_item = 0 ), (__1itemp -> __O1__17pnd_internal_item.nodep = __1nodep )) , (((void )0 ))) ;

__1ind1 = ((__1other_key & __1mask )>> __1unshift );
__1ind2 = ((__1key & __1mask )>> __1unshift );
if (__1ind1 != __1ind2 )break ;
__1nodep -> busy_count__19__pnd_internal_node = 1 ;
__1itemp = (& (__1nodep -> item__19__pnd_internal_node [__1ind1 ]));
}
( (__0__X6 = (& (__1nodep -> item__19__pnd_internal_node [__1ind1 ]))), ( ( (__0__X6 -> this_is_leaf__17pnd_internal_item = 1 ), (__0__X6 -> __O1__17pnd_internal_item.ext_leaf = __1temp )) ,
(((void )0 ))) ) ;
( (__0__X7 = (& (__1nodep -> item__19__pnd_internal_node [__1ind2 ]))), ( ( (__0__X7 -> this_is_leaf__17pnd_internal_item = 1 ), (__0__X7 -> __O1__17pnd_internal_item.ext_leaf = __1new_rec )) ,
(((void )0 ))) ) ;
__1nodep -> busy_count__19__pnd_internal_node = 2 ;
return 0 ;

}

}
}





















static struct __pnd_internal_node *next_node__17pnd_internal_itemFv (struct pnd_internal_item *__0this );

int remove__5__pndFPv (register struct __pnd *__0this , KEYTYP __1addr )
{ 
struct pnd_internal_item *__1curr_pos [13];
int __1curr_depth ;
if (__1addr == 0 )return -1;
{ register unsigned long __1mask ;
register unsigned long __1key ;

__1mask = 31;
__1key = ((((unsigned long )__1addr ))& 3);
if (__1key )
__1key <<= ((8 * (((int )(sizeof (long )))))- 2 );
__1key |= ((((unsigned long )__1addr ))>> 2 );
{ register int __1unshift ;
register struct pnd_internal_item *__1itemp ;
register struct __pnd_internal_node *__1nodep ;

__1unshift = 0 ;
__1itemp = (& __0this -> contents__5__pnd );
__1nodep = 0 ;
for(__1curr_depth = -1;;( (__1mask <<= 5 ), (__1unshift += 5 )) ) { 
if (( (! __1itemp -> __O1__17pnd_internal_item.nodep )) )
return
-1;
if (( __1itemp -> this_is_leaf__17pnd_internal_item ) )
if (( __1itemp -> __O1__17pnd_internal_item.ext_leaf ) -> key__6RECORD == __1key )
break ;
else 
return -1;
__1nodep = ( __1itemp -> __O1__17pnd_internal_item.nodep ) ;

(__1curr_pos [(++ __1curr_depth )])= (__1itemp = (& (__1nodep -> item__19__pnd_internal_node [((__1key & __1mask )>> __1unshift )])));
}

{ struct RECORD *__1old_p ;

int __1ans ;

__1old_p = ( __1itemp -> __O1__17pnd_internal_item.ext_leaf ) ;

__1ans = __1old_p -> count__6RECORD ;
( (__1old_p ?(((void )(__1old_p ?(((void )(((void )( ( ( ((((struct Record_shell *)(((struct Record_shell *)((void *)__1old_p )))))-> next__12Record_shell = top__13__Record_Pool ), (top__13__Record_Pool =
(((struct Record_shell *)(((struct Record_shell *)((void *)__1old_p ))))))) , (((void )0 ))) ) )))):(((void )0 ))))):(((void )0 )))) ;
( ( (__1itemp -> this_is_leaf__17pnd_internal_item = 0 ), (__1itemp -> __O1__17pnd_internal_item.nodep = 0 )) , (((void )0 ))) ;
if ((__1curr_depth == -1)|| ((-- __1nodep -> busy_count__19__pnd_internal_node )> 1 ))
return __1ans ;

{ register struct pnd_internal_item *__1itp ;

__1itp = (& (__1nodep -> item__19__pnd_internal_node [0 ]));
while (( (! __1itp -> __O1__17pnd_internal_item.nodep )) || (__1itp == __1itemp ))__1itp ++ ;
if (! ( __1itp -> this_is_leaf__17pnd_internal_item ) )
return __1ans ;
{ struct RECORD *__1temp ;

__1temp = ( __1itp -> __O1__17pnd_internal_item.ext_leaf ) ;

for(;;) { 
( (__1nodep ?(((void )(__1nodep ?(((void )(((void )( ( ( ((((struct Node_shell *)(((struct Node_shell *)((void *)__1nodep )))))-> next__10Node_shell =
top__11__Node_Pool ), (top__11__Node_Pool = (((struct Node_shell *)(((struct Node_shell *)((void *)__1nodep ))))))) , (((void )0 ))) ) )))):(((void )0 ))))):(((void )0 )))) ;

if ((__1curr_depth -- )== 0 ){ 
struct pnd_internal_item *__0__X9 ;

( (__0__X9 = (& __0this -> contents__5__pnd )), ( ( (__0__X9 -> this_is_leaf__17pnd_internal_item = 1 ), (__0__X9 -> __O1__17pnd_internal_item.ext_leaf = __1temp )) ,
(((void )0 ))) ) ;
return __1ans ;
}

__1nodep = ((__1curr_depth == 0 )?next_node__17pnd_internal_itemFv ( & __0this -> contents__5__pnd ) :( (__1curr_pos [(__1curr_depth - 1 )])-> __O1__17pnd_internal_item.nodep ) );
if (__1nodep -> busy_count__19__pnd_internal_node > 1 ){ 
( ( ((__1curr_pos [__1curr_depth ])-> this_is_leaf__17pnd_internal_item = 1 ), ((__1curr_pos [__1curr_depth ])-> __O1__17pnd_internal_item.ext_leaf = __1temp )) , (((void
)0 ))) ;
return __1ans ;
}

}

}

}

}

}

}
}


struct __pnd *__ct__5__pndFv (struct __pnd *__0this )
{ 
struct pnd_internal_item *__0__X10 ;

if (__0this || (__0this = (struct __pnd *)__nw__FUl ( (unsigned long )(sizeof (struct __pnd))) ))
( (__0__X10 = (& __0this -> contents__5__pnd )),
( ( (__0__X10 -> this_is_leaf__17pnd_internal_item = 0 ), (__0__X10 -> __O1__17pnd_internal_item.nodep = 0 )) , (((void )0 ))) ) ;

return __0this ;
}

void initialize__5__pndSFv (void )
{ 
the_table__5__pnd = __ct__5__pndFv ( (struct __pnd *)0 ) ;
}

struct __Record_Pool *__ct__13__Record_PoolFv (register struct __Record_Pool *__0this )
{ 
register int __1i ;
register struct Record_shell *__1p ;
register struct Record_shell *__1q ;

if (__0this || (__0this = (struct __Record_Pool *)__nw__FUl ( (unsigned long )(sizeof (struct __Record_Pool))) )){ 
__1i = 150 ;
__1p = __0this -> slot__13__Record_Pool ;

while (-- __1i ){ 
__1q = (__1p ++ );
__1q -> next__12Record_shell = __1p ;
}
__1p -> next__12Record_shell = top__13__Record_Pool ;
top__13__Record_Pool = __0this -> slot__13__Record_Pool ;
} 
return __0this ;
}

struct __Node_Pool *__ct__11__Node_PoolFv (register struct __Node_Pool *__0this )
{ 
register int __1i ;
register struct Node_shell *__1p ;
register struct Node_shell *__1q ;

if (__0this || (__0this = (struct __Node_Pool *)__nw__FUl ( (unsigned long )(sizeof (struct __Node_Pool))) )){ 
__1i = 10 ;
__1p = __0this -> slot__11__Node_Pool ;

while (-- __1i ){ 
__1q = (__1p ++ );
__1q -> next__10Node_shell = __1p ;
}
__1p -> next__10Node_shell = top__11__Node_Pool ;
top__11__Node_Pool = __0this -> slot__11__Node_Pool ;
} 
return __0this ;
}

static struct __pnd_internal_node *next_node__17pnd_internal_itemFv (struct pnd_internal_item *__0this ){ return __0this -> __O1__17pnd_internal_item.nodep ;

}




/* the end */
