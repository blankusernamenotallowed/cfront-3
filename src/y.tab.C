/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 29 "gram.y"

#include "cfront.h"
#include "size.h"
#include "template.h"
#include <string.h>
#ifdef SVR42
#include <unistd.h>
#endif
// include tqueue.h after YYSTYPE is defined ...

int		in_friend = 0;
int		must_be_friend = 0;
int		dont_instantiate = 0;
static int explicit_template_definition = 0;
Pname righttname=0;


static struct parstate {
	Ptype intypedef;
	int   infriend;
	int   defercheck;
	Pname intag;
	int cid;
} pstate[BLMAX];
static int px;
extern int classid;
static void
SAVE_STATE()
{
//error('d',"save_state: in_typedef%t in_tag%n defer_check %d",in_typedef,in_tag,defer_check);
	if ( px >= BLMAX ) error('i',"parsing state stack overflow -- current table %s",Ctbl->whereami());
	pstate[px].intypedef = in_typedef;
	pstate[px].infriend = in_friend;
	in_typedef = 0;
	in_friend = 0;
	pstate[px].defercheck = defer_check;
	defer_check = 0;
	pstate[px].intag = in_tag;
	in_tag = 0;
	pstate[px].cid = classid;
	classid = 0;
	++px;
}
static void
RESTORE_STATE()
{
//error('d',"restore_state: in_typedef%t in_tag%n defer_check %d",in_typedef,in_tag,defer_check);
	if ( --px < 0 ) error('i',"parsing state stack underflow -- current table %s",Ctbl->whereami());
	in_typedef = pstate[px].intypedef;
	in_friend = pstate[px].infriend;
	defer_check = pstate[px].defercheck;
	in_tag = pstate[px].intag;
	classid = pstate[px].cid;
//error('d',"            -> in_typedef%t in_tag%n defer_check %d",in_typedef,in_tag,defer_check);
}


//SYM parsing symbol table management
inline void
PUSH_ARG_SCOPE()
{
DB(if(Kdebug>=1)error('d',"push arg table; %ctbl %s",'C',Ctbl->whereami()););
	Ctbl = new ktable( 0, Ctbl, 0 );
	Ctbl->k_id = ARG;
}
inline void
PUSH_CLASS_SCOPE( Pname n )
{
DB(if(Kdebug>=1)error('d',"pushC table%n; %ctbl %s",n,'C',Ctbl->whereami()););
	// table allocated in name::tname() to avoid problems with forward
	//     refs to class templates
	Pclass cl = n->tp->classtype();
	cl->k_tbl->k_next = Ctbl;
	Ctbl = cl->k_tbl;
	Ctbl->expand(CTBLSIZE);
}
inline void
PUSH_BLOCK_SCOPE()
{
DB(if(Kdebug>=1)error('d',"push block tbl; %ctbl %s in %s",'C',Ctbl->whereami(),Ctbl->k_next->whereami()););
	if ( Ctbl->k_id == ARG )
		Ctbl->expand(TBLSIZE);
	else {
		Ctbl = new ktable(TBLSIZE, Ctbl, Ctbl->k_name );
	}
	Ctbl->k_id = BLOCK;
	if ( Ctbl->k_next == Gtbl
	||   Ctbl->k_next->k_id == BLOCK
	||   Ctbl->k_next->k_id == CLASS )
		Ctbl->k_t->next = Ctbl->k_next->k_t;
}
inline void
PUSH_TEMPLATE_SCOPE()
{
DB(if(Kdebug>=1)error('d',"push template tbl; %ctbl %s",'C',Ctbl->whereami()););
	Ctbl = new ktable( 0, Ctbl, 0 );
	Ctbl->k_id = TEMPLATE;
}
inline void
POP_SCOPE( int deallocate = 0 )
{
DB(if(Kdebug>=1)error('d',"pop tbl %s",Ctbl->whereami()););
	if ( Ctbl == Gtbl ) error('i', "bad parsing table");
	Pktab b = Ctbl;
	Ctbl = Ctbl->k_next;
	if ( b->k_id == ARG || deallocate ) delete b;
}


/*SYM -- replaces set_scope()/curr_scope for switching between scopes
 *       in member defs
 * Temporarily reset scope in member defs:
 *     int X::f( T t = a ) { ... }
 *     int X::s[10] =        ... ,  i = 3;
 *            |----scope of X----|
 * ??? What about exprs "p->operator T()", etc ???
 */
// Although local member defs are illegal outside a local class, scopes
//    are stacked for error recovery / extensibility.
struct pcontext {
	Pktab ktbl;
	int   saved_template;
};
static pcontext scopestack[BLMAX];
static int scopex = 0;
Pname
SET_SCOPE( Pname n )
{
	Pktab ntb;
	if ( n == 0 ) ntb = 0;
	else if ( n == sta_name ) ntb = Gtbl;
	else if ( n->n_template_arg == template_type_formal ) {
		DB(if(Kdebug>=1)error('d',"set scope%n -- template formal -- currently in %s next %s",n,Ctbl->whereami(),Ctbl->k_next->whereami()););
		return n;
	}
	else if ( n->tp ) {
		Ptype t = n->tp->skiptypedefs();
		if ( t->base==COBJ ) ntb = t->classtype()->k_tbl;
		else ntb = 0;
	} else ntb = 0;
	DB(if(Kdebug>=1)error('d',"set scope%n ntb %s next %s, currently in %s",n,ntb->whereami(),ntb?ntb->k_next->whereami():"<nil>",Ctbl->whereami()););
	if (ntb == 0) return 0;//error('i',"scope set to null table(n==%n)!",n);
	if ( scopex >= BLMAX ) error('i',"set scope %s: parsing scope stack overflow -- current table %s",ntb->whereami(),Ctbl->whereami());
	Pktab tt = Ctbl;
	if ( Ctbl->k_id == TEMPLATE ) {
		// parsing template member function
		//    template<...> PT<...>::f() {}
		// be sure template params are in scope when parsing f
		// -- extract template scope from current scope and put it
		//    in new scope
		Ctbl = Ctbl->k_next;
		tt->k_next = ntb->k_next;
		ntb->k_next = tt;
		scopestack[scopex].saved_template = 1;
	}
	else if ( Ctbl->k_id == ARG && Ctbl->k_next->k_id == TEMPLATE ) {
		// parsing static data member template with declarator ()'s.
		//    template<...> T (PT<...>::d) = v;
		// interpose PT's table between ARG table and its parent
		Ctbl = Ctbl->k_next->k_next;
		tt->k_next->k_next = ntb->k_next;
		ntb->k_next = tt->k_next;
		tt->k_next = ntb;
		scopestack[scopex].saved_template = 1;
		ntb = tt;
	}
	scopestack[scopex++].ktbl = Ctbl;
	Ctbl = ntb;
	return n;
}
void
UNSET_SCOPE()
{
	// restore surrounding template scope, if appropriate
	Pktab tt = 0;
	if ( --scopex < 0 ) error('i',"parsing scope stack underflow -- current scope %s",Ctbl->whereami());
	if ( scopestack[scopex].saved_template ) {
		scopestack[scopex].saved_template = 0;
		if ( Ctbl->k_next==0 || Ctbl->k_next->k_id != TEMPLATE )
			error('i',"set scope failed restoring template table -- current table %s",Ctbl->whereami());
		tt = Ctbl->k_next;
		Ctbl->k_next = tt->k_next;
	}
	DB(if(Kdebug>=1)error('d',"unset scope %s -> %s tt %s",Ctbl->whereami(),scopestack[scopex].ktbl->whereami(),tt?tt->whereami():"<nil>"););
	Ctbl = scopestack[scopex].ktbl;
	if ( tt ) { tt->k_next = Ctbl; Ctbl = tt; }
}
inline Pktab
GET_XSCOPE()
{
	if ( scopex-1 < 0 ) error('i',"parsing scope stack underflow -- current table %s",Ctbl->whereami());
	return scopestack[scopex-1].ktbl;
}
inline void
SET_XSCOPE( Pktab tb )
{
	if ( scopex-1 < 0 ) error('i',"parsing scope stack underflow -- current table %s",Ctbl->whereami());
	scopestack[scopex-1].ktbl = tb;
}


// macros
#define copy_if_need_be(s)  ((templp->in_progress || templp->parameters_in_progress) ? strdup(s) : s) 
#define YYMAXDEPTH 600

#if 0
#define YYCLEAN {free(yys); free(yyv);}
#else
#define YYCLEAN
#endif

#ifdef DBG
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#endif

static int init_seen = 0;
static int cdi = 0;
static Pnlist cd = 0, cd_vec[BLMAX];
static char stmt_seen = 0, stmt_vec[BLMAX];
static Pnlist scd[BLMAX]; // keep track of cd list outside of switch
static int scdp = -1;

static Pname memptr_pn;
static TOK memptr_tok;

static Pname err_name = 0;

// support for template friend declarations within a class
static Pcons templ_friends;

// fcts put into norm2.c just to get them out of gram.y
void sig_name(Pname);	
Ptype tok_to_type(TOK);
void memptrdcl(Pname, Pname, Ptype, Pname);

static bit decl_with_init(Pnlist cd) 
/* do the declarations have an initializer
   or a class object with a constructor */
{
	for (Pname n=cd->head;n;n=n->n_list) {
		if (n->n_initializer) return 1;
		Pname cln=n->tp->is_cl_obj();
		if (cln && Pclass(cln->tp)->c_ctor)
			return 1;
	}
	return 0;
}


static char* 
get_classname(char* s)
{
// error('d',"get_classname(%s)",s);
	char* r = new char[strlen(s)+1];
	sprintf(r,s);
	s = r;

	char* s1 = s;
	while (*s) {
		for ( ; s[0] && (s[0] != '_' || s[1] && s[1] != '_'); s++) s1++;;
		if (*s) {
			if (strncmp(s,"___pt__",7)==0) {
				*s1 = 0;
				return r;
			}
			if (strncmp(s,"__pt__",6)==0) { // parameterized class
				*s1 = '\0';
				return r;
			}
		}
		return r;
	}
	return r;
}

static Pptr doptr(TOK p, TOK t)
{
	Pptr r = new ptr(p,0);
	switch (t) {
	case CONST:
		r->b_const = 1;
               // if (p == RPTR) error('w',"redundant `const' after &");
		break;
	case VOLATILE:
		error('w',"\"volatile\" not implemented (ignored)");
		break;
	default:
		error("syntax error: *%k",t);
	}
	return r;
}

static Pbcl dobase(TOK pr, Pname n, TOK v = 0)
{
// error('d',"dobase(%k %n %k)", pr,n,v);

	Pbcl b = new basecl(0,0);
	b->ppp = pr;	// save protection indicator

	if (n) {
		if (n->base != TNAME) {
			Pname nn = k_find_name(n->string,Ctbl,HIDDEN);
			if ( nn == 0 ) {
				error("BN%n not aTN",n);
				return 0;
			} else
				n = nn;
		}

		Pbase bt = Pbase(n->tp);
		while (bt->base == TYPE) bt = Pbase(bt->b_name->tp);

                if (bt->base != COBJ) {
                        // template <class B> class D : public B {};
                        if (templp->in_progress == true  && bt->base == ANY)
                            error('s',"formalTZ%n used asBC ofY",n);
                        else error("BN%n not aCN",n);
                        return 0;
                }

		if (v) {
			if (v != VIRTUAL) error("syntax error:%k inBCD",v);
			b->base = VIRTUAL;
		}
		else
			b->base = NAME;

		b->bclass = Pclass(bt->b_name->tp);
	}

	return b;
}


#define Ndata(a,b)	b->normalize(Pbase(a),0,0)
#define Ncast(a,b)	b->normalize(Pbase(a),0,1)
#define Nfct(a,b,c)	b->normalize(Pbase(a),Pblock(c),0)
//#define Ncopy(n)	(n->base==TNAME)?new name(n->string):n
inline Pname Ncopy(Pname n)
{
	Pname nn;
	if (n->base!=TNAME) {
		nn = n;
	} else {
		nn = new name(n->string);
		nn->n_template_arg = n->n_template_arg;
	}
	return nn;
}

#define Finit(p)	Pfct(p)->f_init
#define Fargdcl(p,q,r)	Pfct(p)->argdcl(q,r)
#define Freturns(p)	Pfct(p)->returns
#define Fbody(p)	Pfct(p)->body /*SYM*/
#define Vtype(v)	Pvec(v)->typ
#define Ptyp(p)		Pptr(p)->typ

		/* avoid redefinitions */
#undef EOFTOK
#undef ASM
#undef BREAK
#undef CASE
#undef CONTINUE
#undef DEFAULT
#undef DELETE
#undef DO
#undef ELSE
#undef ENUM
#undef FOR
#undef FORTRAN
#undef FRIEND
#undef GOTO
#undef IF
#undef NEW
#undef OPERATOR
#undef RETURN
#undef SIZEOF
#undef SWITCH
#undef THIS
#undef WHILE
#undef LP
#undef RP
#undef LB
#undef RB
#undef REF
#undef DOT
#undef NOT
#undef COMPL
#undef MUL
#undef AND
#undef PLUS
#undef MINUS
#undef ER
#undef OR
#undef ANDAND
#undef OROR
#undef QUEST
#undef COLON
#undef ASSIGN
#undef CM
#undef SM
#undef LC
#undef RC
#undef ID
#undef STRING
#undef ICON
#undef FCON
#undef CCON
#undef ZERO
#undef ASOP
#undef RELOP
#undef EQUOP
#undef DIVOP
#undef SHIFTOP
#undef ICOP
#undef TYPE

#undef CATCH
#undef THROW
#undef TRY

#undef TNAME
#undef EMPTY
#undef NO_ID
#undef NO_EXPR
#undef FDEF
#undef ELLIPSIS
#undef AGGR
#undef MEM
#undef MEMPTR
#undef PR
#undef MEMQ
#undef TSCOPE
#undef DECL_MARKER
#undef REFMUL
#undef LDOUBLE
#undef LINKAGE
#undef TEMPLATE

#undef XVIRT
#undef XNLIST
#undef XILINE
#undef XIA
#undef SM_PARAM
#undef PTNAME
#undef NEW_INIT_KLUDGE

#line 521 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#if 0
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    EOFTOK = 0,                    /* EOFTOK  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASM = 1,                       /* ASM  */
    AUTO = 2,                      /* AUTO  */
    BREAK = 3,                     /* BREAK  */
    CASE = 4,                      /* CASE  */
    CONTINUE = 7,                  /* CONTINUE  */
    DEFAULT = 8,                   /* DEFAULT  */
    DELETE = 9,                    /* DELETE  */
    DO = 10,                       /* DO  */
    ELSE = 12,                     /* ELSE  */
    ENUM = 13,                     /* ENUM  */
    FOR = 16,                      /* FOR  */
    FORTRAN = 17,                  /* FORTRAN  */
    FRIEND = 18,                   /* FRIEND  */
    GOTO = 19,                     /* GOTO  */
    IF = 20,                       /* IF  */
    NEW = 23,                      /* NEW  */
    OPERATOR = 24,                 /* OPERATOR  */
    RETURN = 28,                   /* RETURN  */
    SIZEOF = 30,                   /* SIZEOF  */
    SWITCH = 33,                   /* SWITCH  */
    THIS = 34,                     /* THIS  */
    WHILE = 39,                    /* WHILE  */
    LP = 40,                       /* LP  */
    RP = 41,                       /* RP  */
    LB = 42,                       /* LB  */
    RB = 43,                       /* RB  */
    REF = 44,                      /* REF  */
    DOT = 45,                      /* DOT  */
    NOT = 46,                      /* NOT  */
    COMPL = 47,                    /* COMPL  */
    MUL = 50,                      /* MUL  */
    AND = 52,                      /* AND  */
    PLUS = 54,                     /* PLUS  */
    MINUS = 55,                    /* MINUS  */
    LT = 58,                       /* LT  */
    GT = 60,                       /* GT  */
    ER = 64,                       /* ER  */
    OR = 65,                       /* OR  */
    ANDAND = 66,                   /* ANDAND  */
    OROR = 67,                     /* OROR  */
    QUEST = 68,                    /* QUEST  */
    COLON = 69,                    /* COLON  */
    ASSIGN = 70,                   /* ASSIGN  */
    CM = 71,                       /* CM  */
    SM = 72,                       /* SM  */
    LC = 73,                       /* LC  */
    RC = 74,                       /* RC  */
    ID = 80,                       /* ID  */
    STRING = 81,                   /* STRING  */
    ICON = 82,                     /* ICON  */
    FCON = 83,                     /* FCON  */
    CCON = 84,                     /* CCON  */
    NAME = 85,                     /* NAME  */
    ZERO = 86,                     /* ZERO  */
    ASOP = 90,                     /* ASOP  */
    RELOP = 91,                    /* RELOP  */
    EQUOP = 92,                    /* EQUOP  */
    DIVOP = 93,                    /* DIVOP  */
    SHIFTOP = 94,                  /* SHIFTOP  */
    ICOP = 95,                     /* ICOP  */
    TYPE = 97,                     /* TYPE  */
    CATCH = 98,                    /* CATCH  */
    THROW = 99,                    /* THROW  */
    TRY = 100,                     /* TRY  */
    TNAME = 123,                   /* TNAME  */
    EMPTY = 124,                   /* EMPTY  */
    NO_ID = 125,                   /* NO_ID  */
    NO_EXPR = 126,                 /* NO_EXPR  */
    FDEF = 127,                    /* FDEF  */
    ELLIPSIS = 155,                /* ELLIPSIS  */
    AGGR = 156,                    /* AGGR  */
    MEM = 160,                     /* MEM  */
    MEMPTR = 173,                  /* MEMPTR  */
    PR = 175,                      /* PR  */
    MEMQ = 176,                    /* MEMQ  */
    TSCOPE = 178,                  /* TSCOPE  */
    DECL_MARKER = 179,             /* DECL_MARKER  */
    REFMUL = 180,                  /* REFMUL  */
    LDOUBLE = 181,                 /* LDOUBLE  */
    LINKAGE = 182,                 /* LINKAGE  */
    TEMPLATE = 185,                /* TEMPLATE  */
    XVIRT = 200,                   /* XVIRT  */
    XNLIST = 201,                  /* XNLIST  */
    XILINE = 202,                  /* XILINE  */
    XIA = 203,                     /* XIA  */
    SM_PARAM = 207,                /* SM_PARAM  */
    PTNAME = 209,                  /* PTNAME  */
    NEW_INIT_KLUDGE = 210,         /* NEW_INIT_KLUDGE  */
    XDELETED_NODE = 211,           /* XDELETED_NODE  */
    DUMMY_LAST_NODE = 212          /* DUMMY_LAST_NODE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define EOFTOK 0
#define YYerror 256
#define YYUNDEF 257
#define ASM 1
#define AUTO 2
#define BREAK 3
#define CASE 4
#define CONTINUE 7
#define DEFAULT 8
#define DELETE 9
#define DO 10
#define ELSE 12
#define ENUM 13
#define FOR 16
#define FORTRAN 17
#define FRIEND 18
#define GOTO 19
#define IF 20
#define NEW 23
#define OPERATOR 24
#define RETURN 28
#define SIZEOF 30
#define SWITCH 33
#define THIS 34
#define WHILE 39
#define LP 40
#define RP 41
#define LB 42
#define RB 43
#define REF 44
#define DOT 45
#define NOT 46
#define COMPL 47
#define MUL 50
#define AND 52
#define PLUS 54
#define MINUS 55
#define LT 58
#define GT 60
#define ER 64
#define OR 65
#define ANDAND 66
#define OROR 67
#define QUEST 68
#define COLON 69
#define ASSIGN 70
#define CM 71
#define SM 72
#define LC 73
#define RC 74
#define ID 80
#define STRING 81
#define ICON 82
#define FCON 83
#define CCON 84
#define NAME 85
#define ZERO 86
#define ASOP 90
#define RELOP 91
#define EQUOP 92
#define DIVOP 93
#define SHIFTOP 94
#define ICOP 95
#define TYPE 97
#define CATCH 98
#define THROW 99
#define TRY 100
#define TNAME 123
#define EMPTY 124
#define NO_ID 125
#define NO_EXPR 126
#define FDEF 127
#define ELLIPSIS 155
#define AGGR 156
#define MEM 160
#define MEMPTR 173
#define PR 175
#define MEMQ 176
#define TSCOPE 178
#define DECL_MARKER 179
#define REFMUL 180
#define LDOUBLE 181
#define LINKAGE 182
#define TEMPLATE 185
#define XVIRT 200
#define XNLIST 201
#define XILINE 202
#define XIA 203
#define SM_PARAM 207
#define PTNAME 209
#define NEW_INIT_KLUDGE 210
#define XDELETED_NODE 211
#define DUMMY_LAST_NODE 212

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 479 "gram.y"

	char*	s;
	TOK	t;
	int	i;
	loc	l;
	Pname	pn;
	Ptype	pt;
	Pexpr	pe;
	Pstmt	ps;
	Pbase	pb;
	Pnlist	nl;
	Pslist	sl;
	Pelist	el;
	Pbcl	pbc;
	Pptr	pp;
	PP	p;	// fudge: pointer to all class node objects
	Plist	pl;
	toknode* q;	// token queue

#line 778 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* EOFTOK  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASM = 3,                        /* ASM  */
  YYSYMBOL_AUTO = 4,                       /* AUTO  */
  YYSYMBOL_BREAK = 5,                      /* BREAK  */
  YYSYMBOL_CASE = 6,                       /* CASE  */
  YYSYMBOL_CONTINUE = 7,                   /* CONTINUE  */
  YYSYMBOL_DEFAULT = 8,                    /* DEFAULT  */
  YYSYMBOL_DELETE = 9,                     /* DELETE  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_ENUM = 12,                      /* ENUM  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_FORTRAN = 14,                   /* FORTRAN  */
  YYSYMBOL_FRIEND = 15,                    /* FRIEND  */
  YYSYMBOL_GOTO = 16,                      /* GOTO  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_NEW = 18,                       /* NEW  */
  YYSYMBOL_OPERATOR = 19,                  /* OPERATOR  */
  YYSYMBOL_RETURN = 20,                    /* RETURN  */
  YYSYMBOL_SIZEOF = 21,                    /* SIZEOF  */
  YYSYMBOL_SWITCH = 22,                    /* SWITCH  */
  YYSYMBOL_THIS = 23,                      /* THIS  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_LP = 25,                        /* LP  */
  YYSYMBOL_RP = 26,                        /* RP  */
  YYSYMBOL_LB = 27,                        /* LB  */
  YYSYMBOL_RB = 28,                        /* RB  */
  YYSYMBOL_REF = 29,                       /* REF  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_COMPL = 32,                     /* COMPL  */
  YYSYMBOL_MUL = 33,                       /* MUL  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_PLUS = 35,                      /* PLUS  */
  YYSYMBOL_MINUS = 36,                     /* MINUS  */
  YYSYMBOL_LT = 37,                        /* LT  */
  YYSYMBOL_GT = 38,                        /* GT  */
  YYSYMBOL_ER = 39,                        /* ER  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_ANDAND = 41,                    /* ANDAND  */
  YYSYMBOL_OROR = 42,                      /* OROR  */
  YYSYMBOL_QUEST = 43,                     /* QUEST  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_ASSIGN = 45,                    /* ASSIGN  */
  YYSYMBOL_CM = 46,                        /* CM  */
  YYSYMBOL_SM = 47,                        /* SM  */
  YYSYMBOL_LC = 48,                        /* LC  */
  YYSYMBOL_RC = 49,                        /* RC  */
  YYSYMBOL_ID = 50,                        /* ID  */
  YYSYMBOL_STRING = 51,                    /* STRING  */
  YYSYMBOL_ICON = 52,                      /* ICON  */
  YYSYMBOL_FCON = 53,                      /* FCON  */
  YYSYMBOL_CCON = 54,                      /* CCON  */
  YYSYMBOL_NAME = 55,                      /* NAME  */
  YYSYMBOL_ZERO = 56,                      /* ZERO  */
  YYSYMBOL_ASOP = 57,                      /* ASOP  */
  YYSYMBOL_RELOP = 58,                     /* RELOP  */
  YYSYMBOL_EQUOP = 59,                     /* EQUOP  */
  YYSYMBOL_DIVOP = 60,                     /* DIVOP  */
  YYSYMBOL_SHIFTOP = 61,                   /* SHIFTOP  */
  YYSYMBOL_ICOP = 62,                      /* ICOP  */
  YYSYMBOL_TYPE = 63,                      /* TYPE  */
  YYSYMBOL_CATCH = 64,                     /* CATCH  */
  YYSYMBOL_THROW = 65,                     /* THROW  */
  YYSYMBOL_TRY = 66,                       /* TRY  */
  YYSYMBOL_TNAME = 67,                     /* TNAME  */
  YYSYMBOL_EMPTY = 68,                     /* EMPTY  */
  YYSYMBOL_NO_ID = 69,                     /* NO_ID  */
  YYSYMBOL_NO_EXPR = 70,                   /* NO_EXPR  */
  YYSYMBOL_FDEF = 71,                      /* FDEF  */
  YYSYMBOL_ELLIPSIS = 72,                  /* ELLIPSIS  */
  YYSYMBOL_AGGR = 73,                      /* AGGR  */
  YYSYMBOL_MEM = 74,                       /* MEM  */
  YYSYMBOL_MEMPTR = 75,                    /* MEMPTR  */
  YYSYMBOL_PR = 76,                        /* PR  */
  YYSYMBOL_MEMQ = 77,                      /* MEMQ  */
  YYSYMBOL_TSCOPE = 78,                    /* TSCOPE  */
  YYSYMBOL_DECL_MARKER = 79,               /* DECL_MARKER  */
  YYSYMBOL_REFMUL = 80,                    /* REFMUL  */
  YYSYMBOL_LDOUBLE = 81,                   /* LDOUBLE  */
  YYSYMBOL_LINKAGE = 82,                   /* LINKAGE  */
  YYSYMBOL_TEMPLATE = 83,                  /* TEMPLATE  */
  YYSYMBOL_XVIRT = 84,                     /* XVIRT  */
  YYSYMBOL_XNLIST = 85,                    /* XNLIST  */
  YYSYMBOL_XILINE = 86,                    /* XILINE  */
  YYSYMBOL_XIA = 87,                       /* XIA  */
  YYSYMBOL_SM_PARAM = 88,                  /* SM_PARAM  */
  YYSYMBOL_PTNAME = 89,                    /* PTNAME  */
  YYSYMBOL_NEW_INIT_KLUDGE = 90,           /* NEW_INIT_KLUDGE  */
  YYSYMBOL_XDELETED_NODE = 91,             /* XDELETED_NODE  */
  YYSYMBOL_DUMMY_LAST_NODE = 92,           /* DUMMY_LAST_NODE  */
  YYSYMBOL_YYACCEPT = 93,                  /* $accept  */
  YYSYMBOL_ext_def = 94,                   /* ext_def  */
  YYSYMBOL_template = 95,                  /* template  */
  YYSYMBOL_96_1 = 96,                      /* $@1  */
  YYSYMBOL_97_2 = 97,                      /* $@2  */
  YYSYMBOL_98_3 = 98,                      /* $@3  */
  YYSYMBOL_template_def = 99,              /* template_def  */
  YYSYMBOL_identifier = 100,               /* identifier  */
  YYSYMBOL_external_def = 101,             /* external_def  */
  YYSYMBOL_fct_dcl = 102,                  /* fct_dcl  */
  YYSYMBOL_att_fct_def = 103,              /* att_fct_def  */
  YYSYMBOL_104_4 = 104,                    /* @4  */
  YYSYMBOL_fct_def = 105,                  /* fct_def  */
  YYSYMBOL_106_5 = 106,                    /* @5  */
  YYSYMBOL_inline_fct_def = 107,           /* inline_fct_def  */
  YYSYMBOL_108_6 = 108,                    /* $@6  */
  YYSYMBOL_check_inline = 109,             /* check_inline  */
  YYSYMBOL_base_init = 110,                /* base_init  */
  YYSYMBOL_111_7 = 111,                    /* $@7  */
  YYSYMBOL_init_list = 112,                /* init_list  */
  YYSYMBOL_binit = 113,                    /* binit  */
  YYSYMBOL_arg_dcl_list = 114,             /* arg_dcl_list  */
  YYSYMBOL_dl = 115,                       /* dl  */
  YYSYMBOL_116_8 = 116,                    /* $@8  */
  YYSYMBOL_117_9 = 117,                    /* $@9  */
  YYSYMBOL_decl_list = 118,                /* decl_list  */
  YYSYMBOL_data_dcl = 119,                 /* data_dcl  */
  YYSYMBOL_lt = 120,                       /* lt  */
  YYSYMBOL_gt = 121,                       /* gt  */
  YYSYMBOL_tname = 122,                    /* tname  */
  YYSYMBOL_tp = 123,                       /* tp  */
  YYSYMBOL_type = 124,                     /* type  */
  YYSYMBOL_cm = 125,                       /* cm  */
  YYSYMBOL_temp_inst_parms = 126,          /* temp_inst_parms  */
  YYSYMBOL_new_decl2 = 127,                /* new_decl2  */
  YYSYMBOL_new_type2 = 128,                /* new_type2  */
  YYSYMBOL_temp_inst_parm = 129,           /* temp_inst_parm  */
  YYSYMBOL_enumtag = 130,                  /* enumtag  */
  YYSYMBOL_enum_dcl = 131,                 /* enum_dcl  */
  YYSYMBOL_132_10 = 132,                   /* $@10  */
  YYSYMBOL_133_11 = 133,                   /* $@11  */
  YYSYMBOL_moe_list = 134,                 /* moe_list  */
  YYSYMBOL_template_parm_list = 135,       /* template_parm_list  */
  YYSYMBOL_template_parm = 136,            /* template_parm  */
  YYSYMBOL_formal_decl = 137,              /* formal_decl  */
  YYSYMBOL_moe = 138,                      /* moe  */
  YYSYMBOL_139_12 = 139,                   /* $@12  */
  YYSYMBOL_class_dcl = 140,                /* class_dcl  */
  YYSYMBOL_141_13 = 141,                   /* $@13  */
  YYSYMBOL_inline_mem_defs = 142,          /* inline_mem_defs  */
  YYSYMBOL_base_list = 143,                /* base_list  */
  YYSYMBOL_base_unit_list = 144,           /* base_unit_list  */
  YYSYMBOL_base_unit = 145,                /* base_unit  */
  YYSYMBOL_class_head = 146,               /* class_head  */
  YYSYMBOL_tag = 147,                      /* tag  */
  YYSYMBOL_ttag = 148,                     /* ttag  */
  YYSYMBOL_cl_mem_list = 149,              /* cl_mem_list  */
  YYSYMBOL_cl_mem = 150,                   /* cl_mem  */
  YYSYMBOL_fname = 151,                    /* fname  */
  YYSYMBOL_oper = 152,                     /* oper  */
  YYSYMBOL_scope_qualifiers = 153,         /* scope_qualifiers  */
  YYSYMBOL_tn_list = 154,                  /* tn_list  */
  YYSYMBOL_qualified_tname = 155,          /* qualified_tname  */
  YYSYMBOL_fct_attributes = 156,           /* fct_attributes  */
  YYSYMBOL_type_list = 157,                /* type_list  */
  YYSYMBOL_decl = 158,                     /* decl  */
  YYSYMBOL_arg_decl = 159,                 /* arg_decl  */
  YYSYMBOL_new_decl = 160,                 /* new_decl  */
  YYSYMBOL_cast_decl = 161,                /* cast_decl  */
  YYSYMBOL_c_decl = 162,                   /* c_decl  */
  YYSYMBOL_stmt_list = 163,                /* stmt_list  */
  YYSYMBOL_caselab_stmt = 164,             /* caselab_stmt  */
  YYSYMBOL_caselablist = 165,              /* caselablist  */
  YYSYMBOL_condition = 166,                /* condition  */
  YYSYMBOL_block = 167,                    /* block  */
  YYSYMBOL_168_14 = 168,                   /* $@14  */
  YYSYMBOL_simple = 169,                   /* simple  */
  YYSYMBOL_170_15 = 170,                   /* $@15  */
  YYSYMBOL_sm = 171,                       /* sm  */
  YYSYMBOL_172_16 = 172,                   /* $@16  */
  YYSYMBOL_statement = 173,                /* statement  */
  YYSYMBOL_174_17 = 174,                   /* $@17  */
  YYSYMBOL_175_18 = 175,                   /* $@18  */
  YYSYMBOL_176_19 = 176,                   /* @19  */
  YYSYMBOL_177_20 = 177,                   /* @20  */
  YYSYMBOL_178_21 = 178,                   /* $@21  */
  YYSYMBOL_179_22 = 179,                   /* @22  */
  YYSYMBOL_handler_list = 180,             /* handler_list  */
  YYSYMBOL_handler = 181,                  /* handler  */
  YYSYMBOL_exception_type = 182,           /* exception_type  */
  YYSYMBOL_elist = 183,                    /* elist  */
  YYSYMBOL_ex_list = 184,                  /* ex_list  */
  YYSYMBOL_initializer = 185,              /* initializer  */
  YYSYMBOL_ee = 186,                       /* ee  */
  YYSYMBOL_e = 187,                        /* e  */
  YYSYMBOL_term = 188,                     /* term  */
  YYSYMBOL_dtorspec = 189,                 /* dtorspec  */
  YYSYMBOL_term_elist = 190,               /* term_elist  */
  YYSYMBOL_ptname = 191,                   /* ptname  */
  YYSYMBOL_tscope = 192,                   /* tscope  */
  YYSYMBOL_prim = 193,                     /* prim  */
  YYSYMBOL_cast_type = 194,                /* cast_type  */
  YYSYMBOL_term_lp = 195,                  /* term_lp  */
  YYSYMBOL_c_tp = 196,                     /* c_tp  */
  YYSYMBOL_c_type = 197,                   /* c_type  */
  YYSYMBOL_new_type = 198,                 /* new_type  */
  YYSYMBOL_arg_type = 199,                 /* arg_type  */
  YYSYMBOL_200_23 = 200,                   /* $@23  */
  YYSYMBOL_arg_lp = 201,                   /* arg_lp  */
  YYSYMBOL_arg_list = 202,                 /* arg_list  */
  YYSYMBOL_arg_type_list = 203,            /* arg_type_list  */
  YYSYMBOL_at = 204,                       /* at  */
  YYSYMBOL_ellipsis_opt = 205,             /* ellipsis_opt  */
  YYSYMBOL_ptr = 206,                      /* ptr  */
  YYSYMBOL_vec = 207                       /* vec  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 498 "gram.y"

#include "tqueue.h"
extern YYSTYPE yylval;
YYSTYPE yyval;	// classic-yacc global $$ (peeked at by lalex.C); see Makefile sed
extern int yyparse();

// Forward declarations for grammar-action helpers defined at end of file
// (modern C++ requires a declaration before use).
static Pname enumcheck( Pname n );
static void  check_tag();
static void  hoist_al();
static void  arg_redec( Pname fn );
static Pname dummy_dtor( TOK q, TOK d );
static Pname dummy_dtor();
static bit   check_if_base( Pclass c1, Pclass c2 );

// in_typedef should allow for nested in_typedef
extern int	declTag;	 // !1: inline, virtual mod permitted
int		in_sizeof = 0;
int		in_new = 0;
Ptype 		in_typedef = 0;  // catch redefinition of TNAME
Pname		in_tag = 0;      // handle complex typedefs: int (*)()
extern int	defer_check;	 // redefinition typedef check delay

extern 	int must_be_id;	 // !0, TNAME => ID, i.e., int X
int	DECL_TYPE = 0; 	 // lalex() wants this set for global x(*fp)()
int	in_arg_list=0; 	 // !0 when parsing argument list, 1: in (), 2: in <>
static  int in_binit_list=0;
int	in_class_decl=0; // !0 when processing class definition
int	parsing_class_members=0; // !0 when parsing class def but not member function body
int	in_mem_fct=0;    // !0 when parsing member function definition
Ptempl_inst pti = 0; // explicit template class: class X<int> {};

#define yylex lalex
/* bison's "no lookahead" sentinel is YYEMPTY (-2), not yacc's -1; treat any
   negative yychar as empty so a real token gets fetched. */
