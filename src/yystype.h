/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 271 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
