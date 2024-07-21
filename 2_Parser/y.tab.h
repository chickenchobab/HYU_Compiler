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
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    WHILE = 259,                   /* WHILE  */
    RETURN = 260,                  /* RETURN  */
    INT = 261,                     /* INT  */
    VOID = 262,                    /* VOID  */
    RPAREN = 263,                  /* RPAREN  */
    ELSE = 264,                    /* ELSE  */
    ID = 265,                      /* ID  */
    NUM = 266,                     /* NUM  */
    EQ = 267,                      /* EQ  */
    NE = 268,                      /* NE  */
    LT = 269,                      /* LT  */
    LE = 270,                      /* LE  */
    GT = 271,                      /* GT  */
    GE = 272,                      /* GE  */
    LPAREN = 273,                  /* LPAREN  */
    LBRACE = 274,                  /* LBRACE  */
    RBRACE = 275,                  /* RBRACE  */
    LCURLY = 276,                  /* LCURLY  */
    RCURLY = 277,                  /* RCURLY  */
    COMMA = 278,                   /* COMMA  */
    SEMI = 279,                    /* SEMI  */
    ERROR = 280,                   /* ERROR  */
    PLUS = 281,                    /* PLUS  */
    MINUS = 282,                   /* MINUS  */
    TIMES = 283,                   /* TIMES  */
    OVER = 284,                    /* OVER  */
    ASSIGN = 285                   /* ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define WHILE 259
#define RETURN 260
#define INT 261
#define VOID 262
#define RPAREN 263
#define ELSE 264
#define ID 265
#define NUM 266
#define EQ 267
#define NE 268
#define LT 269
#define LE 270
#define GT 271
#define GE 272
#define LPAREN 273
#define LBRACE 274
#define RBRACE 275
#define LCURLY 276
#define RCURLY 277
#define COMMA 278
#define SEMI 279
#define ERROR 280
#define PLUS 281
#define MINUS 282
#define TIMES 283
#define OVER 284
#define ASSIGN 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