#define NEXTTOK() ( (yychar<0) ? (yychar=yylex(),yychar) : yychar )
#define EXPECT_ID() must_be_id = 1
#define NOT_EXPECT_ID() must_be_id = 0

Pname syn()
{
ll:
	switch (yyparse()) {
	case 0:		return 0;	// EOF
	case 1:		goto ll;	// no action needed
	default:	return yyval.pn;
	}
}


#line 1063 "y.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  100
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  115
/* YYNRULES -- Number of rules.  */
#define YYNRULES  413
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  706

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   257


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     3,     4,     5,     6,     2,     2,     7,     8,     9,
      10,     2,    11,    12,     2,     2,    13,    14,    15,    16,
      17,     2,     2,    18,    19,     2,     2,     2,    20,     2,
      21,     2,     2,    22,    23,     2,     2,     2,     2,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     2,     2,
      33,     2,    34,     2,    35,    36,     2,     2,    37,     2,
      38,     2,     2,     2,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     2,     2,     2,     2,     2,
      50,    51,    52,    53,    54,    55,    56,     2,     2,     2,
      57,    58,    59,    60,    61,    62,     2,    63,    64,    65,
      66,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,    68,    69,    70,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    72,    73,     2,     2,     2,
      74,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    76,    77,     2,    78,    79,
      80,    81,    82,     2,     2,    83,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      84,    85,    86,    87,     2,     2,     2,    88,     2,    89,
      90,    91,    92,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   731,   731,   732,   733,   734,   740,   746,   750,   762,
     763,   749,   784,   785,   786,   787,   788,   798,   799,   803,
     808,   809,   819,   820,   828,   834,   867,   866,   884,   892,
     903,   902,   921,   929,   948,   947,   963,   999,   999,  1005,
    1009,  1011,  1015,  1020,  1035,  1045,  1052,  1054,  1053,  1065,
    1074,  1073,  1085,  1099,  1123,  1138,  1150,  1156,  1163,  1164,
    1178,  1187,  1200,  1205,  1210,  1216,  1217,  1218,  1234,  1235,
    1250,  1258,  1259,  1260,  1285,  1287,  1289,  1293,  1297,  1303,
    1310,  1315,  1322,  1324,  1329,  1338,  1339,  1347,  1360,  1360,
    1362,  1362,  1364,  1367,  1369,  1378,  1379,  1381,  1387,  1391,
    1398,  1400,  1405,  1409,  1413,  1422,  1430,  1429,  1440,  1444,
    1443,  1493,  1514,  1561,  1568,  1569,  1572,  1573,  1576,  1577,
    1581,  1582,  1583,  1584,  1585,  1588,  1600,  1611,  1649,  1650,
    1653,  1654,  1657,  1667,  1668,  1680,  1681,  1690,  1694,  1703,
    1707,  1708,  1712,  1743,  1744,  1748,  1752,  1763,  1764,  1765,
    1766,  1767,  1768,  1769,  1770,  1771,  1772,  1773,  1774,  1775,
    1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,  1784,  1785,
    1786,  1787,  1788,  1793,  1796,  1817,  1851,  1861,  1872,  1873,
    1896,  1900,  1901,  1905,  1909,  1914,  1926,  1938,  1951,  1964,
    1976,  1988,  1992,  2013,  2018,  2028,  2038,  2043,  2052,  2060,
    2077,  2086,  2094,  2100,  2105,  2110,  2114,  2130,  2140,  2142,
    2148,  2154,  2155,  2161,  2165,  2170,  2177,  2179,  2190,  2193,
    2198,  2209,  2217,  2223,  2231,  2230,  2251,  2255,  2261,  2263,
    2265,  2267,  2269,  2269,  2271,  2287,  2287,  2296,  2297,  2299,
    2301,  2306,  2328,  2339,  2340,  2342,  2344,  2346,  2346,  2348,
    2348,  2353,  2353,  2357,  2357,  2361,  2361,  2367,  2367,  2372,
    2378,  2379,  2391,  2402,  2410,  2417,  2429,  2431,  2435,  2436,
    2453,  2455,  2456,  2457,  2458,  2459,  2460,  2461,  2462,  2463,
    2464,  2465,  2466,  2467,  2468,  2469,  2470,  2471,  2473,  2475,
    2477,  2485,  2487,  2495,  2496,  2500,  2502,  2503,  2504,  2505,
    2506,  2507,  2508,  2509,  2510,  2511,  2512,  2513,  2514,  2515,
    2516,  2517,  2518,  2520,  2522,  2524,  2532,  2534,  2542,  2545,
    2547,  2551,  2552,  2558,  2559,  2565,  2567,  2571,  2573,  2575,
    2577,  2579,  2581,  2583,  2585,  2590,  2595,  2597,  2599,  2604,
    2609,  2611,  2619,  2628,  2630,  2635,  2640,  2642,  2650,  2659,
    2660,  2670,  2676,  2681,  2687,  2693,  2695,  2699,  2703,  2707,
    2711,  2715,  2720,  2726,  2728,  2730,  2735,  2740,  2746,  2753,
    2758,  2765,  2766,  2773,  2774,  2781,  2793,  2799,  2800,  2801,
    2805,  2819,  2823,  2832,  2838,  2841,  2861,  2862,  2879,  2887,
    2890,  2892,  2898,  2897,  2908,  2918,  2930,  2942,  2948,  2949,
    2953,  2954,  2956,  2960,  2965,  2970,  2972,  2985,  2987,  2993,
    3016,  3022,  3030,  3031
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "EOFTOK", "error", "\"invalid token\"", "ASM", "AUTO", "BREAK", "CASE",
  "CONTINUE", "DEFAULT", "DELETE", "DO", "ELSE", "ENUM", "FOR", "FORTRAN",
  "FRIEND", "GOTO", "IF", "NEW", "OPERATOR", "RETURN", "SIZEOF", "SWITCH",
  "THIS", "WHILE", "LP", "RP", "LB", "RB", "REF", "DOT", "NOT", "COMPL",
  "MUL", "AND", "PLUS", "MINUS", "LT", "GT", "ER", "OR", "ANDAND", "OROR",
  "QUEST", "COLON", "ASSIGN", "CM", "SM", "LC", "RC", "ID", "STRING",
  "ICON", "FCON", "CCON", "NAME", "ZERO", "ASOP", "RELOP", "EQUOP",
  "DIVOP", "SHIFTOP", "ICOP", "TYPE", "CATCH", "THROW", "TRY", "TNAME",
  "EMPTY", "NO_ID", "NO_EXPR", "FDEF", "ELLIPSIS", "AGGR", "MEM", "MEMPTR",
  "PR", "MEMQ", "TSCOPE", "DECL_MARKER", "REFMUL", "LDOUBLE", "LINKAGE",
  "TEMPLATE", "XVIRT", "XNLIST", "XILINE", "XIA", "SM_PARAM", "PTNAME",
  "NEW_INIT_KLUDGE", "XDELETED_NODE", "DUMMY_LAST_NODE", "$accept",
  "ext_def", "template", "$@1", "$@2", "$@3", "template_def", "identifier",
  "external_def", "fct_dcl", "att_fct_def", "@4", "fct_def", "@5",
  "inline_fct_def", "$@6", "check_inline", "base_init", "$@7", "init_list",
  "binit", "arg_dcl_list", "dl", "$@8", "$@9", "decl_list", "data_dcl",
  "lt", "gt", "tname", "tp", "type", "cm", "temp_inst_parms", "new_decl2",
  "new_type2", "temp_inst_parm", "enumtag", "enum_dcl", "$@10", "$@11",
  "moe_list", "template_parm_list", "template_parm", "formal_decl", "moe",
  "$@12", "class_dcl", "$@13", "inline_mem_defs", "base_list",
  "base_unit_list", "base_unit", "class_head", "tag", "ttag",
  "cl_mem_list", "cl_mem", "fname", "oper", "scope_qualifiers", "tn_list",
  "qualified_tname", "fct_attributes", "type_list", "decl", "arg_decl",
  "new_decl", "cast_decl", "c_decl", "stmt_list", "caselab_stmt",
  "caselablist", "condition", "block", "$@14", "simple", "$@15", "sm",
  "$@16", "statement", "$@17", "$@18", "@19", "@20", "$@21", "@22",
  "handler_list", "handler", "exception_type", "elist", "ex_list",
  "initializer", "ee", "e", "term", "dtorspec", "term_elist", "ptname",
  "tscope", "prim", "cast_type", "term_lp", "c_tp", "c_type", "new_type",
  "arg_type", "$@23", "arg_lp", "arg_list", "arg_type_list", "at",
  "ellipsis_opt", "ptr", "vec", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-578)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-400)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     794,  -578,     6,   528,  1279,  -578,    -4,    13,    46,  -578,
    -578,    56,   107,  -578,  -578,  1411,  -578,    89,  -578,  -578,
     109,  -578,   107,   179,  -578,  -578,  -578,  -578,  -578,  -578,
     212,  -578,  1695,  -578,  -578,  -578,  -578,    32,   278,   107,
     657,   -54,  -578,  2413,  2366,   140,  -578,  -578,  -578,   136,
    -578,   422,  -578,   158,  -578,  -578,   185,   254,  -578,  -578,
    -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,
    -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,
    -578,  -578,  -578,   280,  1195,  -578,  -578,  -578,  -578,   130,
    -578,  1486,  -578,  -578,   133,   107,  -578,  -578,   255,  1486,
    -578,  1075,  1598,  -578,  1198,  -578,  -578,  1598,  -578,    29,
    -578,  -578,  -578,   207,   212,  -578,  -578,   280,   689,  1133,
     294,  -578,  -578,  -578,  -578,  1486,   282,  1548,  -578,  1198,
    1342,  -578,  -578,   270,  -578,   212,   436,  -578,   212,   242,
     324,   312,  -578,  -578,  -578,  -578,  -578,  -578,  -578,    -8,
    -578,  -578,  1926,   811,  1279,  2126,  -578,  -578,  2126,  2126,
    2126,  2126,  2126,  2126,  -578,  -578,  -578,  -578,  -578,  -578,
    2126,   339,  2126,    28,  -578,   345,  1811,   118,  -578,  -578,
      30,    34,  2978,    23,  -578,  -578,  2126,  1486,  1362,   364,
    1486,  -578,   118,  -578,  2176,  2226,  1548,   339,  2413,   345,
     223,   358,   372,  -578,  2920,  2537,  -578,  1753,   278,  -578,
     -32,  -578,  2920,  -578,  2376,  -578,  -578,  1198,  -578,   377,
    -578,  -578,   379,   385,  -578,  -578,    32,   130,   118,  -578,
     398,   249,  -578,  1695,   423,  -578,  -578,   407,   411,   234,
    -578,   312,  -578,   383,  1598,   448,    23,  1863,  -578,  1414,
    -578,  -578,  -578,    23,  2276,    23,    23,    23,    23,    23,
      23,    23,  1548,    23,  1976,   811,  1548,  -578,   453,   108,
     757,  -578,  -578,  -578,  1486,  -578,   531,  1598,  1598,  1598,
    1598,  1598,  1598,  1598,  1598,  1598,  1598,  1598,  1598,  1598,
    1598,  1598,  1598,  1598,  1598,  1598,  1548,  1598,    37,   366,
    -578,    23,  1838,  2436,  -578,   997,  1832,  -578,   428,  -578,
    -578,  -578,   118,  1212,  -578,    57,   451,   456,   443,   444,
    -578,  1548,  -578,  -578,   392,   135,   829,    16,  -578,   469,
    1598,  -578,   692,  1548,   356,  -578,  -578,  -578,  -578,   455,
    -578,  -578,    57,  -578,  -578,  -578,   468,  -578,  -578,   472,
     312,  -578,   265,  2573,   262,    -8,   484,   492,  1598,    23,
    -578,  1414,  -578,   503,  -578,  -578,   512,   453,  -578,  -578,
    -578,   454,  3188,    12,    12,   330,   330,  3151,  1658,  3103,
    3065,  2746,  2920,  2920,  2920,   330,  1141,   454,   224,  -578,
     510,  2609,   644,   476,    43,    10,   197,  -578,  -578,   336,
     105,  -578,  -578,   465,   518,   759,  -578,  1693,  -578,  1693,
    -578,  1362,   133,  1434,  1780,   210,  -578,  -578,   530,   533,
     533,  -578,   533,  -578,  -578,  -578,  -578,   602,  -578,   453,
    -578,  -578,  -578,  2920,  -578,  -578,  -578,   468,   482,  -578,
    -578,   508,  1598,  -578,  -578,  2126,  -578,   262,   811,  -578,
    2645,   535,  -578,  -578,  1598,  -578,  -578,  -578,  -578,   527,
     838,  -578,  -578,  -578,  -578,  1814,  -578,  -578,  -578,  -578,
     649,  -578,  -578,   262,  -578,  -578,  -578,   519,   298,  -578,
     163,  -578,   453,   806,   611,  -578,  1212,   590,  -578,  -578,
    -578,  1548,  -578,    57,   508,  -578,  -578,   576,   916,  -578,
    2920,    23,  -578,  1198,  -578,  2126,   811,  3007,  1857,  -578,
    -578,  -578,  -578,   453,  -578,  -578,  -578,   778,   453,  1722,
    -578,  -578,   117,  -578,  -578,   468,  1548,   526,  -578,   554,
     538,  -578,  -578,    23,  -578,  -578,  -578,  -578,  -578,  -578,
    -578,  -578,  -578,  -578,  -578,  -578,   537,  -578,   590,   508,
     556,   576,  1548,  -578,   -26,  -578,  -578,  -578,  -578,  -578,
     563,  -578,  -578,  -578,  1003,  -578,   565,  -578,  -578,  -578,
     553,  2026,  -578,   579,   558,   588,  1598,  -578,   588,  -578,
     572,    14,  2126,   508,   574,   217,  -578,  -578,  -578,  -578,
    -578,  2891,    23,   571,  1598,  -578,  1598,    23,  -578,  -578,
    -578,  1598,  -578,  2775,   588,  -578,  -578,   508,    23,  -578,
    -578,  2076,  -578,   585,  1648,  1648,  1648,  1648,  1648,  1648,
    1648,  1648,  1648,  1648,  1648,  1648,  1648,  1648,  1648,  1648,
    1648,  1648,  1648,   608,  2804,  -578,  2681,   615,  -578,  2472,
     630,  -578,  -578,  -578,  -578,  -578,   578,  -578,  1598,    23,
    -578,   568,  3197,   115,   115,   924,   924,  3180,  3142,  3113,
    3074,  2833,  2949,  2949,  2949,   924,  1350,   568,   342,  -578,
    -578,  -578,  -578,  2126,   588,  1598,  -578,  -578,  -578,  -578,
     626,  -578,  -578,  2717,  1648,  -578,    23,  -578,  2862,  -578,
     595,   508,  1198,  2126,  3036,  1598,   634,  -578,  1753,    23,
    2501,  -578,   790,  -578,  -578,  -578
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     4,     0,     0,     0,   394,     0,   403,   404,     3,
       6,   143,     0,    61,   177,     0,   378,   409,   377,    67,
      62,     8,     0,     0,     7,     2,    22,    20,    21,    19,
      63,    68,     0,    66,    65,   133,   192,     0,   173,    58,
      45,     0,   174,     0,     0,     0,    88,   128,    86,    92,
      85,     0,   129,     0,   169,   168,     0,     0,   170,   163,
     164,   149,   150,   147,   148,   157,   158,   152,   151,   159,
     160,   167,   171,   166,   156,   154,   155,   153,   165,   385,
     172,   386,   145,     0,   216,   146,   144,   405,   407,     0,
      56,   320,   125,   113,   111,   129,   411,     5,     0,   320,
       1,   320,   320,   413,   399,   185,   198,   320,    55,   143,
      69,    73,    52,     0,    70,    72,    71,   173,    45,     0,
     143,   194,   176,    64,   175,   320,   394,   320,    25,    36,
     320,   183,   199,   408,   379,     0,     0,   406,   197,   196,
       0,   108,    90,    87,   161,   162,   387,   388,   389,   216,
     143,   193,     0,     0,     0,     0,   360,   384,     0,     0,
       0,     0,     0,     0,   380,   358,   356,   357,   359,   355,
       0,    61,     0,   378,    62,    63,    77,     0,    83,    76,
       0,   173,    84,   318,   353,   349,     0,   320,     0,     0,
     320,     9,     0,   178,     0,     0,   320,     0,     0,     0,
     173,     0,   265,   266,   268,     0,    63,   203,     0,   398,
     400,   397,    49,    47,     0,    54,    50,    36,   109,     0,
     134,   140,   139,   138,   135,   132,     0,     0,     0,   178,
       0,    30,    44,     0,     0,   410,   200,     0,   105,     0,
      93,   108,   217,     0,   320,   378,   314,   208,   321,   320,
     322,   381,   382,   334,   335,   331,   332,   327,   328,   330,
     329,   333,   320,   319,     0,     0,   320,    70,    82,    77,
      77,    57,    74,    60,   320,   350,     0,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,     0,     0,
     325,   326,   211,     0,   130,     0,     0,   131,   116,   118,
     120,   126,     0,    97,   376,   190,   380,   380,     0,     0,
     189,   320,   412,   201,   391,   203,   203,   399,   401,     0,
     320,    53,    46,   320,    26,   114,   141,   136,   137,   194,
     195,    59,   184,    24,    32,    33,    39,   186,    23,     0,
     108,    89,     0,     0,   390,   208,     0,     0,   320,   316,
     323,   320,   324,     0,    80,    81,     0,    79,    75,   352,
     351,   298,   299,   296,   297,   306,   307,   301,   300,   308,
     309,     0,   295,   311,   310,   305,   303,   304,   302,   313,
       0,     0,     0,     0,     0,     0,   173,   340,   337,     0,
       0,   346,   343,   211,     0,   211,   354,     0,   122,     0,
     121,     0,   112,     0,     0,     0,    96,   179,     0,     0,
       0,   269,     0,   267,   392,   206,   205,     0,   202,   204,
     402,   396,   178,    48,    51,    28,    29,    39,   110,   142,
      37,     0,   320,    94,    91,     0,   210,   209,     0,   369,
       0,     0,   370,    78,   320,   375,   336,   364,   361,     0,
       0,   339,   338,   342,   341,     0,   345,   344,   348,   347,
       0,   383,   213,   212,   124,   123,   119,     0,   128,    98,
     129,   100,    99,     0,     0,    10,     0,     0,   187,   188,
     191,   320,   207,   395,     0,    34,   115,     0,     0,    31,
     107,   315,   371,     0,   372,     0,     0,   312,     0,   366,
     362,   368,   367,     0,   127,   103,   102,     0,   101,     0,
      95,   181,     0,   393,    27,    39,   320,    38,    40,     0,
       0,   226,   218,   317,   373,   374,   363,   365,   214,   215,
     104,    11,    15,    13,    14,    12,    65,   180,     0,     0,
       0,     0,   320,   227,   222,    16,   182,    35,    42,    41,
       0,   225,   219,   220,     0,    43,     0,   229,   255,   230,
       0,     0,   232,     0,     0,     0,   320,   249,     0,   238,
     380,    61,     0,     0,   177,   378,   242,   241,   243,   235,
     221,   228,   293,     0,   320,   257,   320,   289,   222,   247,
     231,   320,   222,     0,     0,   222,   251,     0,   294,   260,
     253,     0,   237,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   222,     0,     0,   222,     0,
     244,   239,   222,   246,   222,   240,   259,   222,   320,   291,
     236,   273,   274,   271,   272,   282,   281,   276,   275,   283,
     284,     0,   270,   286,   285,   280,   278,   279,   277,   288,
     234,   222,   258,     0,     0,   320,   223,   222,   250,   252,
       0,   261,   254,     0,     0,   256,   290,   233,     0,   245,
     394,     0,     0,     0,   287,   320,     0,   262,   203,   292,
       0,   264,     0,   222,   263,   248
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -578,  -578,   543,  -578,  -578,  -578,  -578,  -578,  -578,  -113,
    -114,  -578,  -111,  -578,  -578,  -578,   460,  -418,  -578,  -578,
     119,   569,   457,  -578,  -578,  -578,     2,   201,  -174,    74,
    -578,   166,  -578,   -87,   172,  -578,   415,  -578,   -15,  -578,
    -578,   450,  -578,   211,    40,   343,  -578,   -25,  -578,  -578,
     289,  -578,   295,  -578,    44,  -272,  -578,  -578,   -21,   555,
      96,     0,    55,  -216,  -578,    -2,  -316,   357,   -63,   564,
    -578,    61,  -578,  -577,  -433,  -578,  -578,  -578,  -578,  -578,
    -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,  -578,
     334,  -578,   -91,  1752,   466,   616,   416,  -578,   102,   151,
      39,  -133,  -118,  -578,   570,  -254,  -578,  -578,   127,   106,
    -578,   402,  -578,   244,   208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    23,    24,    98,   313,   519,   541,   479,    25,    26,
      27,   437,    28,   346,   496,   525,   231,   441,   497,   527,
     528,   129,   112,   330,   333,   113,   232,   190,   273,   199,
      31,   176,   274,   177,   268,   178,   179,    49,    33,   141,
     241,   239,   415,   416,   482,   240,   349,    34,   335,   438,
     189,   308,   309,    35,    94,   310,   119,   225,    36,    82,
     180,   200,    39,   315,   522,    40,   324,   354,   404,   148,
     554,   563,   564,   602,   499,   532,   589,   598,   612,   613,
     590,   638,   604,   644,   647,   594,   635,   646,   681,   691,
     201,   202,   203,   591,   204,   183,   397,   184,    53,    42,
     185,   186,   187,    84,    85,   250,   209,   491,   104,   131,
     210,   211,   329,    44,   132
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      38,   605,    29,    51,    83,   222,   221,   116,   223,   427,
     429,   362,   192,   342,   327,    83,   121,   115,   314,   494,
     248,   133,   254,   561,   134,     7,     8,   642,     3,   154,
     118,    45,   117,   408,   410,   249,   230,   264,   228,   262,
     328,   136,   139,   117,   117,   277,   265,    50,   296,   154,
     297,     4,   298,   299,   341,   137,   154,   562,    52,    89,
     164,   524,   154,    86,     6,   607,   276,    17,   151,   392,
      95,    12,   293,   213,    30,   460,    87,   463,    81,    13,
     164,    22,   120,    14,    83,   300,    89,   164,   430,    15,
      16,   181,   295,   164,    18,    19,    37,   687,   174,   181,
     393,   122,    41,   312,   208,    22,   114,   549,    16,    88,
     461,    16,    18,   123,   394,    18,   557,   135,   138,    38,
     417,   224,   418,    22,   154,   181,    22,    43,    37,   208,
     181,   588,   360,     5,    41,   474,   105,   475,   412,    37,
      37,     7,     8,   547,    90,    41,    41,   361,   614,     4,
     609,   116,    96,   208,    83,   164,   271,    97,   147,    43,
       5,   115,     6,   548,   272,   175,    32,   130,     7,     8,
      43,    43,   468,   175,   645,   630,    83,   188,   206,   100,
     150,  -117,   116,    17,   142,   323,    41,   181,    83,   124,
     181,   140,   115,    30,   504,   632,   319,    22,   117,   175,
      90,   -18,   124,   206,   175,   339,   340,    83,   116,   -18,
      17,   144,   332,    91,   117,   226,   493,   208,   115,   275,
     105,    41,   116,    99,    22,   529,   611,   206,    81,   465,
     423,   332,   115,   117,   124,   265,   134,   101,   106,   102,
     125,   105,   434,   103,   105,   130,    43,    83,   485,   181,
     267,   243,   535,   214,   215,   276,   486,   277,   697,   279,
     280,   175,   307,   130,   175,   208,   130,   126,   124,   102,
     207,    16,   135,   103,   181,    18,    83,   116,    41,   529,
     350,   267,   145,   351,   293,    32,    22,   115,   135,   102,
     122,   206,   191,   103,    37,   233,   207,    16,   396,   396,
      41,    18,    83,   269,   295,    83,    83,   114,   229,    41,
      37,   350,    22,   208,   444,   502,    41,   344,   345,   247,
     370,   267,   106,   175,   227,    43,    83,   208,   149,    37,
     503,    52,   124,   235,   325,    41,   -17,   398,   402,   206,
     470,    43,   473,   106,   -17,   122,   106,   122,   175,    41,
     237,   124,    16,   302,    16,   154,    18,   123,    18,   124,
      43,   181,   238,   277,   262,   279,   280,    22,   460,    22,
     266,   243,   243,   534,   364,   614,   267,   616,   617,   307,
     307,   428,   702,   233,   320,   154,   164,   206,   503,   116,
     293,   294,    83,   149,   395,   400,   269,   269,   392,   115,
     523,   206,   630,   466,    41,   543,   542,    83,   544,    83,
     295,    83,   311,    83,    83,   302,   164,     5,   321,   102,
     270,   336,   632,   103,   435,   436,   337,   243,    41,   393,
     425,   247,   338,   462,   464,   175,   458,   424,   467,   469,
      16,   366,   367,   399,    18,   343,   130,    52,   208,   347,
     586,   326,   325,   325,   348,    22,  -106,   243,   133,   130,
      83,   126,   236,   102,   234,    83,   265,   103,   480,   126,
     422,   102,   364,   364,   411,   103,   365,   419,     5,   414,
     102,   307,   420,   307,   103,   307,   208,    83,   267,   122,
     403,   355,   421,   207,   546,   432,    16,    83,     7,     8,
      18,   143,   439,   208,   510,   243,   208,   243,    83,   512,
     448,    22,   440,   270,   270,    52,    41,   442,   449,    38,
      52,   545,   206,   517,   518,   488,   489,   302,   490,   452,
     318,   521,   426,   425,   295,   425,   455,     5,   453,   102,
      17,   483,    52,   103,   471,   102,   405,   124,    83,   103,
     459,    83,   537,   495,    22,   487,   498,   182,     5,   508,
     206,   506,   446,    52,   181,   182,   587,   514,   205,   326,
     326,   307,   551,   212,   365,   365,    46,   206,    47,   552,
     206,    47,   558,   356,   555,   243,   243,   553,   515,   565,
     593,   182,   556,    30,   369,    14,   357,   595,    14,   355,
     363,   526,    16,    52,   599,    16,    18,    48,   600,    18,
     483,   483,   472,   601,   247,    37,   606,    22,   610,   538,
      22,    41,   633,   515,   515,   307,   304,     5,   492,   102,
     390,    12,   650,   103,   670,   426,     5,   426,   175,   674,
      47,   677,   680,    14,     7,     8,    43,   405,   632,   405,
      16,   690,   414,   303,    18,   446,   182,    14,   484,   637,
     701,   481,   220,   640,    16,    22,   643,   696,    18,   302,
     559,   331,   247,   116,   137,   513,   102,   334,   472,    22,
     103,   472,   126,   115,   102,    32,    17,   217,   103,   368,
     516,   352,   208,   443,    47,   451,   672,   520,    83,   675,
      22,   477,   127,   678,   128,   679,   476,   457,   682,   251,
     353,    14,   447,   242,   126,   401,   102,   126,    16,   102,
     103,   539,    18,   103,   252,   516,   516,   484,   484,   431,
      32,     0,   685,    22,   216,   -46,   -46,   216,   689,     0,
     182,     0,     0,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,     0,   391,   705,     0,   206,     0,   246,     0,
       0,   253,   267,     0,   255,   256,   257,   258,   259,   260,
       0,     0,     5,     0,   403,     0,   261,     0,   263,     0,
       7,     8,     7,     8,     1,     0,   433,     2,     0,     0,
      41,     0,   301,     5,   540,   102,     3,   692,   425,   103,
     257,   258,     0,     4,     0,     5,   704,   102,     0,     5,
     137,   103,   137,     3,   450,   325,     6,     7,     8,     0,
       0,     5,    17,     0,    17,     0,   157,     0,     0,     7,
       8,     9,     0,    10,    11,     0,    22,     0,    22,    12,
       0,     0,     0,     0,     5,     0,   481,    13,   698,     0,
     550,    14,     7,     8,     0,     0,    12,    15,    16,    17,
     301,     0,    18,    19,    13,     0,    20,    21,    14,   323,
     359,    17,     0,    22,    15,    16,   560,     0,    47,    18,
      19,     0,   137,   174,     0,    22,    14,     0,     0,     0,
      22,   509,     0,    16,    17,    14,     0,    18,   500,     0,
     426,     0,    16,     0,     0,     0,    18,   530,    22,  -224,
     507,  -224,  -224,  -224,  -224,  -224,  -224,    22,  -224,  -224,
       0,     0,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,   326,     0,     0,     0,     0,  -224,  -224,  -224,
    -224,  -224,  -224,     0,     0,     0,     0,   614,     0,   616,
     617,     0,     0,  -224,  -224,   531,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,     0,     0,     0,     0,     0,  -224,  -224,
       0,  -224,  -224,  -224,   630,   631,     0,     0,     0,  -224,
    -224,     0,     0,     0,  -224,  -224,     0,     0,  -224,  -224,
       0,     0,     0,     0,   632,  -224,   566,     0,   567,   568,
     569,   570,   571,   572,     0,     3,   573,     0,     0,   574,
     575,   153,   154,   576,   155,   577,   156,   578,   157,     0,
       0,     0,     0,     0,   158,   159,   160,   161,   162,   163,
       0,     0,   603,     0,     0,     0,     0,   304,     0,     0,
     579,   498,    12,   580,   165,   166,   167,   168,    12,   169,
     634,   501,   636,     0,    14,   170,   581,   639,   582,   583,
     584,    16,     0,   407,     0,    18,    15,   585,     0,     0,
       0,    18,    19,     0,   152,   174,    22,  -394,     0,     0,
       0,     0,    22,   153,   154,     0,   155,     0,   156,     0,
     157,   193,     0,     0,     0,     0,   158,   159,   194,   195,
     162,   163,     0,     0,   683,     0,     0,     0,     0,     0,
       0,   533,     0,   196,     0,   164,   165,   166,   167,   168,
      12,   169,     0,     0,     0,     0,     0,   170,  -394,     0,
     172,   688,  -394,     0,     0,     3,     0,  -394,  -394,  -394,
     198,     0,     4,  -394,  -394,     0,     0,  -394,     5,     0,
       0,   700,     0,     0,    22,     6,     7,     8,     0,     0,
       0,     0,     0,     0,   277,     0,   279,   280,   281,   282,
     592,     0,   218,    11,     0,     0,     0,   597,    12,     0,
       0,     0,     0,     0,     0,     0,    13,     0,   608,   291,
      14,   293,   294,     0,     0,     0,    15,    16,    17,   219,
       3,    18,    19,     0,     0,   174,    21,     0,     0,     0,
       0,   295,    22,     0,     3,     0,     0,   649,     7,     8,
     592,   592,   592,   592,   592,   592,   592,   592,   592,   592,
     592,   592,   592,   592,   592,   592,   592,   592,   592,     0,
      12,     0,     0,    12,     0,     0,     0,     0,   146,     0,
       0,    13,    14,     0,     0,    14,     0,    12,     0,    16,
      17,    15,    16,    18,     0,    13,    18,    19,     0,    14,
     174,     0,     0,     0,    22,   413,    16,    22,    54,   686,
      18,    19,     0,     0,   174,     0,     0,    55,     0,     0,
     592,    22,     0,     0,    56,     0,    57,     0,    58,   699,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     0,     0,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,    14,     0,     0,     0,
       0,   152,     0,    16,     3,     0,     0,    18,     0,    80,
     153,   154,     0,   155,     0,   156,     0,   157,    22,     0,
       0,     0,     0,   158,   159,   160,   161,   162,   163,     0,
       0,     0,     0,   614,     0,   616,   617,   618,   619,     0,
     196,     0,   164,   165,   166,   167,   168,    12,   169,     0,
       0,     0,     0,     0,   170,   171,     0,   172,   628,    14,
     630,   631,   304,     0,  -399,    15,   173,    12,     0,     0,
      18,    19,     0,   152,   174,   305,     3,     0,     0,    14,
     632,    22,   153,   154,     0,   155,    16,   156,   306,   157,
      18,     0,     0,     0,     0,   158,   159,   160,   161,   162,
     163,    22,     0,     0,     0,     0,     0,     0,     0,    92,
       0,    47,   196,     0,   164,   165,   166,   167,   168,    12,
     169,     0,     0,     0,     0,     0,   170,   171,    14,   172,
       0,    14,    92,     0,   478,    16,     0,    15,   173,    18,
      93,     0,    18,    19,     0,   152,   174,     0,     3,     0,
      22,    14,     0,    22,   153,   154,     0,   155,    16,   156,
       0,   157,    18,    93,     0,     0,     0,   158,   159,   160,
     161,   162,   163,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   171,
       0,   172,     0,    14,     0,     0,     0,   152,     0,    15,
     173,     0,     0,     0,    18,    19,   153,   154,   174,   155,
       0,   156,     0,   157,     0,    22,     0,     0,     0,   158,
     159,   160,   161,   162,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   196,     0,   164,   165,
     166,   167,   168,    12,   169,     0,     0,   152,     0,     0,
     170,   197,     0,   172,     0,    14,   153,   154,     0,   155,
       0,   156,   173,   157,     0,     0,    18,     0,     0,   158,
     159,   160,   161,   162,   163,     0,     0,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,    12,   169,     0,     0,   571,     0,     0,
     170,   197,     0,   172,     0,    14,   153,   154,     0,   155,
       0,   156,   173,   157,     0,     0,    18,     0,     0,   158,
     159,   160,   161,   162,   163,     0,     0,    22,     0,     0,
       0,   277,   278,   279,   280,   281,   282,   283,   164,   165,
     166,   167,   168,    12,   169,     0,     0,     3,     0,     0,
     170,   197,     0,   582,     4,    14,   291,   292,   293,   294,
       5,     0,   585,     0,     0,     0,    18,     6,     7,     8,
       0,     0,     0,     0,     3,     0,     0,    22,   295,   107,
       0,     4,   108,   304,     0,   109,     0,     5,    12,     0,
      12,     0,     0,     0,     6,     7,     8,     0,   110,     0,
      14,     0,    14,     0,     0,     3,     0,    16,    15,    16,
      17,    18,    11,    18,   111,     0,     0,    12,     5,     0,
       0,     0,    22,     0,    22,    13,     7,     8,     0,    14,
       0,     0,     3,     0,     0,    15,    16,    17,     0,     0,
      18,    19,     0,   323,   174,     5,     0,     0,    12,     0,
       0,    22,     0,     7,     8,     0,   110,     0,     0,     0,
      14,     0,     0,     3,     0,     0,    15,    16,    17,     0,
     481,    18,   111,     0,     0,    12,     5,     0,     0,     0,
       0,     0,    22,   110,     7,     8,     0,    14,     0,     0,
       3,     0,     0,    15,    16,    17,     0,     0,    18,   111,
       0,     0,     0,   403,    47,     0,    12,     0,     0,    22,
       0,     7,     8,     0,   110,     3,     0,   511,    14,     0,
       0,    14,   304,     0,    15,    16,    17,    12,    16,    18,
     111,     0,    18,    12,     0,   409,     7,     8,     0,    14,
      22,   110,     0,    22,     0,    14,    16,    47,     0,     0,
      18,    15,    16,    17,     0,     0,    18,   111,    12,     0,
     536,    22,     0,     0,    14,     0,   110,    22,     0,     0,
      14,    16,     0,     0,     0,    18,    15,    16,    17,     0,
       0,    18,   111,     0,   153,   154,    22,   155,     0,   156,
       0,   157,    22,   244,     0,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,   358,    18,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,   596,    18,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,   648,    18,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,     0,    18,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,     0,    18,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   316,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,     0,    18,     0,     0,   158,   159,   160,
     161,   162,   163,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   317,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,   153,   154,     0,   155,     0,   156,
     245,   157,     0,     0,    18,     0,     0,   158,   159,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,    12,   169,     0,     0,     0,     0,     0,   170,   197,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
     245,     0,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,     4,     0,     0,     0,     0,
       0,     5,     0,     0,     0,     4,     0,     0,     6,     7,
       8,     5,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     0,     0,     0,     0,     0,    11,     0,     0,     0,
     107,    12,     0,     0,     0,     0,   109,     0,     0,   137,
       0,    12,     4,    14,     0,     0,   694,     0,     5,     0,
      16,    17,     0,    14,    18,     6,     7,     8,     0,     0,
      16,    17,     0,     0,    18,    22,     0,     0,     0,     0,
       0,     0,   406,    11,     0,    22,     0,     0,    12,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
      14,   288,   289,     0,     0,     0,     0,    16,    17,     0,
       0,    18,     0,   290,   291,   292,   293,   294,   676,     0,
       0,     0,    22,     0,     0,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   295,   288,   289,     0,
       0,     0,     0,     0,     0,     0,     0,   703,     0,   290,
     291,   292,   293,   294,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,     0,   288,   289,     0,     0,
       0,     0,   295,     0,     0,     0,     0,     0,   290,   291,
     292,   293,   294,     0,     0,   322,     0,     0,     0,     0,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   295,   288,   289,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   290,   291,   292,   293,   294,     0,
       0,   445,     0,     0,     0,     0,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   295,   288,   289,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     290,   291,   292,   293,   294,     0,     0,   456,     0,     0,
       0,     0,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   295,   288,   289,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   290,   291,   292,   293,
     294,     0,     0,   505,     0,     0,     0,     0,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   295,
     288,   289,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   290,   291,   292,   293,   294,     0,     0,   673,
       0,     0,     0,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   295,   288,   289,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   290,   291,
     292,   293,   294,     0,     0,   693,     0,     0,     0,     0,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   295,   288,   289,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   290,   291,   292,   293,   294,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     454,   288,   289,     0,     0,     0,     0,   295,     0,     0,
       0,     0,     0,   290,   291,   292,   293,   294,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,     0,
     288,   289,   641,     0,     0,     0,   295,     0,     0,     0,
       0,     0,   290,   291,   292,   293,   294,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   671,   288,
     289,     0,     0,     0,     0,   295,     0,     0,     0,     0,
       0,   290,   291,   292,   293,   294,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   684,   625,   626,
       0,     0,     0,     0,   295,     0,     0,     0,     0,     0,
     627,   628,   629,   630,   631,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,     0,   288,   289,   695,
       0,     0,     0,   632,     0,     0,     0,     0,     0,   290,
     291,   292,   293,   294,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   624,     0,   625,   626,     0,     0,
       0,     0,   295,     0,     0,     0,     0,     0,   627,   628,
     629,   630,   631,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,     0,   288,     0,     0,     0,     0,
       0,   632,     0,     0,     0,     0,     0,   290,   291,   292,
     293,   294,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,     0,   625,     0,     0,     0,     0,     0,
     295,     0,     0,     0,     0,     0,   627,   628,   629,   630,
     631,   277,   278,   279,   280,   281,     0,   283,   284,   285,
     286,   287,     0,   288,     0,     0,     0,     0,     0,   632,
       0,     0,     0,     0,     0,   290,   291,   292,   293,   294,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,     0,     0,     0,     0,     0,     0,     0,   295,     0,
       0,     0,     0,     0,     0,   291,   292,   293,   294,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
       0,     0,     0,     0,     0,     0,     0,   295,     0,     0,
       0,     0,     0,     0,   628,   629,   630,   631,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   632,     0,     0,     0,
       0,     0,     0,   291,   292,   293,   294,     0,     0,     0,
       0,     0,   628,   629,   630,   631,   277,   278,   279,   280,
     281,   282,   283,   284,     0,   295,   614,   615,   616,   617,
     618,   619,   620,   621,   632,     0,     0,     0,     0,     0,
       0,   291,   292,   293,   294,     0,     0,     0,     0,     0,
       0,   628,   629,   630,   631,   614,   615,   616,   617,   618,
     619,   620,     0,   295,   277,   278,   279,   280,   281,   282,
       0,     0,     0,   632,     0,     0,     0,     0,     0,     0,
     628,   629,   630,   631,     0,     0,     0,     0,     0,   291,
     292,   293,   294,   614,   615,   616,   617,   618,   619,     0,
       0,   277,   632,   279,   280,   281,   282,     0,     0,     0,
     614,   295,   616,   617,   618,   619,     0,     0,   628,   629,
     630,   631,     0,     0,     0,     0,   291,   292,   293,   294,
       0,     0,     0,     0,     0,   628,   629,   630,   631,     0,
     632,     0,     0,     0,     0,     0,     0,     0,   295,     0,
       0,     0,     0,     0,     0,     0,     0,   632
};

static const yytype_int16 yycheck[] =
{
       0,   578,     0,     3,     4,   119,   119,    32,   119,   325,
     326,   265,    99,   229,    46,    15,    37,    32,   192,   437,
     153,    75,   155,    49,    78,    33,    34,   604,    12,    19,
      32,    25,    32,   305,   306,   153,   127,     9,   125,    25,
      72,    43,    44,    43,    44,    33,    18,     3,    25,    19,
      27,    19,    29,    30,   228,    63,    19,    83,     3,    30,
      50,   494,    19,    67,    32,    51,    32,    75,    89,    32,
      15,    55,    60,    44,     0,    32,    63,    67,     4,    63,
      50,    89,    50,    67,    84,    62,    30,    50,    72,    73,
      74,    91,    80,    50,    78,    79,     0,   674,    82,    99,
      63,    67,     0,   190,   104,    89,    32,   525,    74,    63,
      67,    74,    78,    79,    77,    78,   549,    43,    44,   119,
      63,   119,    65,    89,    19,   125,    89,     0,    32,   129,
     130,   564,   265,    25,    32,   407,    30,   409,   312,    43,
      44,    33,    34,    26,    37,    43,    44,   265,    33,    19,
     583,   176,    63,   153,   154,    50,    38,    48,    84,    32,
      25,   176,    32,    46,    46,    91,     0,    40,    33,    34,
      43,    44,    67,    99,   607,    60,   176,    44,   104,     0,
      50,    48,   207,    75,    48,    50,    84,   187,   188,    38,
     190,    51,   207,   119,   448,    80,   198,    89,   198,   125,
      37,    38,    51,   129,   130,   226,   227,   207,   233,    46,
      75,    26,   214,    12,   214,   119,   432,   217,   233,   180,
     114,   119,   247,    22,    89,   497,     9,   153,   154,    32,
     321,   233,   247,   233,    83,    18,    78,    25,    30,    27,
      39,   135,   333,    31,   138,   118,   119,   247,    38,   249,
     176,   149,   506,    46,    47,    32,    46,    33,   691,    35,
      36,   187,   188,   136,   190,   265,   139,    25,   117,    27,
     104,    74,   198,    31,   274,    78,   276,   302,   176,   551,
      46,   207,    28,    49,    60,   119,    89,   302,   214,    27,
      67,   217,    37,    31,   198,   129,   130,    74,   298,   299,
     198,    78,   302,   176,    80,   305,   306,   233,    26,   207,
     214,    46,    89,   313,    49,   448,   214,    68,    69,   153,
     276,   247,   114,   249,    30,   198,   326,   327,    84,   233,
     448,   276,   181,    63,   207,   233,    38,   298,   299,   265,
     403,   214,   405,   135,    46,    67,   138,    67,   274,   247,
      26,   200,    74,   187,    74,    19,    78,    79,    78,   208,
     233,   361,    50,    33,    25,    35,    36,    89,    32,    89,
      25,   269,   270,   506,   268,    33,   302,    35,    36,   305,
     306,   326,   698,   217,    26,    19,    50,   313,   506,   414,
      60,    61,   392,   149,   298,   299,   269,   270,    32,   414,
     491,   327,    60,    67,   302,   519,   519,   407,   519,   409,
      80,   411,    48,   413,   414,   249,    50,    25,    46,    27,
     176,    44,    80,    31,    68,    69,    47,   325,   326,    63,
     324,   265,    47,   394,   395,   361,   392,    45,   399,   400,
      74,   269,   270,    77,    78,    47,   319,   392,   448,    26,
     564,   207,   325,   326,    47,    89,    45,   355,    75,   332,
     460,    25,    26,    27,   130,   465,    18,    31,   413,    25,
      26,    27,   366,   367,    46,    31,   268,    26,    25,   313,
      27,   407,    26,   409,    31,   411,   486,   487,   414,    67,
      25,   247,    49,   327,   519,    26,    74,   497,    33,    34,
      78,    79,    47,   503,   460,   403,   506,   405,   508,   465,
      26,    89,    44,   269,   270,   460,   414,    45,    26,   519,
     465,   519,   448,   483,   484,   419,   420,   361,   422,    26,
     196,   487,   324,   427,    80,   429,    26,    25,    26,    27,
      75,   414,   487,    31,    26,    27,   302,   396,   548,    31,
      74,   551,   508,    71,    89,    25,    48,    91,    25,    32,
     486,    26,   354,   508,   564,    99,   564,    48,   102,   325,
     326,   497,    46,   107,   366,   367,    48,   503,    50,    25,
     506,    50,    26,   249,    47,   483,   484,    49,   482,    26,
      25,   125,   548,   519,    63,    67,   262,    44,    67,   355,
     266,    25,    74,   548,    25,    74,    78,    79,    50,    78,
     483,   484,   404,    25,   448,   519,    44,    89,    44,   513,
      89,   519,    51,   517,   518,   551,    50,    25,    26,    27,
     296,    55,    47,    31,    26,   427,    25,   429,   564,    24,
      50,    11,    64,    67,    33,    34,   519,   403,    80,   405,
      74,    25,   486,   187,    78,   447,   190,    67,   414,   598,
      26,    50,   119,   602,    74,    89,   605,    72,    78,   503,
     551,   214,   506,   698,    63,    26,    27,   217,   470,    89,
      31,   473,    25,   698,    27,   519,    75,   118,    31,   274,
     482,   241,   692,   350,    50,   361,   635,   486,   698,   638,
      89,   412,    45,   642,    47,   644,   411,    63,   647,   154,
     244,    67,   355,   149,    25,   299,    27,    25,    74,    27,
      31,   513,    78,    31,   154,   517,   518,   483,   484,   327,
     564,    -1,   671,    89,    45,    46,    47,    45,   677,    -1,
     274,    -1,    -1,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,    -1,   297,   703,    -1,   692,    -1,   152,    -1,
      -1,   155,   698,    -1,   158,   159,   160,   161,   162,   163,
      -1,    -1,    25,    -1,    25,    -1,   170,    -1,   172,    -1,
      33,    34,    33,    34,     0,    -1,   330,     3,    -1,    -1,
     698,    -1,   186,    25,    26,    27,    12,   680,   702,    31,
     194,   195,    -1,    19,    -1,    25,    26,    27,    -1,    25,
      63,    31,    63,    12,   358,   698,    32,    33,    34,    -1,
      -1,    25,    75,    -1,    75,    -1,    25,    -1,    -1,    33,
      34,    47,    -1,    49,    50,    -1,    89,    -1,    89,    55,
      -1,    -1,    -1,    -1,    25,    -1,    50,    63,   692,    -1,
     526,    67,    33,    34,    -1,    -1,    55,    73,    74,    75,
     254,    -1,    78,    79,    63,    -1,    82,    83,    67,    50,
     264,    75,    -1,    89,    73,    74,   552,    -1,    50,    78,
      79,    -1,    63,    82,    -1,    89,    67,    -1,    -1,    -1,
      89,    63,    -1,    74,    75,    67,    -1,    78,   442,    -1,
     702,    -1,    74,    -1,    -1,    -1,    78,     1,    89,     3,
     454,     5,     6,     7,     8,     9,    10,    89,    12,    13,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,   698,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    33,    -1,    35,
      36,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    66,    67,    60,    61,    -1,    -1,    -1,    73,
      74,    -1,    -1,    -1,    78,    79,    -1,    -1,    82,    83,
      -1,    -1,    -1,    -1,    80,    89,     3,    -1,     5,     6,
       7,     8,     9,    10,    -1,    12,    13,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      -1,    -1,   576,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      47,    48,    55,    50,    51,    52,    53,    54,    55,    56,
     594,   445,   596,    -1,    67,    62,    63,   601,    65,    66,
      67,    74,    -1,    76,    -1,    78,    73,    74,    -1,    -1,
      -1,    78,    79,    -1,     9,    82,    89,    12,    -1,    -1,
      -1,    -1,    89,    18,    19,    -1,    21,    -1,    23,    -1,
      25,    26,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    -1,    -1,   648,    -1,    -1,    -1,    -1,    -1,
      -1,   505,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,   675,    67,    -1,    -1,    12,    -1,    72,    73,    74,
      75,    -1,    19,    78,    79,    -1,    -1,    82,    25,    -1,
      -1,   695,    -1,    -1,    89,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,
     564,    -1,    49,    50,    -1,    -1,    -1,   571,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,   582,    58,
      67,    60,    61,    -1,    -1,    -1,    73,    74,    75,    76,
      12,    78,    79,    -1,    -1,    82,    83,    -1,    -1,    -1,
      -1,    80,    89,    -1,    12,    -1,    -1,   611,    33,    34,
     614,   615,   616,   617,   618,   619,   620,   621,   622,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,    -1,
      55,    -1,    -1,    55,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    63,    67,    -1,    -1,    67,    -1,    55,    -1,    74,
      75,    73,    74,    78,    -1,    63,    78,    79,    -1,    67,
      82,    -1,    -1,    -1,    89,    73,    74,    89,     9,   673,
      78,    79,    -1,    -1,    82,    -1,    -1,    18,    -1,    -1,
     684,    89,    -1,    -1,    25,    -1,    27,    -1,    29,   693,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,     9,    -1,    74,    12,    -1,    -1,    78,    -1,    80,
      18,    19,    -1,    21,    -1,    23,    -1,    25,    89,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    -1,
      48,    -1,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    58,    67,
      60,    61,    50,    -1,    72,    73,    74,    55,    -1,    -1,
      78,    79,    -1,     9,    82,    63,    12,    -1,    -1,    67,
      80,    89,    18,    19,    -1,    21,    74,    23,    76,    25,
      78,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    50,    48,    -1,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    62,    63,    67,    65,
      -1,    67,    48,    -1,    50,    74,    -1,    73,    74,    78,
      79,    -1,    78,    79,    -1,     9,    82,    -1,    12,    -1,
      89,    67,    -1,    89,    18,    19,    -1,    21,    74,    23,
      -1,    25,    78,    79,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    67,    -1,    -1,    -1,     9,    -1,    73,
      74,    -1,    -1,    -1,    78,    79,    18,    19,    82,    21,
      -1,    23,    -1,    25,    -1,    89,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,     9,    -1,    -1,
      62,    63,    -1,    65,    -1,    67,    18,    19,    -1,    21,
      -1,    23,    74,    25,    -1,    -1,    78,    -1,    -1,    31,
      32,    33,    34,    35,    36,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,     9,    -1,    -1,
      62,    63,    -1,    65,    -1,    67,    18,    19,    -1,    21,
      -1,    23,    74,    25,    -1,    -1,    78,    -1,    -1,    31,
      32,    33,    34,    35,    36,    -1,    -1,    89,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    12,    -1,    -1,
      62,    63,    -1,    65,    19,    67,    58,    59,    60,    61,
      25,    -1,    74,    -1,    -1,    -1,    78,    32,    33,    34,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    89,    80,    44,
      -1,    19,    47,    50,    -1,    50,    -1,    25,    55,    -1,
      55,    -1,    -1,    -1,    32,    33,    34,    -1,    63,    -1,
      67,    -1,    67,    -1,    -1,    12,    -1,    74,    73,    74,
      75,    78,    50,    78,    79,    -1,    -1,    55,    25,    -1,
      -1,    -1,    89,    -1,    89,    63,    33,    34,    -1,    67,
      -1,    -1,    12,    -1,    -1,    73,    74,    75,    -1,    -1,
      78,    79,    -1,    50,    82,    25,    -1,    -1,    55,    -1,
      -1,    89,    -1,    33,    34,    -1,    63,    -1,    -1,    -1,
      67,    -1,    -1,    12,    -1,    -1,    73,    74,    75,    -1,
      50,    78,    79,    -1,    -1,    55,    25,    -1,    -1,    -1,
      -1,    -1,    89,    63,    33,    34,    -1,    67,    -1,    -1,
      12,    -1,    -1,    73,    74,    75,    -1,    -1,    78,    79,
      -1,    -1,    -1,    25,    50,    -1,    55,    -1,    -1,    89,
      -1,    33,    34,    -1,    63,    12,    -1,    63,    67,    -1,
      -1,    67,    50,    -1,    73,    74,    75,    55,    74,    78,
      79,    -1,    78,    55,    -1,    63,    33,    34,    -1,    67,
      89,    63,    -1,    89,    -1,    67,    74,    50,    -1,    -1,
      78,    73,    74,    75,    -1,    -1,    78,    79,    55,    -1,
      63,    89,    -1,    -1,    67,    -1,    63,    89,    -1,    -1,
      67,    74,    -1,    -1,    -1,    78,    73,    74,    75,    -1,
      -1,    78,    79,    -1,    18,    19,    89,    21,    -1,    23,
      -1,    25,    89,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    27,    78,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    27,    78,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    27,    78,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    -1,    78,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    -1,    78,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    -1,    78,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    18,    19,    -1,    21,    -1,    23,
      74,    25,    -1,    -1,    78,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    19,    -1,    -1,    32,    33,
      34,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      44,    55,    -1,    -1,    -1,    -1,    50,    -1,    -1,    63,
      -1,    55,    19,    67,    -1,    -1,   684,    -1,    25,    -1,
      74,    75,    -1,    67,    78,    32,    33,    34,    -1,    -1,
      74,    75,    -1,    -1,    78,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    50,    -1,    89,    -1,    -1,    55,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      67,    45,    46,    -1,    -1,    -1,    -1,    74,    75,    -1,
      -1,    78,    -1,    57,    58,    59,    60,    61,    26,    -1,
      -1,    -1,    89,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    80,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    57,
      58,    59,    60,    61,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    80,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    80,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    80,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    80,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    80,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    80,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    60,    61,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    33,    34,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    80,    33,    34,    35,    36,
      37,    38,    39,    40,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    33,    34,    35,    36,    37,
      38,    39,    -1,    80,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    33,    34,    35,    36,    37,    38,    -1,
      -1,    33,    80,    35,    36,    37,    38,    -1,    -1,    -1,
      33,    80,    35,    36,    37,    38,    -1,    -1,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     0,     3,    12,    19,    25,    32,    33,    34,    47,
      49,    50,    55,    63,    67,    73,    74,    75,    78,    79,
      82,    83,    89,    94,    95,   101,   102,   103,   105,   119,
     122,   123,   124,   131,   140,   146,   151,   153,   154,   155,
     158,   191,   192,   201,   206,    25,    48,    50,    79,   130,
     147,   154,   155,   191,     9,    18,    25,    27,    29,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    45,    46,    57,    58,    59,    60,    61,    62,    63,
      80,   122,   152,   154,   196,   197,    67,    63,    63,    30,
      37,   120,    48,    79,   147,   155,    63,    48,    96,   120,
       0,    25,    27,    31,   201,   202,   207,    44,    47,    50,
      63,    79,   115,   118,   122,   131,   140,   154,   158,   149,
      50,   151,    67,    79,   192,   120,    25,    45,    47,   114,
     201,   202,   207,    75,    78,   122,   158,    63,   122,   158,
      51,   132,    48,    79,    26,    28,    63,   122,   162,   206,
      50,   151,     9,    18,    19,    21,    23,    25,    31,    32,
      33,    34,    35,    36,    50,    51,    52,    53,    54,    56,
      62,    63,    65,    74,    82,   122,   124,   126,   128,   129,
     153,   154,   187,   188,   190,   193,   194,   195,    44,   143,
     120,    37,   126,    26,    33,    34,    48,    63,    75,   122,
     154,   183,   184,   185,   187,   187,   122,   124,   154,   199,
     203,   204,   187,    44,    46,    47,    45,   114,    49,    76,
      95,   102,   103,   105,   119,   150,   153,    30,   126,    26,
     185,   109,   119,   124,   183,    63,    26,    26,    50,   134,
     138,   133,   162,   191,    27,    74,   188,   124,   194,   195,
     198,   152,   197,   188,   194,   188,   188,   188,   188,   188,
     188,   188,    25,   188,     9,    18,    25,   122,   127,   201,
     206,    38,    46,   121,   125,   193,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    45,    46,
      57,    58,    59,    60,    61,    80,    25,    27,    29,    30,
      62,   188,   124,   187,    50,    63,    76,   122,   144,   145,
     148,    48,   126,    97,   121,   156,    50,    50,   183,   158,
      26,    46,    28,    50,   159,   201,   206,    46,    72,   205,
     116,   115,   158,   117,   109,   141,    44,    47,    47,   151,
     151,   121,   156,    47,    68,    69,   106,    26,    47,   139,
      46,    49,   134,   187,   160,   206,   183,   183,    27,   188,
     194,   195,   198,   183,   202,   207,   127,   127,   129,    63,
     147,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     183,   187,    32,    63,    77,   153,   154,   189,   193,    77,
     153,   189,   193,    25,   161,   206,    26,    76,   148,    63,
     148,    46,   121,    73,   124,   135,   136,    63,    65,    26,
      26,    49,    26,   185,    45,   202,   207,   159,   155,   159,
      72,   204,    26,   187,   185,    68,    69,   104,   142,    47,
      44,   110,    45,   138,    49,    28,   207,   160,    26,    26,
     187,   183,    26,    26,    44,    26,    28,    63,   147,    74,
      32,    67,   193,    67,   193,    32,    67,   193,    67,   193,
     161,    26,   207,   161,   148,   148,   145,   143,    50,   100,
     155,    50,   137,   201,   206,    38,    46,    25,   202,   202,
     202,   200,    26,   156,   110,    71,   107,   111,    48,   167,
     187,   188,   194,   195,   198,    28,    26,   187,    32,    63,
     147,    63,   147,    26,    48,   202,   207,   137,   137,    98,
     136,   147,   157,   185,   167,   108,    25,   112,   113,   148,
       1,    49,   168,   188,   194,   198,    63,   147,   202,   207,
      26,    99,   102,   103,   105,   119,   140,    26,    46,   110,
     183,    46,    25,    49,   163,    47,   147,   167,    26,   113,
     183,    49,    83,   164,   165,    26,     3,     5,     6,     7,
       8,     9,    10,    13,    16,    17,    20,    22,    24,    47,
      50,    63,    65,    66,    67,    74,   103,   119,   167,   169,
     173,   186,   188,    25,   178,    44,    27,   188,   170,    25,
      50,    25,   166,   187,   175,   166,    44,    51,   188,   167,
      44,     9,   171,   172,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    45,    46,    57,    58,    59,
      60,    61,    80,    51,   187,   179,   187,   164,   174,   187,
     164,    47,   166,   164,   176,   167,   180,   177,    27,   188,
      47,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
      26,    44,   164,    28,    24,   164,    26,    11,   164,   164,
      64,   181,   164,   187,    44,   164,   188,   166,   187,   164,
      25,   182,   201,    28,   186,    47,    72,   167,   124,   188,
     187,    26,   159,    26,    26,   164
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    94,    94,    94,    94,    94,    96,    97,
      98,    95,    99,    99,    99,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   102,   102,   104,   103,   103,   103,
     106,   105,   105,   105,   108,   107,   109,   111,   110,   110,
     112,   112,   113,   113,   114,   114,   115,   116,   115,   115,
     117,   115,   118,   118,   119,   119,   120,   121,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   125,   126,   126,   127,   127,   127,
     127,   127,   128,   129,   129,   130,   130,   130,   132,   131,
     133,   131,   131,   134,   134,   135,   135,   135,   136,   136,
     137,   137,   137,   137,   137,   138,   139,   138,   138,   141,
     140,   140,   140,   140,   142,   142,   143,   143,   144,   144,
     145,   145,   145,   145,   145,   146,   146,   146,   147,   147,
     148,   148,   149,   149,   149,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   151,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   153,   154,   154,   155,   155,   156,   156,
     156,   157,   157,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   159,   159,   159,   159,   159,   159,   160,   160,
     160,   161,   161,   161,   161,   161,   162,   162,   163,   163,
     163,   164,   165,   166,   168,   167,   167,   167,   169,   169,
     169,   169,   170,   169,   169,   172,   171,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   174,   173,   175,
     173,   176,   173,   177,   173,   178,   173,   179,   173,   173,
     180,   180,   181,   182,   182,   183,   184,   184,   185,   185,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   189,   189,   189,   189,   189,   189,   189,   189,   190,
     190,   190,   190,   190,   190,   190,   191,   192,   192,   192,
     193,   193,   193,   194,   195,   196,   196,   196,   196,   197,
     198,   199,   200,   199,   201,   202,   203,   203,   204,   204,
     205,   205,   205,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   207,   207
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     0,     0,
       0,     8,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     0,     7,     5,     5,
       0,     6,     4,     4,     0,     4,     0,     0,     3,     0,
       1,     3,     3,     4,     2,     0,     1,     0,     4,     2,
       0,     4,     1,     3,     3,     2,     1,     1,     1,     4,
       4,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     1,     3,     1,     0,     3,     2,
       2,     2,     2,     1,     1,     1,     1,     2,     0,     5,
       0,     6,     2,     1,     3,     3,     1,     0,     2,     2,
       1,     2,     2,     2,     3,     1,     0,     4,     0,     0,
       5,     2,     5,     2,     0,     2,     2,     0,     1,     3,
       1,     2,     2,     3,     3,     2,     4,     7,     1,     1,
       1,     1,     2,     0,     2,     1,     2,     2,     1,     1,
       1,     2,     3,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     0,     2,
       5,     1,     3,     2,     4,     2,     4,     6,     6,     4,
       4,     6,     1,     3,     2,     4,     2,     2,     2,     2,
       3,     1,     2,     0,     2,     2,     2,     3,     0,     2,
       2,     0,     2,     2,     4,     4,     0,     2,     0,     2,
       2,     2,     0,     3,     0,     4,     2,     3,     1,     1,
       1,     2,     0,     5,     4,     0,     2,     2,     1,     3,
       3,     1,     1,     1,     3,     5,     3,     0,     9,     0,
       4,     0,     4,     0,     4,     0,     5,     0,     4,     3,
       0,     2,     3,     4,     3,     1,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     3,     2,
       5,     3,     6,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     3,     2,     5,     3,     6,     1,     2,
       0,     2,     2,     3,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     3,     4,     4,
       3,     4,     4,     3,     4,     4,     3,     4,     4,     1,
       2,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     2,     3,     4,     2,     4,     3,     3,     3,     4,
       4,     5,     5,     6,     6,     4,     4,     1,     1,     2,
       1,     2,     2,     4,     1,     1,     1,     2,     2,     2,
       2,     2,     0,     5,     1,     5,     3,     1,     1,     0,
       0,     1,     2,     1,     1,     2,     2,     2,     2,     1,
       3,     2,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  extern YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= EOFTOK)
    {
      yychar = EOFTOK;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* ext_def: external_def  */
#line 731 "gram.y"
                                        {	YYCLEAN;return 2; }
#line 3042 "y.tab.c"
    break;

  case 3: /* ext_def: SM  */
#line 732 "gram.y"
                                        {	YYCLEAN;return 1; }
#line 3048 "y.tab.c"
    break;

  case 4: /* ext_def: EOFTOK  */
#line 733 "gram.y"
                                        {	YYCLEAN;return 0; }
#line 3054 "y.tab.c"
    break;

  case 5: /* ext_def: LINKAGE LC  */
#line 735 "gram.y"
                        {
				set_linkage((yyvsp[-1].s));
				bl_level--;
				YYCLEAN;return 1;
			}
#line 3064 "y.tab.c"
    break;

  case 6: /* ext_def: RC  */
#line 741 "gram.y"
                        {
				set_linkage(0);
				bl_level++;
				YYCLEAN;return 1;
			}
#line 3074 "y.tab.c"
    break;

  case 7: /* ext_def: template  */
#line 746 "gram.y"
                                         {  YYCLEAN;return 1; }
#line 3080 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 750 "gram.y"
                 {	
			PUSH_TEMPLATE_SCOPE();//SYM
// error('d',"template seen: in_class_decl %d", in_class_decl);
			if (in_class_decl) {
				must_be_friend = 1;
				if (templp->in_progress == true) // inside template
					templp->save_templ = new templ_state;
			}
			else must_be_friend = 0;
			templp->start() ;
			templp->formals_in_progress = true;
		 }
#line 3097 "y.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 762 "gram.y"
                    { in_arg_list = 2; }
#line 3103 "y.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 763 "gram.y"
                 {
			templp->enter_parameters(); 
			templp->formals_in_progress = false;
			in_arg_list = 0;
		 }
#line 3113 "y.tab.c"
    break;

  case 11: /* template: TEMPLATE $@1 LT $@2 template_parm_list GT $@3 template_def  */
#line 769 "gram.y"
                 {
			templp->end((yyvsp[0].pn));
			POP_SCOPE(); //SYM
			if (in_class_decl && templp->save_templ) {
				delete templp->save_templ;
				templp->save_templ = 0;
			}
			else { 
				templp->in_progress = false;
				bound_expr_tbl->reinit();
			}
                  //SYM -- goto mod removed
                 }
#line 3131 "y.tab.c"
    break;

  case 13: /* template_def: att_fct_def  */
#line 785 "gram.y"
                              { goto mod; }
#line 3137 "y.tab.c"
    break;

  case 14: /* template_def: fct_def  */
#line 786 "gram.y"
                             { goto mod; }
#line 3143 "y.tab.c"
    break;

  case 16: /* template_def: class_dcl SM  */
#line 789 "gram.y"
                  { 
			Pname pn = (yyvsp[-1].pb)->aggr();
			/* basetype:aggr() does not return the name for a forward 
		    	 * declaration, so extract it directly */
                    	(yyval.p) = (pn ? pn : (yyvsp[-1].pb)->b_name);
                    	DECL_TYPE = 0;
		  }
#line 3155 "y.tab.c"
    break;

  case 18: /* identifier: qualified_tname  */
#line 800 "gram.y"
                        { (yyval.pn) = Ncopy((yyvsp[0].pn)) ;}
#line 3161 "y.tab.c"
    break;

  case 19: /* external_def: data_dcl  */
#line 804 "gram.y"
                        {	
				//SYM -- tn stuff removed
				if ((yyvsp[0].pn)==0) (yyval.i) = 1; 
			}
#line 3170 "y.tab.c"
    break;

  case 20: /* external_def: att_fct_def  */
#line 808 "gram.y"
                                { goto mod; }
#line 3176 "y.tab.c"
    break;

  case 21: /* external_def: fct_def  */
#line 810 "gram.y"
                        { mod: //SYM -- tn stuff removed
				Pname n = (yyvsp[0].pn);
				if ( n && n->n_qualifier ) {//SYM
					if ( n->n_qualifier->n_template_arg != template_type_formal )
						UNSET_SCOPE();
					if ( n->n_qualifier == sta_name )
						n->n_qualifier = 0;
				}
			}
#line 3190 "y.tab.c"
    break;

  case 23: /* external_def: ASM LP STRING RP SM  */
#line 821 "gram.y"
                        {	Pname n = new name(make_name('A'));
				n->tp = new basetype(ASM,0);
				Pbase(n->tp)->b_name = Pname((yyvsp[-2].s));
				(yyval.p) = n;
			}
#line 3200 "y.tab.c"
    break;

  case 24: /* fct_dcl: decl ASSIGN initializer SM  */
#line 829 "gram.y"
                        {
				err_name = (yyvsp[-3].pn);
				if(err_name) err_name->n_initializer = (yyvsp[-1].pe);
				goto fix;
			}
#line 3210 "y.tab.c"
    break;

  case 25: /* fct_dcl: decl SM  */
#line 835 "gram.y"
                        {
				Ptype t;
				err_name = (yyvsp[-1].pn);
			fix:
				if (err_name == 0) {
					error("syntax error:TX");
					(yyval.p) = Ndata(defa_type,err_name);
				}
				else if ((t=err_name->tp) == 0) {
					error("TX for%n",err_name);
					(yyval.p) = Ndata(defa_type,err_name);
				}
				else if (t->base==FCT) {
					if (Pfct(t)->returns==0)
						(yyval.p) = Nfct(defa_type,err_name,0);
					else
						(yyval.p) = Ndata(0,err_name);
				}
				else {
					error("syntax error:TX for%k%n",t->base,err_name);
					(yyval.p) = Ndata(defa_type,err_name);
				}
				if ( err_name && err_name->n_qualifier ) {
					if ( err_name->n_qualifier->n_template_arg != template_type_formal )
						UNSET_SCOPE();
					if ( err_name->n_qualifier == sta_name )
						err_name->n_qualifier = 0;
				}
			}
#line 3244 "y.tab.c"
    break;

  case 26: /* @4: %empty  */
#line 867 "gram.y"
                        {	if ( yychar == LC ) --bl_level;
				Pname n = Nfct((yyvsp[-3].p),(yyvsp[-2].pn),dummy);
				Fargdcl(n->tp,name_unlist((yyvsp[-1].nl)),n);
				arg_redec( (yyvsp[-2].pn) );
				(yyval.pn) = n;
			 	if ( yychar == LC ) ++bl_level;
				Ctbl->k_name = n;
			}
#line 3257 "y.tab.c"
    break;

  case 27: /* att_fct_def: type decl arg_dcl_list check_inline @4 base_init block  */
#line 876 "gram.y"
                        {	Pname n = (yyvsp[-2].pn);//SYM
				if ( !in_typedef ) {
					Fbody(n->tp) = Pblock((yyvsp[0].p));//SYM
					Finit(n->tp) = (yyvsp[-1].pn);
				}
				(yyval.p) = n;
				NOT_EXPECT_ID();
			}
#line 3270 "y.tab.c"
    break;

  case 28: /* att_fct_def: type decl arg_dcl_list check_inline EMPTY  */
#line 885 "gram.y"
                        {
				Pname n = Nfct((yyvsp[-4].p),(yyvsp[-3].pn),dummy);
				Fargdcl(n->tp,name_unlist((yyvsp[-2].nl)),n);
				(yyvsp[0].q)->retval.pn = n;
				(yyval.p) = n;
				NOT_EXPECT_ID();
			}
#line 3282 "y.tab.c"
    break;

  case 29: /* att_fct_def: type decl arg_dcl_list check_inline NO_ID  */
#line 893 "gram.y"
                        {
				if (!templp->in_progress)
					error(&(yyvsp[-3].pn)->where,"syntax error -- did you forget a ';'?");
				Pname n = Nfct((yyvsp[-4].p),(yyvsp[-3].pn),0);
				(yyval.p) = n;
				NOT_EXPECT_ID();
			}
#line 3294 "y.tab.c"
    break;

  case 30: /* @5: %empty  */
#line 903 "gram.y"
                        {	if ( yychar == LC ) --bl_level;
			 	Pname n = Nfct(defa_type,(yyvsp[-2].pn),dummy);
				Fargdcl(n->tp,name_unlist((yyvsp[-1].nl)),n);
				arg_redec( (yyvsp[-2].pn) );
				(yyval.pn) = n;
			 	if ( yychar == LC ) ++bl_level;
				Ctbl->k_name = n;
			}
#line 3307 "y.tab.c"
    break;

  case 31: /* fct_def: decl arg_dcl_list check_inline @5 base_init block  */
#line 912 "gram.y"
                        {	Pname n = (yyvsp[-2].pn);//SYM
				Fbody(n->tp) = Pblock((yyvsp[0].p));//SYM
				if ( (yyvsp[-1].pn) && (yyvsp[-1].pn)->n_list && 
     					ccl && ccl->csu == UNION )  
						error( "multiple initializers in unionK %s::%n", (yyvsp[-5].pn)->string, (yyvsp[-5].pn) );
				Finit(n->tp) = (yyvsp[-1].pn);
				(yyval.p) = n;
				NOT_EXPECT_ID();
			}
#line 3321 "y.tab.c"
    break;

  case 32: /* fct_def: decl arg_dcl_list check_inline EMPTY  */
#line 922 "gram.y"
                        {
				Pname n = Nfct(defa_type,(yyvsp[-3].pn),dummy);
				Fargdcl(n->tp,name_unlist((yyvsp[-2].nl)),n);
				(yyvsp[0].q)->retval.pn = n;
				(yyval.p) = n;
				NOT_EXPECT_ID();
			}
#line 3333 "y.tab.c"
    break;

  case 33: /* fct_def: decl arg_dcl_list check_inline NO_ID  */
#line 930 "gram.y"
                        {
				if (explicit_template_definition  == 0 )
					error(&(yyvsp[-3].pn)->where,"badD of%n -- did you forget a ';'?",(yyvsp[-3].pn));
				else {
			             Pname n = pti->get_tname();
				     if ((yyvsp[-3].pn)->n_oper == DTOR)
					error('s',"explicitYZL for destructor of specializedYC%n -- please drop the parameter list",n);
				     else
					error('i',"specialializedYC%n: declaration problem: %s",n,(yyvsp[-3].pn)->string);
				     error('i', "cannot recover from previous error" );
				}
				Pname n = Nfct(defa_type,(yyvsp[-3].pn),0);
				(yyval.p) = n;
				NOT_EXPECT_ID();
			}
#line 3353 "y.tab.c"
    break;

  case 34: /* $@6: %empty  */
#line 948 "gram.y"
                        {	PUSH_ARG_SCOPE();//SYM
                        	arg_redec((yyvsp[0].pn));
                        	Ctbl->k_name = (yyvsp[0].pn);
                   	}
#line 3362 "y.tab.c"
    break;

  case 35: /* inline_fct_def: FDEF $@6 base_init block  */
#line 953 "gram.y"
                        {
				Finit((yyvsp[-3].pn)->tp) = (yyvsp[-1].pn);
				Pfct((yyvsp[-3].pn)->tp)->body = Pblock((yyvsp[0].p));
				(yyval.pn) = (yyvsp[-3].pn);
				NOT_EXPECT_ID();
			}
#line 3373 "y.tab.c"
    break;

  case 36: /* check_inline: %empty  */
#line 963 "gram.y"
                   {
			// if parsing implicit inline def, save body
			//   of function for parsing after class def
			if ( Ctbl->k_id != ARG )
				error('i',"expectingA table in check_inline!");
			switch ( NEXTTOK() ) {
			case LC: case COLON:
				if ( in_class_decl ) {
					// mem or friend inline def
					// save text of mem_init & ftn
					la_backup(yychar,yylval);
					// yylval used as dummy...
					la_backup(FDEF, yylval);
					if ( yylval.q = save_text() ) {
						yychar = EMPTY;
						POP_SCOPE();//SYM
					} else { // syntax error
						// just parse in place
						yylex(); // FDEF
						yylex();
						yychar = NO_ID;
						hoist_al();//SYM
					}
				} // if in_class_decl
				//SYM -- else non-nested ftn def
				//SYM -- arg table will become block table
				break;
			default:
				la_backup(yychar,yylval);
				yychar = NO_ID; // 'graceful' recovery
				hoist_al();//SYM
				break;
			}
		   }
#line 3412 "y.tab.c"
    break;

  case 37: /* $@7: %empty  */
#line 999 "gram.y"
                         { ++in_binit_list; }
#line 3418 "y.tab.c"
    break;

  case 38: /* base_init: COLON $@7 init_list  */
#line 1000 "gram.y"
                        {	
				(yyval.p) = (yyvsp[0].p); 
				in_arg_list = 0;
				--in_binit_list;
			}
#line 3428 "y.tab.c"
    break;

  case 39: /* base_init: %empty  */
#line 1006 "gram.y"
                        {	(yyval.p) = 0; }
#line 3434 "y.tab.c"
    break;

  case 40: /* init_list: binit  */
#line 1010 "gram.y"
                        { (yyval.p) = (yyvsp[0].p); }
#line 3440 "y.tab.c"
    break;

  case 41: /* init_list: init_list CM binit  */
#line 1012 "gram.y"
                        { (yyval.pn) = (yyvsp[0].pn);  (yyval.pn)->n_list = (yyvsp[-2].pn); }
#line 3446 "y.tab.c"
    break;

  case 42: /* binit: LP elist RP  */
#line 1016 "gram.y"
                        {
				(yyval.pn) = new name;
				(yyval.pn)->n_initializer = (yyvsp[-1].pe);
			}
#line 3455 "y.tab.c"
    break;

  case 43: /* binit: ttag LP elist RP  */
#line 1021 "gram.y"
                        {
				Pname n = Ncopy((yyvsp[-3].pn));
				n->base = (yyvsp[-3].pn)->base;
				n->tp = (yyvsp[-3].pn)->tp;
				n->n_initializer = (yyvsp[-1].pe);
				(yyval.pn) = n;
			}
#line 3467 "y.tab.c"
    break;

  case 44: /* arg_dcl_list: arg_dcl_list data_dcl  */
#line 1036 "gram.y"
                        {	if ((yyvsp[0].pn) == 0)
					error("badAD");
				else if ((yyvsp[0].pn)->tp->base == FCT)
					error("FD inAL (%n)",(yyvsp[0].pn));
				else if ((yyvsp[-1].p))
                                        (yyvsp[-1].nl)->add_list((yyvsp[0].pn));
				else
					(yyval.nl) = new nlist((yyvsp[0].pn));
			}
#line 3481 "y.tab.c"
    break;

  case 45: /* arg_dcl_list: %empty  */
#line 1046 "gram.y"
                        {
				PUSH_ARG_SCOPE();//SYM
                                (yyval.p) = 0; 
			}
#line 3490 "y.tab.c"
    break;

  case 47: /* $@8: %empty  */
#line 1054 "gram.y"
                        {
                                if ( in_typedef ) {
                                        error("Tdef field");
                                        in_typedef = 0;
                                }
                        //      ENTER_NAME($<pn>1);
                        }
#line 3502 "y.tab.c"
    break;

  case 48: /* dl: ID COLON $@8 e  */
#line 1062 "gram.y"
                        {	(yyval.p) = (yyvsp[-3].pn);
				(yyval.pn)->tp = new basetype(FIELD,(yyvsp[0].pn));
		 	}
#line 3510 "y.tab.c"
    break;

  case 49: /* dl: COLON e  */
#line 1066 "gram.y"
                        {	(yyval.p) = new name;
				(yyval.pn)->tp = new basetype(FIELD,(yyvsp[0].pn));
                                if ( in_typedef ) {
                                        error("Tdef field");
                                        in_typedef = 0;
                                }
			}
#line 3522 "y.tab.c"
    break;

  case 50: /* $@9: %empty  */
#line 1074 "gram.y"
                        {
                        //      ENTER_NAME($<pn>1);
                        }
#line 3530 "y.tab.c"
    break;

  case 51: /* dl: decl ASSIGN $@9 initializer  */
#line 1078 "gram.y"
                        {       Pexpr e = (yyvsp[0].pe);
                                if (e == dummy) error("emptyIr");
                                (yyvsp[-3].pn)->n_initializer = e;
                                init_seen = 0;
                        }
#line 3540 "y.tab.c"
    break;

  case 52: /* decl_list: dl  */
#line 1086 "gram.y"
                        {	Pname n = (yyvsp[0].pn);
				if (n) {
				    (yyval.nl) = new nlist(n);
				    if ( n->n_qualifier ) {//SYM
					if ( n->n_qualifier->n_template_arg != template_type_formal )
						UNSET_SCOPE();
					if ( n->n_qualifier == sta_name )
					    n->n_qualifier = 0;
				    }
				}
				if ( NEXTTOK() == CM && la_look() == TNAME ) 
					EXPECT_ID();
			}
#line 3558 "y.tab.c"
    break;

  case 53: /* decl_list: decl_list CM dl  */
#line 1100 "gram.y"
                        {	Pname n = (yyvsp[0].pn);
				if ((yyvsp[-2].p))
					if (n)
						(yyvsp[-2].nl)->add(n);
					else
						error("DL syntax");
				else {
					if (n) (yyval.nl) = new nlist(n);
					error("DL syntax");
				}
				if ( n ) {
				    if ( n->n_qualifier ) {//SYM
					if ( n->n_qualifier->n_template_arg != template_type_formal )
						UNSET_SCOPE();
					if ( n->n_qualifier == sta_name )
					    n->n_qualifier = 0;
				    }
				}
				if ( NEXTTOK() == CM && la_look() == TNAME ) 
					EXPECT_ID();
			}
#line 3584 "y.tab.c"
    break;

  case 54: /* data_dcl: type decl_list SM  */
#line 1124 "gram.y"
                        { 
				extern int co_hack;
				co_hack = 1;
				/*$$ = Ndata($1,name_unlist($<nl>2));*/
				Pname n = Ndata((yyvsp[-2].p),name_unlist((yyvsp[-1].nl))); 
//error('d',"data_dcl:type decl_list sm: %n%t in_typedef%t in_tag%n",n,n->tp,in_typedef,in_tag);
				//SYM redef check removed
				in_typedef = 0;
				in_friend = 0;
				in_tag = 0;
				co_hack = 0;
				DECL_TYPE = 0; 
				(yyval.p) = n;
			}
#line 3603 "y.tab.c"
    break;

  case 55: /* data_dcl: type SM  */
#line 1139 "gram.y"
                        {
				(yyval.p) = (yyvsp[-1].pb)->aggr(); 
				in_typedef = 0;
				in_friend = 0;
				in_tag = 0;
				DECL_TYPE = 0; 
			}
#line 3615 "y.tab.c"
    break;

  case 56: /* lt: LT  */
#line 1151 "gram.y"
                  {
			templp->parameters_in_progress++;
			in_arg_list = 2;
			check_decl();
		  }
#line 3625 "y.tab.c"
    break;

  case 57: /* gt: GT  */
#line 1157 "gram.y"
                  {
			templp->parameters_in_progress--;
			if (!templp->parameters_in_progress)
				in_arg_list = 0;
		  }
#line 3635 "y.tab.c"
    break;

  case 58: /* tname: qualified_tname  */
#line 1163 "gram.y"
                                  { (yyval.pn) = templp->check_tname((yyvsp[0].pn)) ; }
#line 3641 "y.tab.c"
    break;

  case 59: /* tname: qualified_tname lt temp_inst_parms gt  */
#line 1165 "gram.y"
                  { 
			int sm = NEXTTOK()==SM;
			if (in_friend) in_friend += sm;
			bit flag=0;
			if (dtpt_opt && in_typedef &&  
				!templp->parameters_in_progress &&
				curloc.file == first_file)
				flag=1;
		    	(yyval.pn) = parametrized_typename((yyvsp[-3].pn),
						  (expr_unlist((yyvsp[-1].el))),in_friend) ; 
			if (flag)
				righttname=(yyval.pn);
		  }
#line 3659 "y.tab.c"
    break;

  case 60: /* tname: NAME lt temp_inst_parms gt  */
#line 1179 "gram.y"
                  { extern Pbase any_type;
		    error("%n was not aZizedT.", (yyval.pn)) ;
                    (yyval.pn)= (yyvsp[-3].pn)->tdef() ;
                    (yyval.pn)->tp = any_type ; }
#line 3668 "y.tab.c"
    break;

  case 61: /* tp: TYPE  */
#line 1188 "gram.y"
                        { 
				(yyval.p) = new basetype((yyvsp[0].t),0); 
				if ( (yyvsp[0].t) == TYPEDEF ) {
					in_typedef = (yyval.pt);
// error('d',"typedef: ccl %t ", ccl, $<pn>1);
				}
				else if ( (yyvsp[0].t) == FRIEND ) {
					in_friend = 1;
					must_be_friend = 0;
				}
				if (DECL_TYPE == -1) DECL_TYPE = 0;
			}
#line 3685 "y.tab.c"
    break;

  case 62: /* tp: LINKAGE  */
#line 1201 "gram.y"
                        {	(yyval.p) = new basetype(EXTERN,0);
				(yyval.pb)->b_linkage = (yyvsp[0].s);
				if (DECL_TYPE == -1) DECL_TYPE = 0;
			}
#line 3694 "y.tab.c"
    break;

  case 63: /* tp: tname  */
#line 1206 "gram.y"
                        {
				(yyval.p) = new basetype(TYPE,(yyvsp[0].pn)); 
				if (DECL_TYPE == -1) DECL_TYPE = 0;
			}
#line 3703 "y.tab.c"
    break;

  case 64: /* tp: tn_list DECL_MARKER  */
#line 1211 "gram.y"
                        { // modified tn_list TNAME
				(yyval.p) = new basetype(TYPE,(yyvsp[0].pn));
				//xxx qualifier currently ignored...
				if (DECL_TYPE == -1) DECL_TYPE = 0;
			}
#line 3713 "y.tab.c"
    break;

  case 67: /* tp: DECL_MARKER  */
#line 1219 "gram.y"
                        { 
				if (DECL_TYPE == TNAME)
					(yyval.p) = new basetype(TYPE,(yyvsp[0].pn)); 
		//	else if (DECL_TYPE == TSCOPE)
		//	$$ = 0;
				else
				if (DECL_TYPE == 0 &&
					(yyvsp[0].p)->base == TNAME)
						(yyval.p) = new basetype(TYPE,(yyvsp[0].pn)); 
				else
					(yyval.p) = new basetype((yyvsp[0].t),0); 
				DECL_TYPE = -1;
			}
#line 3731 "y.tab.c"
    break;

  case 69: /* type: type TYPE  */
#line 1236 "gram.y"
                        { 
				if ( DECL_TYPE != -1 ) {
					switch ((yyvsp[-1].pb)->base) { 
					case COBJ: case EOBJ:
						Pbase bt;	
						bt = new basetype(0,0);
						*bt = *(yyvsp[-1].pb);
						DEL((yyvsp[-1].pb));
						(yyvsp[-1].pb) = bt;
					}
					(yyval.p) = (yyvsp[-1].pb)->type_adj((yyvsp[0].t)); 
				}
				DECL_TYPE = 0;
			}
#line 3750 "y.tab.c"
    break;

  case 70: /* type: type tname  */
#line 1251 "gram.y"
                        {
//error('d',"decl_type: %d  $1: %t  $2: %n",DECL_TYPE,$<pb>1,$<pn>2);
				if ( DECL_TYPE != -1 ) 
			 		(yyval.p) = (yyvsp[-1].pb)->name_adj((yyvsp[0].pn));
			/*XXX*/	else if((yyvsp[-1].pb)==0) (yyval.p)=new basetype(TYPE,(yyvsp[0].pn));
				DECL_TYPE = 0;
			}
#line 3762 "y.tab.c"
    break;

  case 71: /* type: type class_dcl  */
#line 1258 "gram.y"
                                        { (yyval.p) = (yyvsp[-1].pb)->base_adj((yyvsp[0].pb)); }
#line 3768 "y.tab.c"
    break;

  case 72: /* type: type enum_dcl  */
#line 1259 "gram.y"
                                        { (yyval.p) = (yyvsp[-1].pb)->base_adj((yyvsp[0].pb)); }
#line 3774 "y.tab.c"
    break;

  case 73: /* type: type DECL_MARKER  */
#line 1261 "gram.y"
                        { 
				if (DECL_TYPE == TYPE) {
					switch ((yyvsp[-1].pb)->base) { 
					case COBJ: case EOBJ: 
						{
						Pbase bt;
						bt = new basetype(0,0);
						*bt = *(yyvsp[-1].pb);
						DEL((yyvsp[-1].pb));
						(yyvsp[-1].pb) = bt;
						}
					}
					(yyval.p) = (yyvsp[-1].pb)->type_adj((yyvsp[0].t));  
				}
			/*XXX*/	else if (DECL_TYPE == TSCOPE) {
			/*XXX*/		error('i',"T decl_marker(tscope)");
			/*XXX*/	//	$$ = $1;//ignore(?)
			/*XXX*/	}
				else
					(yyval.p) = (yyvsp[-1].pb)->name_adj((yyvsp[0].pn)); 
				DECL_TYPE = -1;
			}
#line 3801 "y.tab.c"
    break;

  case 74: /* cm: CM  */
#line 1285 "gram.y"
                     {in_arg_list = 2; check_decl();}
#line 3807 "y.tab.c"
    break;

  case 75: /* temp_inst_parms: temp_inst_parms cm temp_inst_parm  */
#line 1288 "gram.y"
                  {(yyvsp[-2].el)->add(new expr(ELIST,(yyvsp[0].pe),0)) ; }
#line 3813 "y.tab.c"
    break;

  case 76: /* temp_inst_parms: temp_inst_parm  */
#line 1290 "gram.y"
                        { in_arg_list=0; (yyval.el) = new elist(new expr(ELIST,(yyvsp[0].pe),0)); }
#line 3819 "y.tab.c"
    break;

  case 77: /* new_decl2: %empty  */
#line 1294 "gram.y"
                        {
				(yyval.p) = new name;
			}
#line 3827 "y.tab.c"
    break;

  case 78: /* new_decl2: arg_lp new_decl2 RP  */
#line 1298 "gram.y"
                        {
				(yyval.p) = (yyvsp[-1].p);
				in_arg_list = 0;
				hoist_al();
			}
#line 3837 "y.tab.c"
    break;

  case 79: /* new_decl2: ptr new_decl2  */
#line 1304 "gram.y"
                        {
				Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (Ptype)(yyvsp[-1].p);
				(yyval.p) = (yyvsp[0].p);
				NOT_EXPECT_ID();
			}
#line 3848 "y.tab.c"
    break;

  case 80: /* new_decl2: new_decl2 arg_list  */
#line 1311 "gram.y"
                        {
				Freturns((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 3857 "y.tab.c"
    break;

  case 81: /* new_decl2: new_decl2 vec  */
#line 1316 "gram.y"
                        {
				Vtype((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 3866 "y.tab.c"
    break;

  case 82: /* new_type2: type new_decl2  */
#line 1322 "gram.y"
                                        { (yyval.p) = Ncast((yyvsp[-1].p),(yyvsp[0].pn)); }
#line 3872 "y.tab.c"
    break;

  case 83: /* temp_inst_parm: new_type2  */
#line 1325 "gram.y"
                        {
				(yyvsp[0].pn)->n_template_arg = template_actual_arg_dummy;
				(yyval.pe) = (yyvsp[0].pn); /* keep yacc happy */ 
			}
#line 3881 "y.tab.c"
    break;

  case 84: /* temp_inst_parm: e  */
#line 1330 "gram.y"
                        { 
				if ((yyvsp[0].pe) == dummy) error("emptyYZL");
				(yyval.pe) = (yyvsp[0].pe); 
			}
#line 3890 "y.tab.c"
    break;

  case 85: /* enumtag: tag  */
#line 1338 "gram.y"
               { (yyval.p) = enumcheck( (yyvsp[0].pn)); }
#line 3896 "y.tab.c"
    break;

  case 86: /* enumtag: DECL_MARKER  */
#line 1340 "gram.y"
                {
			if ( DECL_TYPE != TNAME ) {
				error("syntax error -- enum%k",(yyvsp[0].t));
				(yyval.p) = 0;
			} else 
				(yyval.p) = enumcheck( (yyvsp[0].pn));
		}
#line 3908 "y.tab.c"
    break;

  case 87: /* enumtag: tn_list DECL_MARKER  */
#line 1348 "gram.y"
                {
			if ( DECL_TYPE != TNAME ) {
				error("enum declaration syntax");
				(yyval.p) = 0;
			} else 
				(yyval.pn) = enumcheck((yyvsp[0].pn));
			if (in_typedef && in_typedef->base == 0)
				in_typedef->defined = TNAME_SEEN;
			//xxx qualifier currently ignored...
		}
#line 3923 "y.tab.c"
    break;

  case 88: /* $@10: %empty  */
#line 1360 "gram.y"
                           { ++in_class_decl; }
#line 3929 "y.tab.c"
    break;

  case 89: /* enum_dcl: ENUM LC $@10 moe_list RC  */
#line 1361 "gram.y"
                        { --in_class_decl; (yyval.p) = end_enum(0,(yyvsp[-1].nl)); }
#line 3935 "y.tab.c"
    break;

  case 90: /* $@11: %empty  */
#line 1362 "gram.y"
                                   { ++in_class_decl; }
#line 3941 "y.tab.c"
    break;

  case 91: /* enum_dcl: ENUM enumtag LC $@11 moe_list RC  */
#line 1363 "gram.y"
                        { --in_class_decl; (yyval.p) = end_enum((yyvsp[-4].pn),(yyvsp[-1].nl)); }
#line 3947 "y.tab.c"
    break;

  case 92: /* enum_dcl: ENUM enumtag  */
#line 1364 "gram.y"
                                                { (yyval.pb) = (Pbase)(yyvsp[0].pn)->tp; }
#line 3953 "y.tab.c"
    break;

  case 93: /* moe_list: moe  */
#line 1368 "gram.y"
                        {	if ((yyvsp[0].p)) (yyval.nl) = new nlist((yyvsp[0].pn)); }
#line 3959 "y.tab.c"
    break;

  case 94: /* moe_list: moe_list CM moe  */
#line 1370 "gram.y"
                        {	if( (yyvsp[0].p))
					if ((yyvsp[-2].p))
						(yyvsp[-2].nl)->add((yyvsp[0].pn));
					else
						(yyval.nl) = new nlist((yyvsp[0].pn));
			}
#line 3970 "y.tab.c"
    break;

  case 97: /* template_parm_list: %empty  */
#line 1381 "gram.y"
                        { 
				(yyval.pn) = 0;
				error("emptyYZL");
			}
#line 3979 "y.tab.c"
    break;

  case 98: /* template_parm: AGGR identifier  */
#line 1390 "gram.y"
                 { templp->collect((yyvsp[-1].t), (yyvsp[0].pn)) ; }
#line 3985 "y.tab.c"
    break;

  case 99: /* template_parm: type formal_decl  */
#line 1392 "gram.y"
                        {templp->collect(Ndata((yyvsp[-1].p),(yyvsp[0].pn))); }
#line 3991 "y.tab.c"
    break;

  case 100: /* formal_decl: ID  */
#line 1399 "gram.y"
                        {	(yyval.p) = (yyvsp[0].pn); }
#line 3997 "y.tab.c"
    break;

  case 101: /* formal_decl: ptr formal_decl  */
#line 1401 "gram.y"
                        {	Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (Ptype)(yyvsp[-1].p);
				(yyval.p) = (yyvsp[0].p);
			}
#line 4006 "y.tab.c"
    break;

  case 102: /* formal_decl: formal_decl vec  */
#line 1406 "gram.y"
                        {	Vtype((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 4014 "y.tab.c"
    break;

  case 103: /* formal_decl: formal_decl arg_list  */
#line 1410 "gram.y"
                        {	Freturns((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 4022 "y.tab.c"
    break;

  case 104: /* formal_decl: arg_lp formal_decl RP  */
#line 1414 "gram.y"
                        {
				(yyval.p) = (yyvsp[-1].p);
				in_arg_list = 0;
				hoist_al();
			}
#line 4032 "y.tab.c"
    break;

  case 105: /* moe: ID  */
#line 1423 "gram.y"
                        {
				if ( (yyvsp[0].pn)->n_oper != TNAME )
					insert_name((yyvsp[0].pn),Ctbl);
				(yyval.p) = (yyvsp[0].pn);
				(yyval.pn)->tp = moe_type;
			}
#line 4043 "y.tab.c"
    break;

  case 106: /* $@12: %empty  */
#line 1430 "gram.y"
                        {
				if ( (yyvsp[0].pn)->n_oper != TNAME )
					insert_name((yyvsp[0].pn),Ctbl);
			}
#line 4052 "y.tab.c"
    break;

  case 107: /* moe: ID $@12 ASSIGN e  */
#line 1435 "gram.y"
                        {	(yyval.p) = (yyvsp[-3].pn);
				(yyval.pn)->tp = moe_type;
				(yyval.pn)->n_initializer = (yyvsp[0].pe);
			}
#line 4061 "y.tab.c"
    break;

  case 108: /* moe: %empty  */
#line 1440 "gram.y"
                        {	(yyval.p) = 0; }
#line 4067 "y.tab.c"
    break;

  case 109: /* $@13: %empty  */
#line 1444 "gram.y"
                        {	parsing_class_members = 0;
				RESTORE_STATE();
				switch ( NEXTTOK() ) {
				case TYPE: case AGGR: case ENUM: case EOFTOK:
					error("`;' or declaratorX afterCD");
					la_backup(yychar,yylval);
					yychar = SM;
					break;
				}
				la_backup(yychar,yylval);
				yychar = YYEMPTY;	/* bison empty sentinel, was -1 */
				restore_text();
				++bl_level; // scope weirdness!
				++in_mem_fct;
			}
#line 4087 "y.tab.c"
    break;

  case 110: /* class_dcl: class_head cl_mem_list RC $@13 inline_mem_defs  */
#line 1460 "gram.y"
                        {
				--in_mem_fct;
				--bl_level; // scope weirdness!
				if ( yychar == ID ) {
					// (yuk!) adjust lex level
					--yylval.pn->lex_level;
				}
				ccl->mem_list = name_unlist((yyvsp[-3].nl));
// error('d',"ccl: %t templ_friends: %d", ccl, templ_friends);
				ccl->templ_friends = templ_friends; templ_friends = 0;
				if ( --in_class_decl )  // nested class
					// continue to parse enclosing class
					parsing_class_members = 1;
				//SYM -- tn stuff removed
                        	POP_SCOPE();//SYM
				if ( Ctbl->k_id == TEMPLATE ) {
					// remove intermediate template table
					//    from scope of class
					ccl->k_tbl->k_next = Ctbl->k_next;
				}

				if (pti) {
					pti->explicit_inst();
					Pname nnn = (yyval.pt)->bname();
// error('d',"ccl: %s nnn: %s", ccl->string, nnn->string);
					nnn->string = ccl->string;
					explicit_template_definition = 0;
					pti = 0;
				}

				end_cl();
				declTag = 1;
			}
#line 4125 "y.tab.c"
    break;

  case 111: /* class_dcl: AGGR tag  */
#line 1494 "gram.y"
                        { aggrcheck:
				(yyval.pb) = (Pbase)(yyvsp[0].pn)->tp; 
				if ( (yyval.p) == 0 ) {
					if (templp->parameters_in_progress)
						error("TX for%n -- did you misdeclare aY?",(yyvsp[0].pn));
					else error("TX for %n",(yyvsp[0].pn));
					error('i', "cannot recover from previous error" );
				}

				if ( (yyval.p)->base == TYPE ) {
					Pname nx = (yyval.pb)->b_name;
					(yyval.pb) = (Pbase)nx->tp;
					if ( (yyval.p)->base != COBJ
					||   strcmp(nx->string,(yyvsp[0].pn)->string)
					)
						error("%n of type%t redeclared as%k.",(yyvsp[0].pn),(yyval.pb),(yyvsp[-1].t));
				} else if ( (yyval.p)->base != COBJ )
					error("%n of type%t redeclared as%k",(yyvsp[0].pn),(yyval.pb),(yyvsp[-1].t));
				check_tag();
			}
#line 4150 "y.tab.c"
    break;

  case 112: /* class_dcl: AGGR qualified_tname lt temp_inst_parms gt  */
#line 1515 "gram.y"
                  { 
                    /* don't place the template on the instantiation list if it is
                     * a friend declaration or a foward declaration of a specialization
                     * friend class x<int> and struct x<int>; */

                    dont_instantiate = NEXTTOK()==SM;
		    Pexpr e=0;
		    if (dont_instantiate && in_friend == 0) {
			// *** this code could be used for forward declaration
			Ptempl t = templp->is_template((yyvsp[-3].pn));

			// must have seen a definition of template class
			if (t == 0) {
				error("explicitC instance of a nonYC%n",(yyvsp[-3].pn));
				error('i', "cannot recover from previous error" );
			}

			// make sure the explicit arguments are ok
			e = expr_unlist((yyvsp[-1].el));
			t->check_actual_args(e);

			// watch out for redefinition -- if exists,
			// use forward declaration or create instance
			pti = t->get_match(e,0,false);
			if ( pti ) { 
				if (pti->get_class()->class_base == INSTANTIATED)
					error("ZC%n multiply instantiated",(yyvsp[-3].pn));
			}
			else pti = new templ_inst(e,t,(yyvsp[-4].t));
			pti->inst_formals = t->get_formals();

			error('s',"forwardD of a specialized version ofY%n",(yyvsp[-3].pn));
			error('C',"\tclass %n",pti->get_tname()); 
			error('c'," -- did you mean a general forward declaration of theY?\n");
			error('C',"\tif so, use:  template <formal-parameters> class %n;\n",(yyvsp[-3].pn));
	            }

		    if (!e)
		    {
		        e = expr_unlist((yyvsp[-1].el));
                    }
                    Pname p = parametrized_typename((yyvsp[-3].pn), e, in_friend);
                    dont_instantiate = 0;
                    (yyval.pb) = (Pbase)p->tp;
                    check_tag();
                  }
#line 4201 "y.tab.c"
    break;

  case 113: /* class_dcl: AGGR DECL_MARKER  */
#line 1562 "gram.y"
                        {
				goto aggrcheck;
			}
#line 4209 "y.tab.c"
    break;

  case 116: /* base_list: COLON base_unit_list  */
#line 1572 "gram.y"
                                                { (yyval.pbc) = (yyvsp[0].pbc); }
#line 4215 "y.tab.c"
    break;

  case 117: /* base_list: %empty  */
#line 1573 "gram.y"
                                                { (yyval.pbc) = 0; }
#line 4221 "y.tab.c"
    break;

  case 119: /* base_unit_list: base_unit_list CM base_unit  */
#line 1578 "gram.y"
                        {	if ((yyvsp[0].pbc)) { (yyval.pbc) = (yyvsp[0].pbc); (yyval.pbc)->next = (yyvsp[-2].pbc); } }
#line 4227 "y.tab.c"
    break;

  case 120: /* base_unit: ttag  */
#line 1581 "gram.y"
                                        { (yyval.pbc) = dobase(0,(yyvsp[0].pn)); }
#line 4233 "y.tab.c"
    break;

  case 121: /* base_unit: PR ttag  */
#line 1582 "gram.y"
                                        { (yyval.pbc) = dobase((yyvsp[-1].t),(yyvsp[0].pn)); }
#line 4239 "y.tab.c"
    break;

  case 122: /* base_unit: TYPE ttag  */
#line 1583 "gram.y"
                                        { (yyval.pbc) = dobase(0,(yyvsp[0].pn),(yyvsp[-1].t)); }
#line 4245 "y.tab.c"
    break;

  case 123: /* base_unit: PR TYPE ttag  */
#line 1584 "gram.y"
                                        { (yyval.pbc) = dobase((yyvsp[-2].t),(yyvsp[0].pn),(yyvsp[-1].t)); }
#line 4251 "y.tab.c"
    break;

  case 124: /* base_unit: TYPE PR ttag  */
#line 1585 "gram.y"
                                        { (yyval.pbc) = dobase((yyvsp[-1].t),(yyvsp[0].pn),(yyvsp[-2].t)); }
#line 4257 "y.tab.c"
    break;

  case 125: /* class_head: AGGR LC  */
#line 1589 "gram.y"
                        {
				Pname n = start_cl((yyvsp[-1].t),0,0);
				PUSH_CLASS_SCOPE(n);//SYM
				ccl->k_tbl = Ctbl;//SYM
				(yyval.p) = Pbase(n->tp);
				parsing_class_members = 1;
				//SYM -- tn stuff removed
				in_class_decl++;
				SAVE_STATE();
			}
#line 4272 "y.tab.c"
    break;

  case 126: /* class_head: AGGR tag base_list LC  */
#line 1601 "gram.y"
                        {
				Pname n = start_cl((yyvsp[-3].t),(yyvsp[-2].pn),(yyvsp[-1].pbc));
				PUSH_CLASS_SCOPE(n);//SYM
				ccl->k_tbl = Ctbl;//SYM
				(yyval.p) = Pbase(n->tp);
				parsing_class_members = 1;
				//SYM -- tn stuff removed
				in_class_decl++;
				SAVE_STATE();
			}
#line 4287 "y.tab.c"
    break;

  case 127: /* class_head: AGGR qualified_tname lt temp_inst_parms gt base_list LC  */
#line 1612 "gram.y"
                        {
			// LC increments bl_level by 1
			if ( bl_level > 1 )
			     error('s', "specializedY%n not at global scope",(yyvsp[-5].pn));
			explicit_template_definition = 1;
			Ptempl t = templp->is_template((yyvsp[-5].pn));

			// must have seen a definition of template class
			if (t == 0 || !t->defined) {
				error("YC%n must be defined prior to an explicitC instance",(yyvsp[-5].pn));
				error('i', "cannot recover from previous error" );
			}

			// make sure the explicit arguments are ok
			Pexpr e = expr_unlist((yyvsp[-3].el));
			t->check_actual_args(e);

			// watch out for redefinition -- if exists,
			// use forward declaration or create instance
			pti = t->get_match(e,0,false);
			if ( pti ) { 
				if (pti->get_class()->class_base == INSTANTIATED)
					error("ZC%n multiply instantiated",(yyvsp[-5].pn));
			}
			else pti = new templ_inst(e,t,(yyvsp[-6].t));

			Pname n = start_cl((yyvsp[-6].t),pti->get_tname(),(yyvsp[-1].pbc));
                        Pbase(n->tp)->b_name->n_redefined = 1;
			PUSH_CLASS_SCOPE(n);//SYM
			ccl->k_tbl = Ctbl;//SYM
			(yyval.p) = Pbase(n->tp);
			parsing_class_members = 1;
			in_class_decl++;
			SAVE_STATE();
			}
#line 4327 "y.tab.c"
    break;

  case 128: /* tag: ID  */
#line 1649 "gram.y"
                        { (yyval.p) = (yyvsp[0].pn); }
#line 4333 "y.tab.c"
    break;

  case 129: /* tag: qualified_tname  */
#line 1650 "gram.y"
                                   { (yyval.p)=(yyvsp[0].p); }
#line 4339 "y.tab.c"
    break;

  case 130: /* ttag: ID  */
#line 1653 "gram.y"
                        { (yyval.p) = (yyvsp[0].pn); }
#line 4345 "y.tab.c"
    break;

  case 131: /* ttag: tname  */
#line 1654 "gram.y"
                         { (yyval.p)=(yyvsp[0].p); }
#line 4351 "y.tab.c"
    break;

  case 132: /* cl_mem_list: cl_mem_list cl_mem  */
#line 1658 "gram.y"
                        {
				if ((yyvsp[0].p)) {
					if ((yyvsp[-1].p))
						(yyvsp[-1].nl)->add_list((yyvsp[0].pn));
					else
						(yyval.nl) = new nlist((yyvsp[0].pn));
				}
				in_friend = 0;
			}
#line 4365 "y.tab.c"
    break;

  case 133: /* cl_mem_list: %empty  */
#line 1667 "gram.y"
                               { (yyval.p) = 0; }
#line 4371 "y.tab.c"
    break;

  case 134: /* cl_mem_list: cl_mem_list template  */
#line 1669 "gram.y"
                        {
// error('d', "ZizedTD must be atG, notC scope" );
				if (must_be_friend) {
					error("non-friend ZizedTD must be atG, notC scope" );
					error('i', "cannot recover from previous error" );
				}
  				templ_friends = new cons(templp->parsed_template,templ_friends);
				templp->parsed_template = 0;
			}
#line 4385 "y.tab.c"
    break;

  case 136: /* cl_mem: att_fct_def SM  */
#line 1682 "gram.y"
                        {
				fct_friend1:
				if (in_friend &&
				    (yyvsp[-1].pn) &&
				    (yyvsp[-1].pn)->n_qualifier &&
				    (yyvsp[-1].pn)->n_qualifier->n_template_arg != template_type_formal)
					UNSET_SCOPE();
			}
#line 4398 "y.tab.c"
    break;

  case 137: /* cl_mem: fct_def SM  */
#line 1691 "gram.y"
                        {
				goto fct_friend1;
			}
#line 4406 "y.tab.c"
    break;

  case 138: /* cl_mem: fct_def  */
#line 1695 "gram.y"
                        {
				fct_friend2:
				if (in_friend &&
				    (yyvsp[0].pn) &&
				    (yyvsp[0].pn)->n_qualifier &&
				    (yyvsp[0].pn)->n_qualifier->n_template_arg != template_type_formal)
					UNSET_SCOPE();
			}
#line 4419 "y.tab.c"
    break;

  case 139: /* cl_mem: att_fct_def  */
#line 1704 "gram.y"
                        {
				goto fct_friend2;
			}
#line 4427 "y.tab.c"
    break;

  case 141: /* cl_mem: PR COLON  */
#line 1709 "gram.y"
                        {	(yyval.p) = new name;
				(yyval.pn)->base = (yyvsp[-1].t);
			}
#line 4435 "y.tab.c"
    break;

  case 142: /* cl_mem: scope_qualifiers fname SM  */
#line 1713 "gram.y"
                        {	Pname n = Ncopy((yyvsp[-1].pn));
				if (n->n_oper == TYPE) {
					error('s',"visibilityD for conversion operator");
					// n->tp = Ptype(n->n_initializer);
					n->tp = Ptype(n->cond);
					n->cond = 0;
					// n->n_initializer = 0;
					n->n_oper = 0;
					sig_name(n);
				}
				n->n_qualifier = (yyvsp[-2].pn);
				n->base = PR;
				(yyval.p) = n;
				if ( (yyvsp[-2].pn) && (yyvsp[-2].pn)->n_template_arg != template_type_formal )
					UNSET_SCOPE();//SYM
			}
#line 4456 "y.tab.c"
    break;

  case 143: /* fname: ID  */
#line 1743 "gram.y"
                      { (yyval.p) = (yyvsp[0].pn); }
#line 4462 "y.tab.c"
    break;

  case 144: /* fname: COMPL TNAME  */
#line 1745 "gram.y"
                        {	(yyval.p) = Ncopy((yyvsp[0].pn));
				(yyval.pn)->n_oper = DTOR;
			}
#line 4470 "y.tab.c"
    break;

  case 145: /* fname: OPERATOR oper  */
#line 1749 "gram.y"
                        {	(yyval.p) = new name(oper_name((yyvsp[0].t)));
				(yyval.pn)->n_oper = (yyvsp[0].t);
			}
#line 4478 "y.tab.c"
    break;

  case 146: /* fname: OPERATOR c_type  */
#line 1753 "gram.y"
                        {	Pname n = (yyvsp[0].pn);
				n->string = "_type";
				n->n_oper = TYPE;
				n->cond = Pexpr(n->tp);
				// n->n_initializer = Pexpr(n->tp);
				n->tp = 0;
				(yyval.p) = n;
			}
#line 4491 "y.tab.c"
    break;

  case 161: /* oper: LP RP  */
#line 1777 "gram.y"
                                {	(yyval.t) = CALL; }
#line 4497 "y.tab.c"
    break;

  case 162: /* oper: LB RB  */
#line 1778 "gram.y"
                                {	(yyval.t) = DEREF; }
#line 4503 "y.tab.c"
    break;

  case 168: /* oper: NEW  */
#line 1784 "gram.y"
                                {	(yyval.t) = NEW; --in_new; }
#line 4509 "y.tab.c"
    break;

  case 169: /* oper: DELETE  */
#line 1785 "gram.y"
                                {	(yyval.t) = DELETE; }
#line 4515 "y.tab.c"
    break;

  case 170: /* oper: REF  */
#line 1786 "gram.y"
                                {	(yyval.t) = REF; }
#line 4521 "y.tab.c"
    break;

  case 171: /* oper: CM  */
#line 1787 "gram.y"
                                {	(yyval.t) = CM; }
#line 4527 "y.tab.c"
    break;

  case 172: /* oper: REFMUL  */
#line 1788 "gram.y"
                                {	(yyval.t) = REFMUL;
					if ((yyvsp[0].t) == DOT) error(".* cannot be overloaded");
				}
#line 4535 "y.tab.c"
    break;

  case 173: /* scope_qualifiers: tn_list  */
#line 1793 "gram.y"
                           { (yyval.pn) = SET_SCOPE((yyvsp[0].pn)); }
#line 4541 "y.tab.c"
    break;

  case 174: /* tn_list: tscope  */
#line 1797 "gram.y"
                        {   if ( (yyvsp[0].pn) != sta_name ) {
				Pname n = (yyvsp[0].pn);
				char *str = 0, *str2 = 0, *s = n->string;
				if (n->n_template_arg != template_type_formal) {
				    n = n->tp->is_cl_obj();
				    if ( n ) str = s = get_classname(n->string);
				}
				if ( n && NEXTTOK() == TNAME
				&& strcmp(s,str2=get_classname(yylval.pn->string))==0){
					// ctor -- change to ID to avoid
					//    parsing as type spec
					yychar = ID;
					yylval.pn = Ncopy(yylval.pn);
					yylval.pn->n_oper = TNAME;
				}
				if ( str ) delete [] str;
				if ( str2 ) delete [] str2;
			    }
			    (yyval.pn) = (yyvsp[0].pn);
			}
#line 4566 "y.tab.c"
    break;

  case 175: /* tn_list: tn_list tscope  */
#line 1818 "gram.y"
                        {//SYM
			   (yyval.pn) = (yyvsp[0].pn);
			   if ( (yyvsp[0].pn) == sta_name ) {
			   	error("scope qualifier syntax");
			   } else {
// error('d',"tn_list: tn_list tscope: pn2: %s", $<pn>2->string);
				Pname cn = (yyvsp[0].pn);
				char *str = 0, *str2 = 0, *s = cn->string;
				if (cn->n_template_arg != template_type_formal){
				    cn = (yyvsp[0].pn)->tp->is_cl_obj();
				    if (cn) str = s = get_classname(cn->string);
				}
				if ( cn && NEXTTOK() == TNAME
				&& strcmp(s,str2=get_classname(yylval.pn->string))==0){
					// ctor -- change to ID to avoid
					//    parsing as type spec
					yychar = ID;
					yylval.pn = Ncopy(yylval.pn);
					yylval.pn->n_oper = TNAME;
				}
				if ( str ) delete [] str;
				if ( str2 ) delete [] str2;
				if ( (yyvsp[-1].pn) != sta_name
				&&   (yyvsp[-1].pn)->n_template_arg != template_type_formal){
				    Pname cx = (yyvsp[-1].pn)->tp->is_cl_obj();
				    if ( cx ) // cx::cn::
					if ( check_if_base(Pclass(cx->tp),Pclass(cn->tp)) )
						error("%n ::%n :: --%n not aM of%n",cx,cn,cn,cx);
				}
			    }
			}
#line 4602 "y.tab.c"
    break;

  case 176: /* qualified_tname: tn_list TNAME  */
#line 1852 "gram.y"
                        {	
				(yyval.pn) = (yyvsp[0].pn);
				if (in_typedef && in_typedef->base == 0)
					in_typedef->defined = TNAME_SEEN;
				//xxx qualifier currently ignored...
				// $<pn>$ = Ncopy( $<pn>2 );
				// $<pn>$->n_oper = TNAME;
				// $<pn>$->n_qualifier = $<pn>1;
			}
#line 4616 "y.tab.c"
    break;

  case 177: /* qualified_tname: TNAME  */
#line 1862 "gram.y"
                        {	
				(yyval.pn) = (yyvsp[0].pn);
				if (in_typedef && in_typedef->base == 0)
					in_typedef->defined = TNAME_SEEN;
			//	$<pn>$ = Ncopy( $<pn>1 );
			//	$<pn>$->n_oper = TNAME;
			}
#line 4628 "y.tab.c"
    break;

  case 178: /* fct_attributes: %empty  */
#line 1872 "gram.y"
                        { (yyval.i) = 0; }
#line 4634 "y.tab.c"
    break;

  case 179: /* fct_attributes: fct_attributes TYPE  */
#line 1874 "gram.y"
                        { /* const/volatile function */
				switch ( (yyvsp[0].t) ) {
				case VOLATILE:
					error('s',"volatile functions");
					break;
				case CONST:
					(yyval.i) = ((yyvsp[-1].i) | 1);
					break;
				default:
					if ( NEXTTOK() != SM
					&&   yychar != COLON
					&&   yychar != LC ) {
						la_backup(yychar,yylval);
						yylval.t = (yyvsp[0].t);
						la_backup(TYPE,yylval);
						yylval.t = SM;
						yychar = SM;
						error("syntax error: unexpected%k (did you forget a `;'?)",(yyvsp[0].t));
					} else error("FD syntax: unexpected%k",(yyvsp[0].t));
					break;
				}
 			}
#line 4661 "y.tab.c"
    break;

  case 180: /* fct_attributes: fct_attributes THROW LP type_list RP  */
#line 1897 "gram.y"
                        { (yyval.i) = (yyvsp[-4].i); }
#line 4667 "y.tab.c"
    break;

  case 181: /* type_list: tag  */
#line 1900 "gram.y"
                        { (yyval.pl) = 0; }
#line 4673 "y.tab.c"
    break;

  case 182: /* type_list: type_list CM tag  */
#line 1902 "gram.y"
                        { (yyval.pl) = 0; }
#line 4679 "y.tab.c"
    break;

  case 183: /* decl: decl arg_list  */
#line 1906 "gram.y"
                        {	Freturns((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (yyvsp[0].pt);
			}
#line 4687 "y.tab.c"
    break;

  case 184: /* decl: decl LP RP fct_attributes  */
#line 1910 "gram.y"
                        { /* function with no argument */
 				(yyvsp[-3].pn)->tp = new fct((yyvsp[-3].pn)->tp,0,1);
 				Pfct((yyvsp[-3].pn)->tp)->f_const = ((yyvsp[0].i) & 1);
 			}
#line 4696 "y.tab.c"
    break;

  case 185: /* decl: tname arg_list  */
#line 1915 "gram.y"
                        {	Pname n = (yyvsp[-1].pn);
				(yyval.p) = Ncopy(n);
				//??? what if tname is qualified ???
				//SYM -- change -- do not if ctor def...
				if ( !in_typedef
				&&  (ccl==0 || strcmp(n->string,ccl->string)) )
					n->hide();
				(yyval.pn)->n_oper = TNAME;
				Freturns((yyvsp[0].p)) = (yyval.pn)->tp;
				(yyval.pn)->tp = (yyvsp[0].pt);
			}
#line 4712 "y.tab.c"
    break;

  case 186: /* decl: decl arg_lp elist RP  */
#line 1931 "gram.y"
                        {	
				(yyvsp[-3].pn)->tp = new fct((yyvsp[-3].pn)->tp,(yyvsp[-1].pn),1); 
 				in_arg_list = 0;
 				//SYM end_al($2,0);
 				POP_SCOPE();//SYM
				//RESTORE_STATE();
			}
#line 4724 "y.tab.c"
    break;

  case 187: /* decl: tname LP MUL ID RP arg_list  */
#line 1939 "gram.y"
                        {
				Pptr p = new ptr( PTR, 0 );
				Ptyp(p) = new basetype(TYPE,(yyvsp[-5].pn));
				Freturns( (yyvsp[0].p) ) = Ptype(p);
				(yyvsp[-2].pn)->tp = (yyvsp[0].pt);
			//SYM -- insert in table if not done elsewhere...
				if ( (yyvsp[-2].pn)->n_oper != TNAME && !in_typedef ) {
					insert_name((yyvsp[-2].pn),Ctbl);
				}
				(yyval.p) = (yyvsp[-2].pn);
				if (DECL_TYPE == -1) DECL_TYPE = 0;
			}
#line 4741 "y.tab.c"
    break;

  case 188: /* decl: tname LP AND ID RP arg_list  */
#line 1952 "gram.y"
                        {
				Pptr p = new ptr( RPTR, 0 );
				Ptyp(p) = new basetype(TYPE,(yyvsp[-5].pn));
				Freturns( (yyvsp[0].p) ) = Ptype(p);
				(yyvsp[-2].pn)->tp = (yyvsp[0].pt);
			//SYM -- insert in table if not done elsewhere...
				if ( (yyvsp[-2].pn)->n_oper != TNAME && !in_typedef ) {
					insert_name((yyvsp[-2].pn),Ctbl);
				}
				(yyval.p) = (yyvsp[-2].pn);
				if (DECL_TYPE == -1) DECL_TYPE = 0;
			}
#line 4758 "y.tab.c"
    break;

  case 189: /* decl: tname LP elist RP  */
#line 1965 "gram.y"
                        {	Pname n = (yyvsp[-3].pn);
				(yyval.p) = Ncopy((yyvsp[-3].pn));
				//??? what about qualified tname?
				//SYM -- change -- do not if ctor def...
			//XXXXX defer until name::normalize()?
				if ( !in_typedef
				&&  (ccl==0 || strcmp(n->string,ccl->string)) )
					n->hide();
				(yyval.pn)->n_oper = TNAME;
				(yyval.pn)->tp = new fct(0,(yyvsp[-1].pn),1);
			}
#line 4774 "y.tab.c"
    break;

  case 190: /* decl: tname LP RP fct_attributes  */
#line 1977 "gram.y"
                        { /* function with no argument */
				Pname n = (yyvsp[-3].pn);
				(yyval.p) = Ncopy((yyvsp[-3].pn));
				//SYM -- change -- do not if ctor def...
				if ( !in_typedef
				&&  (ccl==0 || strcmp(n->string,ccl->string)) )
					n->hide();
 				(yyval.pn)->n_oper = TNAME;
 				(yyval.pn)->tp = new fct(0,0,1);
 				Pfct((yyval.pn)->tp)->f_const = ((yyvsp[0].i) & 1);
			}
#line 4790 "y.tab.c"
    break;

  case 191: /* decl: tname LP MEMPTR decl RP arg_list  */
#line 1989 "gram.y"
                        {	memptrdcl((yyvsp[-3].pn),(yyvsp[-5].pn),(yyvsp[0].pt),(yyvsp[-2].pn));
				(yyval.p) = (yyvsp[-2].p);
			}
#line 4798 "y.tab.c"
    break;

  case 192: /* decl: fname  */
#line 1993 "gram.y"
                        {//SYM -- insert in table if appropriate...
			 //SYM    n_oper == TNAME => tname already hidden
			 //SYM    other !=0 values of n_oper => op or dtor
			 //SYM -- enter non-oper names as well as TNAMEs
			 //SYM    in parsing table to handle "1.5 namespace"
			 //SYM    in all scopes, since dcl does not build
			 //SYM    the complete table until after functions
			 //SYM    / classdefs are parsed.
			 //SYM friends are processed in norm.c
			 //SYM    to handle 'friend x;' etc
				if ( (yyvsp[0].pn)->n_oper == 0
				&&  !in_typedef && !in_friend ) {
				    //SYM do not hide ctor name...
				    if ( ccl==0 || parsing_class_members==0
				    ||   strcmp(ccl->string,(yyvsp[0].pn)->string)) {
					Pname n = new name; *n = *(yyvsp[0].pn);
					insert_name(n,Ctbl);
				    }
				}
			}
#line 4823 "y.tab.c"
    break;

  case 193: /* decl: ID DOT fname  */
#line 2014 "gram.y"
                        {	(yyval.p) = Ncopy((yyvsp[0].pn));
				//$<pn>$->n_qualifier = $1;
				error("`.' used for qualification; please use `::'");
			}
#line 4832 "y.tab.c"
    break;

  case 194: /* decl: scope_qualifiers fname  */
#line 2019 "gram.y"
                        {	(yyval.p) = (yyvsp[0].p);
				//SYM if ( $<pn>1 != sta_name ) {
    				//SYM	set_scope($<pn>1); 
					if ( (yyvsp[-1].pn) == sta_name 
    					&&   (yyval.pn)->n_oper==DTOR )
						error("bad syntax for destructor ::%n",(yyval.pn));
    					(yyval.pn)->n_qualifier = (yyvsp[-1].pn);
				//SYM }
			}
#line 4846 "y.tab.c"
    break;

  case 195: /* decl: scope_qualifiers ID DOT fname  */
#line 2029 "gram.y"
                        {	(yyval.p) = Ncopy((yyvsp[0].pn));
				//$<pn>$->n_qualifier = $<pn>1;//SYM $2;
				error("`.' used for qualification; please use `::'");
				error("non-type qualifier%n",(yyvsp[-2].pn));
				//if ( $<pn>1 != sta_name ) {
    				//SYM	set_scope($<pn>1); 
    				//	$<pn>2->n_qualifier = $<pn>1;
				//}
			}
#line 4860 "y.tab.c"
    break;

  case 196: /* decl: ptr decl  */
#line 2039 "gram.y"
                        {	Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (yyvsp[-1].pt);
				(yyval.p) = (yyvsp[0].p);
			}
#line 4869 "y.tab.c"
    break;

  case 197: /* decl: ptr tname  */
#line 2044 "gram.y"
                        {	(yyval.p) = Ncopy((yyvsp[0].pn));
				//??? what about qualified tnames?
				(yyval.pn)->n_oper = TNAME;
				// cannot evaluate at this point: defer until data_dcl
				if ( !in_typedef ) (yyvsp[0].pn)->hide();//SYM
				else in_tag = (yyvsp[0].pn);//SYM???
				(yyval.pn)->tp = (yyvsp[-1].pt);
			}
#line 4882 "y.tab.c"
    break;

  case 198: /* decl: tname vec  */
#line 2053 "gram.y"
                        {	(yyval.p) = Ncopy((yyvsp[-1].pn));
				//??? what about qualified tnames?
				(yyval.pn)->n_oper = TNAME;
				if ( !in_typedef ) (yyvsp[-1].pn)->hide();//SYM
				else in_tag = (yyvsp[-1].pn);//SYM???
				(yyval.pn)->tp = (yyvsp[0].pt);
			}
#line 4894 "y.tab.c"
    break;

  case 199: /* decl: decl vec  */
#line 2061 "gram.y"
                        {	Vtype((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (yyvsp[0].pt);
			}
#line 4902 "y.tab.c"
    break;

  case 200: /* decl: arg_lp decl RP  */
#line 2078 "gram.y"
                        { 
				(yyval.p) = (yyvsp[-1].p); 
				in_arg_list = 0;
				hoist_al();//SYM end_al($1,0);
				//RESTORE_STATE();
			}
#line 4913 "y.tab.c"
    break;

  case 201: /* arg_decl: ID  */
#line 2087 "gram.y"
                        {//SYM -- insert in table if not done elsewhere...
				if ( (yyvsp[0].pn)->n_oper != TNAME ) {
					Pname n = new name; *n = *(yyvsp[0].pn);
					insert_name(n,Ctbl);
				}
				(yyval.p) = (yyvsp[0].pn);
			}
#line 4925 "y.tab.c"
    break;

  case 202: /* arg_decl: ptr qualified_tname  */
#line 2095 "gram.y"
                        {	(yyval.p) = Ncopy((yyvsp[0].pn));
				(yyval.pn)->n_oper = TNAME;
				(yyvsp[0].pn)->hide();
				(yyval.pn)->tp = (yyvsp[-1].pt);
			}
#line 4935 "y.tab.c"
    break;

  case 203: /* arg_decl: %empty  */
#line 2101 "gram.y"
                        {	
				(yyval.p) = new name; 
				NOT_EXPECT_ID();
			}
#line 4944 "y.tab.c"
    break;

  case 204: /* arg_decl: ptr arg_decl  */
#line 2106 "gram.y"
                        {	Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (Ptype)(yyvsp[-1].p);
				(yyval.p) = (yyvsp[0].p);
			}
#line 4953 "y.tab.c"
    break;

  case 205: /* arg_decl: arg_decl vec  */
#line 2111 "gram.y"
                        {	Vtype((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 4961 "y.tab.c"
    break;

  case 206: /* arg_decl: arg_decl arg_list  */
#line 2115 "gram.y"
                        {	Freturns((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 4969 "y.tab.c"
    break;

  case 207: /* arg_decl: arg_lp arg_decl RP  */
#line 2131 "gram.y"
                        { 
// error('d', "arg_lp arg_decl rp in_arg_list: %d", in_arg_list );
				(yyval.p) = (yyvsp[-1].p); 
				in_arg_list = 0;
				hoist_al();//SYM end_al($1,0);
				//RESTORE_STATE();
			}
#line 4981 "y.tab.c"
    break;

  case 208: /* new_decl: %empty  */
#line 2141 "gram.y"
                        {	(yyval.p) = new name; }
#line 4987 "y.tab.c"
    break;

  case 209: /* new_decl: ptr new_decl  */
#line 2143 "gram.y"
                        {	Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (Ptype)(yyvsp[-1].p);
				(yyval.p) = (yyvsp[0].p);
                                NOT_EXPECT_ID();
			}
#line 4997 "y.tab.c"
    break;

  case 210: /* new_decl: new_decl vec  */
#line 2149 "gram.y"
                        {	Vtype((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 5005 "y.tab.c"
    break;

  case 211: /* cast_decl: %empty  */
#line 2154 "gram.y"
                               { (yyval.p) = new name; }
#line 5011 "y.tab.c"
    break;

  case 212: /* cast_decl: ptr cast_decl  */
#line 2156 "gram.y"
                        {	Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (Ptype)(yyvsp[-1].p);
				(yyval.p) = (yyvsp[0].p);
				NOT_EXPECT_ID();
			}
#line 5021 "y.tab.c"
    break;

  case 213: /* cast_decl: cast_decl vec  */
#line 2162 "gram.y"
                        {	Vtype((yyvsp[0].p)) = (yyvsp[-1].pn)->tp;
				(yyvsp[-1].pn)->tp = (Ptype)(yyvsp[0].p);
			}
#line 5029 "y.tab.c"
    break;

  case 214: /* cast_decl: LP cast_decl RP arg_list  */
#line 2166 "gram.y"
                        {	Freturns((yyvsp[0].p)) = (yyvsp[-2].pn)->tp;
				(yyvsp[-2].pn)->tp = (yyvsp[0].pt);
				(yyval.p) = (yyvsp[-2].p);
			}
#line 5038 "y.tab.c"
    break;

  case 215: /* cast_decl: LP cast_decl RP vec  */
#line 2171 "gram.y"
                        {	Vtype((yyvsp[0].p)) = (yyvsp[-2].pn)->tp;
				(yyvsp[-2].pn)->tp = (yyvsp[0].pt);
				(yyval.p) = (yyvsp[-2].p);
			}
#line 5047 "y.tab.c"
    break;

  case 216: /* c_decl: %empty  */
#line 2178 "gram.y"
                        {	(yyval.p) = new name; }
#line 5053 "y.tab.c"
    break;

  case 217: /* c_decl: ptr c_decl  */
#line 2180 "gram.y"
                        {	Ptyp((yyvsp[-1].p)) = (yyvsp[0].pn)->tp;
				(yyvsp[0].pn)->tp = (Ptype)(yyvsp[-1].p);
				(yyval.p) = (yyvsp[0].p);
			}
#line 5062 "y.tab.c"
    break;

  case 218: /* stmt_list: %empty  */
#line 2190 "gram.y"
                        {
				(yyval.p) = 0; 
			}
#line 5070 "y.tab.c"
    break;

  case 219: /* stmt_list: stmt_list TEMPLATE  */
#line 2194 "gram.y"
                        {
				error( "ZizedTD must be atG, not local scope" );
				error('i', "cannot recover from previous error" );
			}
#line 5079 "y.tab.c"
    break;

  case 220: /* stmt_list: stmt_list caselab_stmt  */
#line 2199 "gram.y"
                        {	
				if ((yyvsp[0].p))
					if ((yyvsp[-1].p))
						(yyvsp[-1].sl)->add((yyvsp[0].ps));
					else {
						(yyval.sl) =  new slist((yyvsp[0].ps));
						stmt_seen = 1;
					}
			}
#line 5093 "y.tab.c"
    break;

  case 221: /* caselab_stmt: caselablist statement  */
#line 2210 "gram.y"
                        {
				(yyval.p) = (yyvsp[0].p);
				if ((yyvsp[0].p))	stmt_seen = 1;
			}
#line 5102 "y.tab.c"
    break;

  case 222: /* caselablist: %empty  */
#line 2217 "gram.y"
                        {
				(yyval.p) = 0;
				check_decl();
			}
#line 5111 "y.tab.c"
    break;

  case 223: /* condition: LP e RP  */
#line 2224 "gram.y"
                        {	(yyval.p) = (yyvsp[-1].p);
			/*	if ($<pe>$ == dummy) error("empty condition");*/
				stmt_seen = 1;
			}
#line 5120 "y.tab.c"
    break;

  case 224: /* $@14: %empty  */
#line 2231 "gram.y"
                        {	PUSH_BLOCK_SCOPE();//SYM
				cd_vec[cdi] = cd;
				stmt_vec[cdi] = stmt_seen;
				++cdi;
				cd = 0;
				stmt_seen = 0;
				//SYM -- tn stuff removed
			}
#line 5133 "y.tab.c"
    break;

  case 225: /* block: LC $@14 stmt_list RC  */
#line 2240 "gram.y"
                        {	Pname n = name_unlist(cd);
				Pstmt ss = stmt_unlist((yyvsp[-1].sl));
				(yyval.p) = new block((yyvsp[-3].l),n,ss,(yyvsp[0].l));
				//SYM -- tn stuff removed
				cd = cd_vec[--cdi];
				stmt_seen = stmt_vec[cdi];
				if (cdi < 0) error('i',"block level(%d)",cdi);
				NOT_EXPECT_ID();
				(yyval.ps)->k_tbl = Ctbl;//SYM
                        	POP_SCOPE();//SYM
			}
#line 5149 "y.tab.c"
    break;

  case 226: /* block: LC RC  */
#line 2252 "gram.y"
                        { (yyval.p) = new block((yyvsp[-1].l),0,0,(yyvsp[0].l)); NOT_EXPECT_ID();
			  if ( Ctbl->k_id == ARG ) POP_SCOPE();//SYM
			}
#line 5157 "y.tab.c"
    break;

  case 227: /* block: LC error RC  */
#line 2256 "gram.y"
                        { (yyval.p) = new block((yyvsp[-2].l),0,0,(yyvsp[0].l)); NOT_EXPECT_ID();
			  if ( Ctbl->k_id == ARG ) POP_SCOPE();//SYM
			}
#line 5165 "y.tab.c"
    break;

  case 228: /* simple: ee  */
#line 2262 "gram.y"
                        {	(yyval.p) = new estmt(SM,curloc,(yyvsp[0].pe),0);	}
#line 5171 "y.tab.c"
    break;

  case 229: /* simple: BREAK  */
#line 2264 "gram.y"
                        {	(yyval.p) = new stmt(BREAK,(yyvsp[0].l),0); }
#line 5177 "y.tab.c"
    break;

  case 230: /* simple: CONTINUE  */
#line 2266 "gram.y"
                        {	(yyval.p) = new stmt(CONTINUE,(yyvsp[0].l),0); }
#line 5183 "y.tab.c"
    break;

  case 231: /* simple: GOTO ID  */
#line 2268 "gram.y"
                        {	(yyval.p) = new lstmt(GOTO,(yyvsp[-1].l),(yyvsp[0].pn),0); }
#line 5189 "y.tab.c"
    break;

  case 232: /* $@15: %empty  */
#line 2269 "gram.y"
                      { stmt_seen=1; }
#line 5195 "y.tab.c"
    break;

  case 233: /* simple: DO $@15 caselab_stmt WHILE condition  */
#line 2270 "gram.y"
                        {	(yyval.p) = new estmt(DO,(yyvsp[-4].l),(yyvsp[0].pe),(yyvsp[-2].ps)); }
#line 5201 "y.tab.c"
    break;

  case 234: /* simple: ASM LP STRING RP  */
#line 2272 "gram.y"
                        {	
				if (stmt_seen)
					(yyval.p) = new estmt(ASM,curloc,(Pexpr)(yyvsp[-1].s),0);
				else {
					Pname n = new name(make_name('A'));
					n->tp = new basetype(ASM,(Pname)(yyvsp[-1].s));
					if (cd)
						cd->add_list(n);
					else
						cd = new nlist(n);
					(yyval.p) = 0;
				}
			}
#line 5219 "y.tab.c"
    break;

  case 235: /* $@16: %empty  */
#line 2287 "gram.y"
                  {
			if ( NEXTTOK() != SM ) {
				error("`;' missing afterS");
				la_backup(yychar,yylval);
				yychar = SM;
			}
		  }
#line 5231 "y.tab.c"
    break;

  case 238: /* statement: SM  */
#line 2298 "gram.y"
                        {	(yyval.p) = new estmt(SM,curloc,dummy,0); }
#line 5237 "y.tab.c"
    break;

  case 239: /* statement: RETURN e SM  */
#line 2300 "gram.y"
                        {	(yyval.p) = new estmt(RETURN,(yyvsp[-2].l),(yyvsp[-1].pe),0); }
#line 5243 "y.tab.c"
    break;

  case 240: /* statement: TYPE STRING block  */
#line 2302 "gram.y"
                        {
				error("local linkage specification");
				(yyval.p) = (yyvsp[0].pn);
			}
#line 5252 "y.tab.c"
    break;

  case 241: /* statement: data_dcl  */
#line 2307 "gram.y"
                        {	Pname n = (yyvsp[0].pn);
				if (n) {
//error('d',"adding local dcl of%n%t ll %d in_typedef%t",n,n->tp,n->lex_level,in_typedef);
					if (stmt_seen) {
						(yyval.p) = new block(n->where,n,0);
						(yyval.ps)->base = DCL;
						(yyval.ps)->k_tbl = Ctbl;//SYM
					}
					else {
						if (cd)
							cd->add_list(n);
						else
							cd = new nlist(n);
						(yyval.p) = 0;
					}
				} // if n
				else if (stmt_seen) {
					(yyval.p) = new block(curloc,0,0);
					(yyval.ps)->base = FDCL;
				}
			}
#line 5278 "y.tab.c"
    break;

  case 242: /* statement: att_fct_def  */
#line 2329 "gram.y"
                        {
				Pname n = (yyvsp[0].pn);
				if (!templp->in_progress)
					error(&n->where,"%n's definition is nested (did you forget a ``}''?)",n);
				if (cd)
					cd->add_list(n);
				else
					cd = new nlist(n);
				(yyval.p) = 0;
			}
#line 5293 "y.tab.c"
    break;

  case 244: /* statement: IF condition caselab_stmt  */
#line 2341 "gram.y"
                        {	(yyval.p) = new ifstmt((yyvsp[-2].l),(yyvsp[-1].pe),(yyvsp[0].ps),0); }
#line 5299 "y.tab.c"
    break;

  case 245: /* statement: IF condition caselab_stmt ELSE caselab_stmt  */
#line 2343 "gram.y"
                        {	(yyval.p) = new ifstmt((yyvsp[-4].l),(yyvsp[-3].pe),(yyvsp[-2].ps),(yyvsp[0].ps)); }
#line 5305 "y.tab.c"
    break;

  case 246: /* statement: WHILE condition caselab_stmt  */
#line 2345 "gram.y"
                        {	(yyval.p) = new estmt(WHILE,(yyvsp[-2].l),(yyvsp[-1].pe),(yyvsp[0].ps)); }
#line 5311 "y.tab.c"
    break;

  case 247: /* $@17: %empty  */
#line 2346 "gram.y"
                          { stmt_seen=1; }
#line 5317 "y.tab.c"
    break;

  case 248: /* statement: FOR LP $@17 caselab_stmt e SM e RP caselab_stmt  */
#line 2347 "gram.y"
                        {	(yyval.p) = new forstmt((yyvsp[-8].l),(yyvsp[-5].ps),(yyvsp[-4].pe),(yyvsp[-2].pe),(yyvsp[0].ps)); }
#line 5323 "y.tab.c"
    break;

  case 249: /* $@18: %empty  */
#line 2348 "gram.y"
                           { scd[++scdp] = cd;}
#line 5329 "y.tab.c"
    break;

  case 250: /* statement: SWITCH $@18 condition caselab_stmt  */
#line 2349 "gram.y"
                        {	
				--scdp;
				(yyval.p) = new estmt(SWITCH,(yyvsp[-3].l),(yyvsp[-1].pe),(yyvsp[0].ps)); 
			}
#line 5338 "y.tab.c"
    break;

  case 251: /* @19: %empty  */
#line 2353 "gram.y"
                            { (yyval.pn) = (yyvsp[-1].pn); stmt_seen=1; }
#line 5344 "y.tab.c"
    break;

  case 252: /* statement: ID COLON @19 caselab_stmt  */
#line 2354 "gram.y"
                        {	Pname n = (yyvsp[-1].pn);
				(yyval.p) = new lstmt(LABEL,n->where,n,(yyvsp[0].ps));
			}
#line 5352 "y.tab.c"
    break;

  case 253: /* @20: %empty  */
#line 2357 "gram.y"
                               { (yyval.pn) = new name((yyvsp[-1].pn)->string); stmt_seen=1; }
#line 5358 "y.tab.c"
    break;

  case 254: /* statement: TNAME COLON @20 caselab_stmt  */
#line 2358 "gram.y"
                        {	Pname n = (yyvsp[-1].pn);
				(yyval.p) = new lstmt(LABEL,n->where,n,(yyvsp[0].ps));
			}
#line 5366 "y.tab.c"
    break;

  case 255: /* $@21: %empty  */
#line 2361 "gram.y"
                        { stmt_seen=1; }
#line 5372 "y.tab.c"
    break;

  case 256: /* statement: CASE $@21 e COLON caselab_stmt  */
#line 2362 "gram.y"
                        {	
				if (scdp>=0 && scd[scdp]!=cd && cd && decl_with_init(cd)) error("jump past initializer (did you forget a '{ }'?)");
				if ((yyvsp[-2].pe) == dummy) error("empty case label");
				(yyval.p) = new estmt(CASE,(yyvsp[-4].l),(yyvsp[-2].pe),(yyvsp[0].ps));
			}
#line 5382 "y.tab.c"
    break;

  case 257: /* @22: %empty  */
#line 2367 "gram.y"
                                 { stmt_seen=1; }
#line 5388 "y.tab.c"
    break;

  case 258: /* statement: DEFAULT COLON @22 caselab_stmt  */
#line 2368 "gram.y"
                        {	
				if (scdp>=0 && scd[scdp]!=cd && cd && (yyvsp[-1].pe) && decl_with_init(cd)) error("jump past initializer (did you forget a '{ }'?)");
				(yyval.p) = new stmt(DEFAULT,(yyvsp[-3].l),(yyvsp[0].ps)); 
			}
#line 5397 "y.tab.c"
    break;

  case 259: /* statement: TRY block handler_list  */
#line 2373 "gram.y"
                        { (yyval.p) = new handler( (yyvsp[-1].ps), stmt_unlist((yyvsp[0].sl)) ); }
#line 5403 "y.tab.c"
    break;

  case 260: /* handler_list: %empty  */
#line 2378 "gram.y"
                        { (yyval.sl) = 0; }
#line 5409 "y.tab.c"
    break;

  case 261: /* handler_list: handler_list handler  */
#line 2380 "gram.y"
                        {	
				if ((yyvsp[0].ps))
					if ((yyvsp[-1].sl))
						(yyvsp[-1].sl)->add((yyvsp[0].ps));
					else {
						(yyval.sl) =  new slist((yyvsp[0].ps));
						stmt_seen = 1;
					}
			}
#line 5423 "y.tab.c"
    break;

  case 262: /* handler: CATCH exception_type block  */
#line 2392 "gram.y"
                        {
			    if ( (yyvsp[-1].pn) ) {
				(yyvsp[-1].pn)->n_list = (yyvsp[0].ps)->d;
				(yyvsp[0].ps)->d = (yyvsp[-1].pn);
			    }
			    (yyval.ps) = (yyvsp[0].ps);
			}
#line 5435 "y.tab.c"
    break;

  case 263: /* exception_type: arg_lp type arg_decl RP  */
#line 2403 "gram.y"
                        {	in_arg_list = 0;
				(yyval.pn) = Ndata((yyvsp[-2].p),(yyvsp[-1].pn));
				if ( (yyval.pn)->string == 0 )
					(yyval.pn) = 0;
				else
					(yyval.pn)->base = CATCH;
			}
#line 5447 "y.tab.c"
    break;

  case 264: /* exception_type: LP ELLIPSIS RP  */
#line 2411 "gram.y"
                        { (yyval.pn) = 0; }
#line 5453 "y.tab.c"
    break;

  case 265: /* elist: ex_list  */
#line 2418 "gram.y"
                        {	Pexpr e = expr_unlist((yyvsp[0].el));
				while (e && e->e1==dummy) {
					register Pexpr ee2 = e->e2;
					if (ee2) error("EX inEL");
					delete e;
					e = ee2;
				}
				(yyval.p) = e;
			}
#line 5467 "y.tab.c"
    break;

  case 266: /* ex_list: initializer  */
#line 2430 "gram.y"
                        {	(yyval.el) = new elist(new expr(ELIST,(yyvsp[0].pe),0)); }
#line 5473 "y.tab.c"
    break;

  case 267: /* ex_list: ex_list CM initializer  */
#line 2432 "gram.y"
                        {	(yyvsp[-2].el)->add(new expr(ELIST,(yyvsp[0].pe),0)); }
#line 5479 "y.tab.c"
    break;

  case 269: /* initializer: LC elist RC  */
#line 2437 "gram.y"
                        {
  			  	if ( in_arg_list ) 
       			  		error( "syntax error: IrL not permitted in AL" );
				else if ( in_binit_list )
					error( "syntax error: IrL not permitted inMIr" );
  			  	else 
					init_seen = 1;
				Pexpr e;
				if ((yyvsp[-1].p))
					e = (yyvsp[-1].pe);
				else
					e = new expr(ELIST,dummy,0);
				(yyval.p) = new expr(ILIST,e,0);
			}
#line 5498 "y.tab.c"
    break;

  case 270: /* ee: ee ASSIGN ee  */
#line 2454 "gram.y"
                        {	bbinop:	(yyval.p) = new expr((yyvsp[-1].t),(yyvsp[-2].pe),(yyvsp[0].pe)); }
#line 5504 "y.tab.c"
    break;

  case 271: /* ee: ee PLUS ee  */
#line 2455 "gram.y"
                                {	goto bbinop; }
#line 5510 "y.tab.c"
    break;

  case 272: /* ee: ee MINUS ee  */
#line 2456 "gram.y"
                                {	goto bbinop; }
#line 5516 "y.tab.c"
    break;

  case 273: /* ee: ee MUL ee  */
#line 2457 "gram.y"
                                {	goto bbinop; }
#line 5522 "y.tab.c"
    break;

  case 274: /* ee: ee AND ee  */
#line 2458 "gram.y"
                                {	goto bbinop; }
#line 5528 "y.tab.c"
    break;

  case 275: /* ee: ee OR ee  */
#line 2459 "gram.y"
                                {	goto bbinop; }
#line 5534 "y.tab.c"
    break;

  case 276: /* ee: ee ER ee  */
#line 2460 "gram.y"
                                {	goto bbinop; }
#line 5540 "y.tab.c"
    break;

  case 277: /* ee: ee SHIFTOP ee  */
#line 2461 "gram.y"
                                        { 	goto bbinop; }
#line 5546 "y.tab.c"
    break;

  case 278: /* ee: ee EQUOP ee  */
#line 2462 "gram.y"
                                {	goto bbinop; }
#line 5552 "y.tab.c"
    break;

  case 279: /* ee: ee DIVOP ee  */
#line 2463 "gram.y"
                                {	goto bbinop; }
#line 5558 "y.tab.c"
    break;

  case 280: /* ee: ee RELOP ee  */
#line 2464 "gram.y"
                                {	goto bbinop; }
#line 5564 "y.tab.c"
    break;

  case 281: /* ee: ee GT ee  */
#line 2465 "gram.y"
                                {	goto bbinop; }
#line 5570 "y.tab.c"
    break;

  case 282: /* ee: ee LT ee  */
#line 2466 "gram.y"
                                {	goto bbinop; }
#line 5576 "y.tab.c"
    break;

  case 283: /* ee: ee ANDAND ee  */
#line 2467 "gram.y"
                                {	goto bbinop; }
#line 5582 "y.tab.c"
    break;

  case 284: /* ee: ee OROR ee  */
#line 2468 "gram.y"
                                {	goto bbinop; }
#line 5588 "y.tab.c"
    break;

  case 285: /* ee: ee ASOP ee  */
#line 2469 "gram.y"
                                {	goto bbinop; }
#line 5594 "y.tab.c"
    break;

  case 286: /* ee: ee CM ee  */
#line 2470 "gram.y"
                                {	goto bbinop; }
#line 5600 "y.tab.c"
    break;

  case 287: /* ee: ee QUEST ee COLON ee  */
#line 2472 "gram.y"
                        {	(yyval.p) = new qexpr((yyvsp[-4].pe),(yyvsp[-2].pe),(yyvsp[0].pe)); }
#line 5606 "y.tab.c"
    break;

  case 288: /* ee: ee REFMUL ee  */
#line 2474 "gram.y"
                        {	(yyval.p) = new expr((yyvsp[-1].t),(yyvsp[-2].pe),(yyvsp[0].pe)); }
#line 5612 "y.tab.c"
    break;

  case 289: /* ee: DELETE term  */
#line 2476 "gram.y"
                        { (yyval.p) = new expr(DELETE,(yyvsp[0].pe),0); }
#line 5618 "y.tab.c"
    break;

  case 290: /* ee: DELETE LB e RB term  */
#line 2478 "gram.y"
                        {
				if((yyvsp[-2].pe) != dummy) {
					if ( warning_opt || strict_opt )
						error(strict_opt?0:'w',"v in `delete[v]' is redundant; use `delete[] instead (anachronism)");
				}
				(yyval.p) = new expr(DELETE,(yyvsp[0].pe),(yyvsp[-2].pe));
			}
#line 5630 "y.tab.c"
    break;

  case 291: /* ee: MEM DELETE term  */
#line 2486 "gram.y"
                        {	(yyval.p) = new expr(GDELETE,(yyvsp[0].pe),0); }
#line 5636 "y.tab.c"
    break;

  case 292: /* ee: MEM DELETE LB e RB term  */
#line 2488 "gram.y"
                        {
				if((yyvsp[-2].pe) != dummy) { 
					if ( warning_opt || strict_opt )
						error(strict_opt?0:'w',"v in `::delete[v]' is redundant; use `::delete[] instead (anachronism)");
				}
				(yyval.p) = new expr(DELETE,(yyvsp[0].pe),(yyvsp[-2].pe));
			}
#line 5648 "y.tab.c"
    break;

  case 294: /* ee: THROW term  */
#line 2497 "gram.y"
                        { (yyval.p) = dummy; }
#line 5654 "y.tab.c"
    break;

  case 295: /* e: e ASSIGN e  */
#line 2501 "gram.y"
                        {	binop:	(yyval.p) = new expr((yyvsp[-1].t),(yyvsp[-2].pe),(yyvsp[0].pe)); }
#line 5660 "y.tab.c"
    break;

  case 296: /* e: e PLUS e  */
#line 2502 "gram.y"
                                {	goto binop; }
#line 5666 "y.tab.c"
    break;

  case 297: /* e: e MINUS e  */
#line 2503 "gram.y"
                                {	goto binop; }
#line 5672 "y.tab.c"
    break;

  case 298: /* e: e MUL e  */
#line 2504 "gram.y"
                                {	goto binop; }
#line 5678 "y.tab.c"
    break;

  case 299: /* e: e AND e  */
#line 2505 "gram.y"
                                {	goto binop; }
#line 5684 "y.tab.c"
    break;

  case 300: /* e: e OR e  */
#line 2506 "gram.y"
                                {	goto binop; }
#line 5690 "y.tab.c"
    break;

  case 301: /* e: e ER e  */
#line 2507 "gram.y"
                                {	goto binop; }
#line 5696 "y.tab.c"
    break;

  case 302: /* e: e SHIFTOP e  */
#line 2508 "gram.y"
                                { 	goto binop; }
#line 5702 "y.tab.c"
    break;

  case 303: /* e: e EQUOP e  */
#line 2509 "gram.y"
                                {	goto binop; }
#line 5708 "y.tab.c"
    break;

  case 304: /* e: e DIVOP e  */
#line 2510 "gram.y"
                                {	goto binop; }
#line 5714 "y.tab.c"
    break;

  case 305: /* e: e RELOP e  */
#line 2511 "gram.y"
                                {	goto binop; }
#line 5720 "y.tab.c"
    break;

  case 306: /* e: e LT e  */
#line 2512 "gram.y"
                                {	goto binop; }
#line 5726 "y.tab.c"
    break;

  case 307: /* e: e GT e  */
#line 2513 "gram.y"
                                {	goto binop; }
#line 5732 "y.tab.c"
    break;

  case 308: /* e: e ANDAND e  */
#line 2514 "gram.y"
                                {	goto binop; }
#line 5738 "y.tab.c"
    break;

  case 309: /* e: e OROR e  */
#line 2515 "gram.y"
                                {	goto binop; }
#line 5744 "y.tab.c"
    break;

  case 310: /* e: e ASOP e  */
#line 2516 "gram.y"
                                {	goto binop; }
#line 5750 "y.tab.c"
    break;

  case 311: /* e: e CM e  */
#line 2517 "gram.y"
                                {	goto binop; }
#line 5756 "y.tab.c"
    break;

  case 312: /* e: e QUEST e COLON e  */
#line 2519 "gram.y"
                        {	(yyval.p) = new qexpr((yyvsp[-4].pe),(yyvsp[-2].pe),(yyvsp[0].pe)); }
#line 5762 "y.tab.c"
    break;

  case 313: /* e: e REFMUL e  */
#line 2521 "gram.y"
                        {	(yyval.p) = new expr((yyvsp[-1].t),(yyvsp[-2].pe),(yyvsp[0].pe)); }
#line 5768 "y.tab.c"
    break;

  case 314: /* e: DELETE term  */
#line 2523 "gram.y"
                        {	(yyval.p) = new expr(DELETE,(yyvsp[0].pe),0); }
#line 5774 "y.tab.c"
    break;

  case 315: /* e: DELETE LB e RB term  */
#line 2525 "gram.y"
                        {
				if((yyvsp[-2].pe) != dummy) {
					if ( warning_opt || strict_opt )
						error(strict_opt?0:'w',"v in `delete[v]' is redundant; use `delete[] instead (anachronism)");
				}
				(yyval.p) = new expr(DELETE,(yyvsp[0].pe),(yyvsp[-2].pe));
			}
#line 5786 "y.tab.c"
    break;

  case 316: /* e: MEM DELETE term  */
#line 2533 "gram.y"
                        {	(yyval.p) = new expr(GDELETE,(yyvsp[0].pe),0); }
#line 5792 "y.tab.c"
    break;

  case 317: /* e: MEM DELETE LB e RB term  */
#line 2535 "gram.y"
                        {
				if((yyvsp[-2].pe) != dummy) {
					if ( warning_opt || strict_opt )
						error(strict_opt?0:'w',"v in `::delete[v]' is redundant; use `::delete[] instead (anachronism)");
				}
				(yyval.p) = new expr(DELETE,(yyvsp[0].pe),(yyvsp[-2].pe));
			}
#line 5804 "y.tab.c"
    break;

  case 318: /* e: term  */
#line 2542 "gram.y"
                        { 
			init_seen = 0; 
			}
#line 5812 "y.tab.c"
    break;

  case 319: /* e: THROW term  */
#line 2546 "gram.y"
                        { (yyval.p) = dummy; }
#line 5818 "y.tab.c"
    break;

  case 320: /* e: %empty  */
#line 2548 "gram.y"
                        {	(yyval.p) = dummy; }
#line 5824 "y.tab.c"
    break;

  case 321: /* term: NEW cast_type  */
#line 2551 "gram.y"
                                        { goto new1; }
#line 5830 "y.tab.c"
    break;

  case 322: /* term: NEW new_type  */
#line 2553 "gram.y"
                        {	new1:
				Ptype t = (yyvsp[0].pn)->tp;
				(yyval.p) = new texpr(NEW,t,0);
				--in_new;
			}
#line 5840 "y.tab.c"
    break;

  case 323: /* term: MEM NEW cast_type  */
#line 2558 "gram.y"
                                        { goto new3; }
#line 5846 "y.tab.c"
    break;

  case 324: /* term: MEM NEW new_type  */
#line 2560 "gram.y"
                        {	new3:
				Ptype t = (yyvsp[0].pn)->tp;
 				(yyval.p) = new texpr(GNEW,t,0);
				--in_new;
 			}
#line 5856 "y.tab.c"
    break;

  case 325: /* term: term ICOP  */
#line 2566 "gram.y"
                        {	(yyval.p) = new expr((yyvsp[0].t),(yyvsp[-1].pe),0); }
#line 5862 "y.tab.c"
    break;

  case 326: /* term: cast_type term  */
#line 2568 "gram.y"
                        {
				(yyval.p) = new texpr(CAST,(yyvsp[-1].pn)->tp,(yyvsp[0].pe));
			}
#line 5870 "y.tab.c"
    break;

  case 327: /* term: MUL term  */
#line 2572 "gram.y"
                        {	(yyval.p) = new expr(DEREF,(yyvsp[0].pe),0); }
#line 5876 "y.tab.c"
    break;

  case 328: /* term: AND term  */
#line 2574 "gram.y"
                        {	(yyval.p) = new expr(ADDROF,0,(yyvsp[0].pe)); }
#line 5882 "y.tab.c"
    break;

  case 329: /* term: MINUS term  */
#line 2576 "gram.y"
                        {	(yyval.p) = new expr(UMINUS,0,(yyvsp[0].pe)); }
#line 5888 "y.tab.c"
    break;

  case 330: /* term: PLUS term  */
#line 2578 "gram.y"
                        {	(yyval.p) = new expr(UPLUS,0,(yyvsp[0].pe)); }
#line 5894 "y.tab.c"
    break;

  case 331: /* term: NOT term  */
#line 2580 "gram.y"
                        {	(yyval.p) = new expr(NOT,0,(yyvsp[0].pe)); }
#line 5900 "y.tab.c"
    break;

  case 332: /* term: COMPL term  */
#line 2582 "gram.y"
                        {	(yyval.p) = new expr(COMPL,0,(yyvsp[0].pe)); }
#line 5906 "y.tab.c"
    break;

  case 333: /* term: ICOP term  */
#line 2584 "gram.y"
                        {	(yyval.p) = new expr((yyvsp[-1].t),0,(yyvsp[0].pe)); }
#line 5912 "y.tab.c"
    break;

  case 334: /* term: SIZEOF term  */
#line 2586 "gram.y"
                        {	
				(yyval.p) = new texpr(SIZEOF,0,(yyvsp[0].pe)); 
				--in_sizeof;
			}
#line 5921 "y.tab.c"
    break;

  case 335: /* term: SIZEOF cast_type  */
#line 2591 "gram.y"
                        {	
				(yyval.p) = new texpr(SIZEOF,(yyvsp[0].pn)->tp,0); 
				--in_sizeof;
			}
#line 5930 "y.tab.c"
    break;

  case 336: /* term: term LB e RB  */
#line 2596 "gram.y"
                        {	(yyval.p) = new expr(DEREF,(yyvsp[-3].pe),(yyvsp[-1].pe)); }
#line 5936 "y.tab.c"
    break;

  case 337: /* term: term REF prim  */
#line 2598 "gram.y"
                        {	(yyval.p) = new ref(REF,(yyvsp[-2].pe),(yyvsp[0].pn)); }
#line 5942 "y.tab.c"
    break;

  case 338: /* term: term REF MEMQ prim  */
#line 2600 "gram.y"
                        {
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(REF,(yyvsp[-3].pe),(yyvsp[0].pn));
			}
#line 5951 "y.tab.c"
    break;

  case 339: /* term: term REF MEMQ TNAME  */
#line 2605 "gram.y"
                        {	(yyvsp[0].pn) = new name((yyvsp[0].pn)->string);
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(REF,(yyvsp[-3].pe),(yyvsp[0].pn));
			}
#line 5960 "y.tab.c"
    break;

  case 340: /* term: term REF dtorspec  */
#line 2610 "gram.y"
                        {	(yyval.p) = new ref(REF,(yyvsp[-2].pe),(yyvsp[0].pn)); }
#line 5966 "y.tab.c"
    break;

  case 341: /* term: term REF scope_qualifiers prim  */
#line 2612 "gram.y"
                        { // kluge to handle parameterized qualifiers, since
			  //    they are not included in MEMQ
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(REF,(yyvsp[-3].pe),(yyvsp[0].pn));
				if ( (yyvsp[-1].pn) && (yyvsp[-1].pn)->n_template_arg != template_type_formal )
					UNSET_SCOPE();
			}
#line 5978 "y.tab.c"
    break;

  case 342: /* term: term REF scope_qualifiers TNAME  */
#line 2620 "gram.y"
                        { // kluge to handle parameterized qualifiers, since
			  //    they are not included in MEMQ
				(yyvsp[0].pn) = new name((yyvsp[0].pn)->string);
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(REF,(yyvsp[-3].pe),(yyvsp[0].pn));
				if ( (yyvsp[-1].pn) && (yyvsp[-1].pn)->n_template_arg != template_type_formal )
					UNSET_SCOPE();
			}
#line 5991 "y.tab.c"
    break;

  case 343: /* term: term DOT prim  */
#line 2629 "gram.y"
                        {	(yyval.p) = new ref(DOT,(yyvsp[-2].pe),(yyvsp[0].pn)); }
#line 5997 "y.tab.c"
    break;

  case 344: /* term: term DOT MEMQ prim  */
#line 2631 "gram.y"
                        {
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(DOT,(yyvsp[-3].pe),(yyvsp[0].pn));
			}
#line 6006 "y.tab.c"
    break;

  case 345: /* term: term DOT MEMQ TNAME  */
#line 2636 "gram.y"
                        {	(yyvsp[0].pn) = new name((yyvsp[0].pn)->string);
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(DOT,(yyvsp[-3].pe),(yyvsp[0].pn));
			}
#line 6015 "y.tab.c"
    break;

  case 346: /* term: term DOT dtorspec  */
#line 2641 "gram.y"
                        {	(yyval.p) = new ref(DOT,(yyvsp[-2].pe),(yyvsp[0].pn)); }
#line 6021 "y.tab.c"
    break;

  case 347: /* term: term DOT scope_qualifiers prim  */
#line 2643 "gram.y"
                        { // kluge to handle parameterized qualifiers, since
			  //    they are not included in MEMQ
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(DOT,(yyvsp[-3].pe),(yyvsp[0].pn));
				if ( (yyvsp[-1].pn) && (yyvsp[-1].pn)->n_template_arg != template_type_formal )
					UNSET_SCOPE();
			}
#line 6033 "y.tab.c"
    break;

  case 348: /* term: term DOT scope_qualifiers TNAME  */
#line 2651 "gram.y"
                        { // kluge to handle parameterized qualifiers, since
			  //    they are not included in MEMQ
				(yyvsp[0].pn) = new name((yyvsp[0].pn)->string);
				(yyvsp[0].pn)->n_qualifier = (yyvsp[-1].pn);
				(yyval.p) = new ref(DOT,(yyvsp[-3].pe),(yyvsp[0].pn));
				if ( (yyvsp[-1].pn) && (yyvsp[-1].pn)->n_template_arg != template_type_formal )
					UNSET_SCOPE();
			}
#line 6046 "y.tab.c"
    break;

  case 350: /* term: scope_qualifiers prim  */
#line 2661 "gram.y"
                        { // set scope to parse 'C::operator N' where N is in C
			  // still does not handle 'p->operator N'
			  //     (requires either fancier structures or 
			  //     on-the-fly type checking)
				(yyval.p) = Ncopy((yyvsp[0].pn));
				(yyval.pn)->n_qualifier = (yyvsp[-1].pn);
				if ( (yyvsp[-1].pn) && (yyvsp[-1].pn)->n_template_arg != template_type_formal )
					UNSET_SCOPE();
			}
#line 6060 "y.tab.c"
    break;

  case 351: /* term: tn_list COMPL tag  */
#line 2671 "gram.y"
                        {
				(yyval.p) = dummy_dtor();
				(yyval.pn)->n_qualifier = (yyvsp[-2].pn);
				(yyval.pn)->n_dtag = (yyvsp[0].pn);
			}
#line 6070 "y.tab.c"
    break;

  case 352: /* term: tn_list COMPL TYPE  */
#line 2677 "gram.y"
                        {	
				(yyval.p) = dummy_dtor( (yyvsp[0].t), (yyvsp[0].t) );
				(yyval.pn)->n_qualifier = (yyvsp[-2].pn);
			}
#line 6079 "y.tab.c"
    break;

  case 353: /* term: term_elist  */
#line 2682 "gram.y"
                        {
			if ( init_seen )
     				error( "syntax error:IrL illegal within ()");
			}
#line 6088 "y.tab.c"
    break;

  case 354: /* term: term_lp e RP  */
#line 2688 "gram.y"
                        {
				if ( (yyvsp[-1].p) == dummy )
					error("syntax error: nullE");
				(yyval.p) = (yyvsp[-1].p);
			}
#line 6098 "y.tab.c"
    break;

  case 355: /* term: ZERO  */
#line 2694 "gram.y"
                        {	(yyval.p) = zero; }
#line 6104 "y.tab.c"
    break;

  case 356: /* term: ICON  */
#line 2696 "gram.y"
                        {	(yyval.p) = new expr(ICON,0,0);
				(yyval.pe)->string = copy_if_need_be((yyvsp[0].s));
			}
#line 6112 "y.tab.c"
    break;

  case 357: /* term: FCON  */
#line 2700 "gram.y"
                        {	(yyval.p) = new expr(FCON,0,0);
				(yyval.pe)->string = copy_if_need_be((yyvsp[0].s));
			}
#line 6120 "y.tab.c"
    break;

  case 358: /* term: STRING  */
#line 2704 "gram.y"
                        {	(yyval.p) = new expr(STRING,0,0);
				(yyval.pe)->string = copy_if_need_be((yyvsp[0].s));
			}
#line 6128 "y.tab.c"
    break;

  case 359: /* term: CCON  */
#line 2708 "gram.y"
                        {	(yyval.p) = new expr(CCON,0,0);
				(yyval.pe)->string = copy_if_need_be((yyvsp[0].s));
			}
#line 6136 "y.tab.c"
    break;

  case 360: /* term: THIS  */
#line 2712 "gram.y"
                        {	(yyval.p) = new expr(THIS,0,0); }
#line 6142 "y.tab.c"
    break;

  case 361: /* dtorspec: COMPL tag  */
#line 2716 "gram.y"
                        {	
				(yyval.p) = dummy_dtor();
				(yyval.pn)->n_dtag = (yyvsp[0].pn); // checked later
			}
#line 6151 "y.tab.c"
    break;

  case 362: /* dtorspec: MEMQ COMPL tag  */
#line 2721 "gram.y"
                        {	
				(yyval.p) = dummy_dtor();
				(yyval.pn)->n_qualifier = (yyvsp[-2].pn); // checked later
				(yyval.pn)->n_dtag = (yyvsp[0].pn); // checked later
			}
#line 6161 "y.tab.c"
    break;

  case 363: /* dtorspec: TYPE MEM COMPL TYPE  */
#line 2727 "gram.y"
                        { (yyval.p) = dummy_dtor((yyvsp[-3].t),(yyvsp[0].t)); }
#line 6167 "y.tab.c"
    break;

  case 364: /* dtorspec: COMPL TYPE  */
#line 2729 "gram.y"
                        { (yyval.p) = dummy_dtor((yyvsp[0].t),(yyvsp[0].t)); }
#line 6173 "y.tab.c"
    break;

  case 365: /* dtorspec: TYPE MEM COMPL tag  */
#line 2731 "gram.y"
                        {	
				(yyval.p) = dummy_dtor( (yyvsp[-3].t), (yyvsp[-3].t) );
				(yyval.pn)->n_dtag = (yyvsp[0].pn);
			}
#line 6182 "y.tab.c"
    break;

  case 366: /* dtorspec: MEMQ COMPL TYPE  */
#line 2736 "gram.y"
                        {
				(yyval.p) = dummy_dtor( (yyvsp[0].t), (yyvsp[0].t) );
				(yyval.pn)->n_qualifier = (yyvsp[-2].pn);
			}
#line 6191 "y.tab.c"
    break;

  case 367: /* dtorspec: tn_list COMPL tag  */
#line 2741 "gram.y"
                        { // kluge to parse parameterized qualifiers after ./->
				(yyval.p) = dummy_dtor();
				(yyval.pn)->n_qualifier = (yyvsp[-2].pn);
				(yyval.pn)->n_dtag = (yyvsp[0].pn);
			}
#line 6201 "y.tab.c"
    break;

  case 368: /* dtorspec: tn_list COMPL TYPE  */
#line 2747 "gram.y"
                        { // kluge to parse parameterized qualifiers after ./->
				(yyval.p) = dummy_dtor( (yyvsp[0].t), (yyvsp[0].t) );
				(yyval.pn)->n_qualifier = (yyvsp[-2].pn);
			}
#line 6210 "y.tab.c"
    break;

  case 369: /* term_elist: TYPE LP elist RP  */
#line 2754 "gram.y"
                        { 	(yyval.p) = new texpr(VALUE,tok_to_type((yyvsp[-3].t)),(yyvsp[-1].pe)); }
#line 6216 "y.tab.c"
    break;

  case 370: /* term_elist: tname LP elist RP  */
#line 2759 "gram.y"
                        {	
				(yyval.p) = new texpr(VALUE,(yyvsp[-3].pn)->tp,(yyvsp[-1].pe)); 
				if ((yyvsp[-3].pn)->is_template_arg() && (yyvsp[-3].pn)->tp->base == ANY) {
					(yyval.pe)->tp2 = new basetype(TYPE,(yyvsp[-3].pn));
				}
			}
#line 6227 "y.tab.c"
    break;

  case 371: /* term_elist: NEW term_lp elist RP cast_type  */
#line 2765 "gram.y"
                                                     { goto new2; }
#line 6233 "y.tab.c"
    break;

  case 372: /* term_elist: NEW term_lp elist RP new_type  */
#line 2767 "gram.y"
                        {	new2:
				Ptype t = (yyvsp[0].pn)->tp;
				(yyval.p)=new texpr(NEW,t,0);
				(yyval.pe)->e2 = (yyvsp[-2].pe);
				--in_new;
			}
#line 6244 "y.tab.c"
    break;

  case 373: /* term_elist: MEM NEW term_lp elist RP cast_type  */
#line 2773 "gram.y"
                                                        { goto new4; }
#line 6250 "y.tab.c"
    break;

  case 374: /* term_elist: MEM NEW term_lp elist RP new_type  */
#line 2775 "gram.y"
                        {	new4:
				Ptype t = (yyvsp[0].pn)->tp;
				(yyval.p) = new texpr(GNEW,t,0);
				(yyval.pe)->e2 = (yyvsp[-2].pe);
				--in_new;
			}
#line 6261 "y.tab.c"
    break;

  case 375: /* term_elist: term LP elist RP  */
#line 2782 "gram.y"
                        {	
				Pexpr ee = (yyvsp[-1].pe);
				Pexpr e = (yyvsp[-3].pe);
				if (e->base==NEW || e->base==GNEW)
					e->e1 = ee;
				else
					(yyval.p) = new call(e,ee);
			}
#line 6274 "y.tab.c"
    break;

  case 376: /* ptname: PTNAME lt temp_inst_parms gt  */
#line 2794 "gram.y"
                 {
			(yyval.pn) = parametrized_typename((yyvsp[-3].pn),(expr_unlist((yyvsp[-1].el)))); 
	 	 }
#line 6282 "y.tab.c"
    break;

  case 377: /* tscope: TSCOPE  */
#line 2799 "gram.y"
                          { (yyval.pn) = (yyvsp[0].pn); }
#line 6288 "y.tab.c"
    break;

  case 378: /* tscope: MEM  */
#line 2800 "gram.y"
                       { (yyval.pn) = sta_name; }
#line 6294 "y.tab.c"
    break;

  case 379: /* tscope: ptname TSCOPE  */
#line 2801 "gram.y"
                                 { (yyval.pn) = (yyvsp[-1].pn); }
#line 6300 "y.tab.c"
    break;

  case 380: /* prim: ID  */
#line 2806 "gram.y"
                        {
				if ( in_arg_list && !in_binit_list ) {
				    Pktab tb = Ctbl;
				    for (; tb && tb->k_id==ARG; tb=tb->k_next) {
					if ( tb->look((yyvsp[0].pn)->string,0) ) {
						error("illegalR toA%n in defaultA",(yyvsp[0].pn));
						(yyvsp[0].pe) = dummy;
						break;
					}
				    }
				}
				(yyval.p) = (yyvsp[0].pn);
			}
#line 6318 "y.tab.c"
    break;

  case 381: /* prim: OPERATOR oper  */
#line 2820 "gram.y"
                        {	(yyval.p) = new name(oper_name((yyvsp[0].t)));
				(yyval.pn)->n_oper = (yyvsp[0].t);
			}
#line 6326 "y.tab.c"
    break;

  case 382: /* prim: OPERATOR c_type  */
#line 2824 "gram.y"
                        {	(yyval.p) = (yyvsp[0].p);
				sig_name((yyval.pn));
			}
#line 6334 "y.tab.c"
    break;

  case 383: /* cast_type: term_lp type cast_decl RP  */
#line 2833 "gram.y"
                        {
				(yyval.p) = Ncast((yyvsp[-2].p),(yyvsp[-1].pn));
			}
#line 6342 "y.tab.c"
    break;

  case 384: /* term_lp: LP  */
#line 2838 "gram.y"
                      { check_cast(); }
#line 6348 "y.tab.c"
    break;

  case 385: /* c_tp: TYPE  */
#line 2842 "gram.y"
                        {
				TOK t = (yyvsp[0].t);

				switch (t) {
				case FRIEND:
				case OVERLOAD:
				case REGISTER:
				case STATIC:
				case EXTERN:
				case AUTO:
				case VIRTUAL:
					error("%k in operatorT",t);
					t = INT;
					
				}

				(yyval.p) = new basetype(t,0);

			}
#line 6372 "y.tab.c"
    break;

  case 386: /* c_tp: tname  */
#line 2861 "gram.y"
                                { (yyval.p) = new basetype(TYPE,(yyvsp[0].pn)); }
#line 6378 "y.tab.c"
    break;

  case 387: /* c_tp: c_tp TYPE  */
#line 2863 "gram.y"
                        { 
				if ( DECL_TYPE != -1 ) {
					switch ((yyvsp[-1].pb)->base) { 
					case COBJ: case EOBJ:
						{
						Pbase bt;
						bt = new basetype(0,0);
						*bt = *(yyvsp[-1].pb);
						DEL((yyvsp[-1].pb));
						(yyvsp[-1].pb) = bt;
						}
					}
					(yyval.p) = (yyvsp[-1].pb)->type_adj((yyvsp[0].t)); 
				}
				DECL_TYPE = 0;
			}
#line 6399 "y.tab.c"
    break;

  case 388: /* c_tp: c_tp tname  */
#line 2880 "gram.y"
                        { 
				if ( DECL_TYPE != -1 ) 
			 		(yyval.p) = (yyvsp[-1].pb)->name_adj((yyvsp[0].pn));
				DECL_TYPE = 0;
			}
#line 6409 "y.tab.c"
    break;

  case 389: /* c_type: c_tp c_decl  */
#line 2887 "gram.y"
                                { (yyval.p) = Ncast((yyvsp[-1].p),(yyvsp[0].pn)); }
#line 6415 "y.tab.c"
    break;

  case 390: /* new_type: type new_decl  */
#line 2890 "gram.y"
                                        { (yyval.p) = Ncast((yyvsp[-1].p),(yyvsp[0].pn)); }
#line 6421 "y.tab.c"
    break;

  case 391: /* arg_type: type arg_decl  */
#line 2893 "gram.y"
                        {	
                         //      ENTER_NAME($<pn>2);
				(yyval.p) = Ndata((yyvsp[-1].p),(yyvsp[0].pn)); 
			}
#line 6430 "y.tab.c"
    break;

  case 392: /* $@23: %empty  */
#line 2898 "gram.y"
                        {
                        //      ENTER_NAME($<pn>2);
                        }
#line 6438 "y.tab.c"
    break;

  case 393: /* arg_type: type arg_decl ASSIGN $@23 initializer  */
#line 2902 "gram.y"
                        {       
				(yyval.p) = Ndata((yyvsp[-4].p),(yyvsp[-3].pn));
                                (yyval.pn)->n_initializer = (yyvsp[0].pe);
                        }
#line 6447 "y.tab.c"
    break;

  case 394: /* arg_lp: LP  */
#line 2909 "gram.y"
                        {	PUSH_ARG_SCOPE();//SYM
				//SAVE_STATE();
				in_arg_list=1; 
				check_decl(); 
				(yyval.pl) = 0;
				//SYM -- tn stuff removed
			}
#line 6459 "y.tab.c"
    break;

  case 395: /* arg_list: arg_lp arg_type_list ellipsis_opt RP fct_attributes  */
#line 2919 "gram.y"
                    {
			(yyval.p) = new fct(0,name_unlist((yyvsp[-3].nl)),(yyvsp[-2].t)); 
			if ( NEXTTOK() != COLON ) in_arg_list=0;
			//in_arg_list=0;
			Pfct((yyval.pt))->f_const = ((yyvsp[0].i) & 1);
			//SYM -- removed kluge
                        POP_SCOPE();//SYM
			//RESTORE_STATE();
		    }
#line 6473 "y.tab.c"
    break;

  case 396: /* arg_type_list: arg_type_list CM at  */
#line 2931 "gram.y"
                        {
				if ((yyvsp[0].p))
					if ((yyvsp[-2].p))
						(yyvsp[-2].nl)->add((yyvsp[0].pn));
					else {
						error("AD syntax");
						(yyval.nl) = new nlist((yyvsp[0].pn)); 
					}
				else
					error("AD syntax");
			}
#line 6489 "y.tab.c"
    break;

  case 397: /* arg_type_list: at  */
#line 2943 "gram.y"
                        {
				if ((yyvsp[0].p)) (yyval.nl) = new nlist((yyvsp[0].pn)); 
			}
#line 6497 "y.tab.c"
    break;

  case 399: /* at: %empty  */
#line 2949 "gram.y"
                                {	(yyval.p) = 0; }
#line 6503 "y.tab.c"
    break;

  case 400: /* ellipsis_opt: %empty  */
#line 2953 "gram.y"
                    {	(yyval.t) = 1; }
#line 6509 "y.tab.c"
    break;

  case 401: /* ellipsis_opt: ELLIPSIS  */
#line 2955 "gram.y"
                    {	(yyval.t) = ELLIPSIS; }
#line 6515 "y.tab.c"
    break;

  case 402: /* ellipsis_opt: CM ELLIPSIS  */
#line 2957 "gram.y"
                    {	(yyval.t) = ELLIPSIS; }
#line 6521 "y.tab.c"
    break;

  case 403: /* ptr: MUL  */
#line 2961 "gram.y"
                        {
			(yyval.p) = new ptr(PTR,0); 
			EXPECT_ID();
			}
#line 6530 "y.tab.c"
    break;

  case 404: /* ptr: AND  */
#line 2966 "gram.y"
                        {
			(yyval.p) = new ptr(RPTR,0); 
			EXPECT_ID();
			}
#line 6539 "y.tab.c"
    break;

  case 405: /* ptr: MUL TYPE  */
#line 2971 "gram.y"
                        {	(yyval.p) = doptr(PTR,(yyvsp[0].t)); }
#line 6545 "y.tab.c"
    break;

  case 406: /* ptr: ptr TYPE  */
#line 2973 "gram.y"
                        {	
				switch ( (yyvsp[0].t) ) {
				case CONST:
                                     (yyvsp[-1].pp)->b_const = 1; break;
				case VOLATILE:
				     error('w',"\"volatile\" not implemented (ignored)");
				     break;
				default:
				    error( "syntax error: *%k", (yyvsp[0].t) );
				}
				(yyval.p) = (yyvsp[-1].pp); 
			}
#line 6562 "y.tab.c"
    break;

  case 407: /* ptr: AND TYPE  */
#line 2986 "gram.y"
                        {	(yyval.p) = doptr(RPTR,(yyvsp[0].t)); }
#line 6568 "y.tab.c"
    break;

  case 408: /* ptr: ptname MEMPTR  */
#line 2988 "gram.y"
                        {	
				memptr_pn = (yyvsp[-1].pn);
				memptr_tok = 0;
				goto memptr1;
			}
#line 6578 "y.tab.c"
    break;

  case 409: /* ptr: MEMPTR  */
#line 2994 "gram.y"
                        {
			memptr_pn = (yyvsp[0].pn);
			memptr_tok = 0;
			memptr1:
			if (memptr_tok)
				(yyval.p) = doptr(PTR,memptr_tok);
			else
				(yyval.p) = new ptr(PTR,0);
			Pname n = memptr_pn;
			if (n->is_template_arg()==0) {
				if(n->tp->skiptypedefs()->base != COBJ) {
				    (yyval.pp)->memof = 0;
				    error("P toM of nonCT");
				}
				else (yyval.pp)->memof = n->tp->skiptypedefs()->classtype();
			}
			else {
				(yyval.pp)->memof = 0;
				(yyval.pp)->ptname = n;
			}
			EXPECT_ID();
			}
#line 6605 "y.tab.c"
    break;

  case 410: /* ptr: ptname MEMPTR TYPE  */
#line 3017 "gram.y"
                        {	
				memptr_pn = (yyvsp[-2].pn);
				memptr_tok = (yyvsp[0].t);
				goto memptr1;
			}
#line 6615 "y.tab.c"
    break;

  case 411: /* ptr: MEMPTR TYPE  */
#line 3023 "gram.y"
                        {	
				memptr_pn = (yyvsp[-1].pn);
				memptr_tok = (yyvsp[0].t);
				goto memptr1;
			}
#line 6625 "y.tab.c"
    break;

  case 412: /* vec: LB e RB  */
#line 3030 "gram.y"
                                        { (yyval.p) = new vec(0,(yyvsp[-1].pe)!=dummy?(yyvsp[-1].pe):0 ); }
#line 6631 "y.tab.c"
    break;

  case 413: /* vec: NOT  */
#line 3031 "gram.y"
                                        { (yyval.p) = new vec(0,0); }
#line 6637 "y.tab.c"
    break;


#line 6641 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= EOFTOK)
        {
          /* Return failure if at end of input.  */
          if (yychar == EOFTOK)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 3034 "gram.y"


static Pname
enumcheck( Pname n )
{
	Ptype tx = n->tp;
	if ( tx->base == TYPE ) {
		Pname bn = Pbase(tx)->b_name;
		tx = bn->tp;
		if ( tx->base != EOBJ
		||   strcmp(bn->string,n->string)
		)
			error("%n ofT%t redeclared as enum.",n,tx);
		n = bn;
	} else if ( tx->base != EOBJ )
		error("%n ofT%t redeclared as enum",n,tx);

// error('d',"enumtag: ccl %t tag: %n", ccl, n);
	return n;
}

static void
check_tag()
/*
        Allow the case of inline/virtual/overload as 
        modifiers of return type of form struct/class/union x foo() 
        SM, COLON, LC ==> real class declaration, not return type
*/
{
	switch ( NEXTTOK() ) {
	case SM: case COLON: case LC:
    		declTag = 1;
    		break;
	default:
    		declTag = 0;
    		break;
        }
}

static void
hoist_al()
/*SYM hoist names in arg table to next outer scope and pop scope
 * called upon discovering that an arg list isn't really being parsed
 *    -- i.e., 'arg_lp decl RP ...' -- arg_lp pushed an arg table
 */
{
	if ( Ctbl->k_id != ARG ) {
		// saw something like '( X::y )' while probably reduced
		//    as 'arg_lp decl RP' and pushed scope of X
		// no names should have been entered; discard table
		Pktab otbl = Ctbl;
		Ctbl = GET_XSCOPE();
		if ( Ctbl->k_id != ARG ) error('i',"hoist_al: noA table");
		POP_SCOPE();
		SET_XSCOPE(Ctbl);
		Ctbl = otbl;
		return;
	}
	if ( !in_typedef && !in_friend ) Ctbl->hoist();
	POP_SCOPE();
}
static void
arg_redec( Pname fn )
/* parsing restored member inline at end of class
 * redeclare args before entering function
 */
{
	if ( fn==0 || fn->tp->base != FCT )
		error('i',"bad inline rewrite! --%n %t",fn,fn?fn->tp:0);
	if ( Ctbl->k_id != ARG )
		error('i',"arg_redec(%n ) -- noA table",fn);
	//SYM -- reenter in arg table
	//SYM -- probably more efficient to keep arg table around...
	Pname al = Pfct(fn->tp)->argtype;
	Pname n = 0;
	for ( ;  al;  al = al->n_list ) {
		DB( if(Ydebug>=1)error('d',"arg_redec:  %n  %d",al,al->lex_level); );
		n = new name(al->string);
		insert_name(n,Ctbl);
		DB( if(Ydebug>=1)error('d',"   %n",n); );
	}
}

static Pname
dummy_dtor( TOK q, TOK d )
{
	if ( q != d ) {
		error("syntax error: inconsistent destructor notation");
		q = d;
	}
	Pname dt = new name("type destructor");
	dt->base = DTOR;
	dt->tp = new fct(void_type,0,1);
	dt->n_dcl_printed = 1; // suppress any code generation
	switch ( d ) {
	default:
		error("syntax error: illegal destructor notation");
		dt->tp2 = any_type;
		break;
	case CHAR:
		dt->tp2 = dt->tpdef = char_type;
		break;
	case SHORT:
		dt->tp2 = dt->tpdef = short_type;
		break;
	case SIGNED:
	case INT:
		dt->tp2 = dt->tpdef = int_type;
		break;
	case UNSIGNED:
		dt->tp2 = dt->tpdef = uint_type;
		break;
	case LONG:
		dt->tp2 = dt->tpdef = long_type;
		break;
	case FLOAT:
		dt->tp2 = dt->tpdef = float_type;
		break;
	case DOUBLE:
		dt->tp2 = dt->tpdef = double_type;
		break;
	case VOID:
		dt->tp2 = dt->tpdef = void_type;
		break;
	}
	return dt;
}
static Pname
dummy_dtor()
{
	Pname dt = new name("type destructor");
	dt->base = DTOR;
	dt->tp = new fct(void_type,0,1);
	dt->n_dcl_printed = 1; // suppress any code generation
	dt->tp2 = 0;
	dt->tpdef = 0;
	return dt;
}

static bit
check_if_base( Pclass c1, Pclass c2 )
{
	if ( same_class(c1,c2) ) return 1;
	for (Pbcl b = c1->baselist; b; b=b->next) {
		if ( same_class(b->bclass,c2) ) return 1;
		if (check_if_base(b->bclass,c2)) return 1;
	}
	return 0;
}
