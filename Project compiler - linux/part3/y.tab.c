/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "proj.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "scope.h"
#define YYSTYPE struct node*
extern int yylex();
extern int yylineno;
extern char *yytext;

node* mknode(char* token,node* left,node* mid1,node* mid2, node* right);
void Printtree(node* tree,int tab);
int isTerminal(node* tree);
int AllChildTerminal(node* tree);
void yyerror(const char *msg);
char* freshVar();
char* freshLabel();
char* itoa(int value, char* result, int base);
int countSubString(char* source, char* find);

scope* global;
int globalVar = -1;
int globalLabel = -1;
int countBeginFunc = 0;


#line 48 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define BOOL 257
#define VOID 258
#define CHAR 259
#define INT 260
#define STRING 261
#define INTP 262
#define CHARP 263
#define REALP 264
#define REAL 265
#define VAR 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define DO 270
#define FOR 271
#define RRETURN 272
#define NNULL 273
#define AND 274
#define DIVIDE 275
#define ASSIGN 276
#define ISEQUAL 277
#define GREATER 278
#define GREATEREQ 279
#define LESS 280
#define LESSEQ 281
#define MINUS 282
#define NOT 283
#define NOTEQUAL 284
#define OR 285
#define PLUS 286
#define MULT 287
#define BAND 288
#define BOOL_TRUE 289
#define BOOL_FALSE 290
#define FUNC 291
#define CHARR 292
#define NUM 293
#define ID 294
#define HEX 295
#define DEC 296
#define REAL_NUMBER 297
#define STRING_ID 298
#define SEMI 299
#define COMMA 300
#define ABS 301
#define OBRACE 302
#define CBRACE 303
#define OBRACKET 304
#define CBRACKET 305
#define OSQRERACKET 306
#define CSQRERACKET 307
#define OCMNT 308
#define SINMGLE_COMMENT 309
#define CCMNT 310
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    2,    2,    3,    3,    9,   10,   10,   10,
    6,    6,   14,   14,   15,   13,   13,   13,   17,   17,
   19,   19,   16,   16,    4,    4,    4,    4,    4,    4,
    4,   11,   11,   11,   23,   23,   23,   23,    7,   27,
   20,   20,   20,   20,   22,   22,   28,   28,   24,   24,
   25,   25,   25,   25,   26,   26,   26,   26,   26,   32,
   32,   32,   32,   32,   12,   12,   12,   31,   31,   21,
   21,   21,   21,   21,   21,   21,   21,   21,   21,   21,
   21,   21,   21,   21,   21,   21,   21,   21,   21,   21,
   21,   21,   21,   21,   21,   35,   35,   35,   35,    5,
   29,   33,   34,   36,    8,   18,   30,
};
static const YYINT yylen[] = {                            2,
    1,    1,    2,    1,    7,    7,    3,    2,    2,    0,
    1,    0,    3,    1,    2,    4,    3,    3,    3,    1,
    7,    5,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    2,    0,    1,    2,    1,    1,    3,    1,
    4,    5,    8,    5,    2,    0,    1,    4,    4,    3,
    5,    7,    5,    7,    5,    8,    5,    8,    7,    3,
    3,    3,    3,    3,    3,    2,    0,    3,    1,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    2,    2,    2,    2,    1,    1,    1,    1,    3,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    1,    2,    0,   25,  105,   26,   27,   29,
   30,   31,   28,    0,    0,    3,  100,    0,    0,    0,
    0,  106,   23,    0,    0,   14,    0,   24,    0,    0,
    0,    0,   15,    0,    0,    5,   13,    0,    6,    0,
    0,    0,    0,    0,    0,   19,    0,    8,   39,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   35,    0,
    0,   37,   38,    0,    9,    0,    0,    0,    0,   18,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   33,
    0,    7,   32,   36,  101,    0,    0,   17,   16,   92,
    0,    0,    0,    0,   87,   88,  104,   96,   97,   98,
   99,  107,    0,    0,    0,   93,   89,   95,   86,   94,
    0,    0,    0,    0,    0,   50,    0,    0,    0,   66,
    0,    0,    0,    0,    0,   82,   83,   85,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   49,
   48,   65,    0,   41,    0,   91,   90,    0,   73,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   72,    0,
   40,   53,   55,   57,    0,    0,   44,   42,    0,    0,
    0,    0,    0,    0,  103,  102,    0,    0,    0,    0,
    0,    0,   45,   52,   54,   59,    0,    0,    0,    0,
    0,    0,    0,   21,    0,   60,   62,   56,   58,   61,
   63,   43,
};
static const YYINT yydgoto[] = {                          2,
    3,    4,   41,   23,   56,   24,   57,   15,   42,   43,
   58,   82,   44,   25,   26,   27,   33,   28,   67,   59,
  105,  181,  171,  106,   62,   63,  172,  107,   86,  108,
  118,  188,  189,  190,  109,  110,
};
static const YYINT yysindex[] = {                      -281,
  -57,    0,    0,    0, -281,    0,    0,    0,    0,    0,
    0,    0,    0, -239, -239,    0,    0, -223, -210,  -30,
  -30,    0,    0, -259, -243,    0, -239,    0, -204, -184,
  -30, -175,    0, -184, -244,    0,    0, -239,    0,    1,
 -244, -163,  -90, -244, -239,    0, -215,    0,    0, -146,
 -144, -184, -138, -239, -239, -151,  -90, -103,    0,  -90,
 -128,    0,    0, -104,    0, -131, -110, -270, -108,    0,
  302,  302,  -74, -215, -112, -104, -104,  249,  302,    0,
  275,    0,    0,    0,    0,  328,  302,    0,    0,    0,
  302,  302,  302, -239,    0,    0,    0,    0,    0,    0,
    0,    0,  302,  302,  356,    0,    0,    0,    0,    0,
  370, -105,  302,  302,  302,    0,  528, -207,   69,    0,
  432, -239,  448,   83, -209,    0,    0,    0,  414,  385,
  302,  302,  302,  302,  302,  302,  302,  302,  302,  302,
  302,  302,  -90,  -90,  302,  464,  480,  496,  302,    0,
    0,    0,  -97,    0, -104,    0,    0,  239,    0, -248,
 -248, -248, -248, -248, -209, -248,  239, -209,    0,  -72,
    0,    0,    0,    0,  399, -191,    0,    0,  528,  302,
  -89,  -88,  -90,  -77,    0,    0, -190,  -69,  -58,  -41,
  100, -239,    0,    0,    0,    0,  302,  -58,  -41,  -90,
 -239, -239,  -62,    0,  528,    0,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,  242,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -51,
  -51,    0,    0,    0,  -46,    0,    0,    0,    0,    0,
    0, -186,    0,    0, -218,    0,    0,    0,    0,    0,
 -218,    0, -258, -218,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -61, -258,  -60,    0, -258,
    0,    0,    0,    0,    0,    0,    0, -257,    0,    0,
    0,    0,    0,    0,   -9,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -203,    0,    0,    0,
    0,    0,    0,    0,  -29,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  512,    0, -135,    0,    0, -242,    0,  114,
  146,  155,  187,  196,    3,  228, -115,   35,    0, -120,
    0,    0,    0,    0,    0,    0,    0,    0, -179,    0,
  -52,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -43,    0,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  263,  143,    8,  -14,  248,  -27,    0,    0,   98,
   97,    0,    0,    0,  243,    0,   24,   79,   81,  -45,
   -4,    0,    7,  -37,    0,    0, -139,  -39,  -65,   93,
    0,    0, -161,  -75,    0,    0,
};
#define YYTABLESIZE 815
static const YYINT yytable[] = {                         18,
   19,   70,   36,   64,  174,   61,   39,   64,   14,    1,
  114,  115,   32,   34,   76,   77,   22,   64,   47,   61,
   64,   40,   61,   32,   73,  198,  132,  201,  113,   38,
   66,   74,   68,  138,   64,   79,  206,  141,  142,   75,
   75,   20,   74,  195,   34,   30,    1,   47,   10,   60,
   10,   10,   10,   10,   17,   31,   74,   74,   74,   75,
  209,   46,   74,   60,   74,  132,   60,  111,   10,   10,
   69,   54,   55,  117,  119,   10,  121,  142,   17,  128,
   20,  123,  124,   10,   10,   85,  125,  126,  127,  182,
  185,  185,  149,   21,  186,  186,   69,  150,  129,  130,
   34,   69,   17,   64,   64,   61,   61,  153,  146,  147,
  148,  199,   20,   45,  202,  170,  173,   35,   20,   45,
   68,  197,   45,  207,   38,   68,  158,  159,  160,  161,
  162,  163,  164,  165,  166,  167,  168,  169,   48,   49,
  175,   65,    5,   64,  179,   61,   51,    5,   51,   51,
   51,   51,   78,   80,   79,  194,   83,   71,   75,   72,
   64,  187,   61,   46,   46,   74,   51,   51,   81,   75,
   84,   85,  208,   51,   87,  191,   50,   66,   51,   52,
   53,   51,   51,   75,   75,   75,  210,  211,   88,   75,
   89,   75,  205,   79,  112,  183,   54,   55,  145,    6,
    7,    8,    9,   17,   10,   11,   12,   13,  180,  102,
  192,   35,   47,   47,   47,   47,   47,   47,   47,   47,
   47,  196,   47,   47,   47,   47,    6,  186,    8,    9,
   22,   10,   11,   12,   13,  200,  212,   47,   47,   47,
  185,    4,   67,   47,   84,   47,   22,   84,   84,   84,
   84,   84,   84,   12,   84,   84,   84,    6,   11,    8,
    9,   64,   10,   11,   12,   13,   47,   16,   29,   84,
   84,   84,  204,   37,  193,   84,   71,   84,    0,   71,
   71,   71,   71,   71,   71,    0,   71,   71,   71,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   71,   71,   71,    0,    0,    0,   71,   70,   71,
    0,   70,   70,   70,   70,   70,   70,    0,   70,   70,
   70,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   70,   70,   70,    0,    0,    0,   70,
    0,   70,  131,  132,    0,  133,  134,  135,  136,  137,
  138,    0,  139,  140,  141,  142,  131,  132,    0,  133,
  134,  135,  136,  137,  138,    0,  139,  140,  141,  142,
    0,    0,    0,  131,  132,  151,  133,  134,  135,  136,
  137,  138,    0,  139,  140,  141,  142,   76,    0,  155,
   76,   76,   76,   76,   76,    0,    0,   76,   76,    0,
    0,    0,    0,    0,    0,    0,  203,    0,    0,    0,
    0,    0,   76,   76,   76,    0,    0,    0,   76,   78,
   76,    0,   78,   78,   78,   78,   78,    0,   79,   78,
   78,   79,   79,   79,   79,   79,    0,    0,   79,   79,
    0,    0,    0,    0,   78,   78,   78,    0,    0,    0,
   78,    0,   78,   79,   79,   79,    0,    0,    0,   79,
   80,   79,    0,   80,   80,   80,   80,   80,    0,   81,
   80,   80,   81,   81,   81,   81,   81,    0,    0,   81,
   81,    0,    0,    0,    0,   80,   80,   80,    0,    0,
    0,   80,    0,   80,   81,   81,   81,    0,    0,    0,
   81,   77,   81,    0,   77,   77,   77,   77,   77,    0,
    0,   77,   77,  132,    0,  133,  134,  135,  136,  137,
  138,   90,  139,    0,  141,  142,   77,   77,   77,    0,
   91,   92,   77,    0,   77,   93,   94,   95,   96,    0,
   97,   98,   17,   99,  100,  101,  102,   90,    0,  103,
    0,    0,  104,  116,    0,    0,   91,   92,    0,    0,
    0,   93,   94,   95,   96,    0,   97,   98,   17,   99,
  100,  101,  102,  120,   90,  103,    0,    0,  104,    0,
    0,    0,    0,   91,   92,    0,    0,    0,   93,   94,
   95,   96,    0,   97,   98,   17,   99,  100,  101,  102,
   90,    0,  103,    0,    0,  104,    0,    0,    0,   91,
   92,    0,    0,    0,   93,  122,   95,   96,    0,   97,
   98,   17,   99,  100,  101,  102,    0,    0,  103,  131,
  132,  104,  133,  134,  135,  136,  137,  138,    0,  139,
  140,  141,  142,  131,  132,    0,  133,  134,  135,  136,
  137,  138,    0,  139,  140,  141,  142,    0,  131,  132,
  143,  133,  134,  135,  136,  137,  138,    0,  139,  140,
  141,  142,  131,  132,  144,  133,  134,  135,  136,  137,
  138,    0,  139,  140,  141,  142,    0,  131,  132,  157,
  133,  134,  135,  136,  137,  138,    0,  139,  140,  141,
  142,    0,    0,  184,    0,  131,  132,    0,  133,  134,
  135,  136,  137,  138,  156,  139,  140,  141,  142,    0,
    0,  131,  132,    0,  133,  134,  135,  136,  137,  138,
  152,  139,  140,  141,  142,    0,    0,  131,  132,    0,
  133,  134,  135,  136,  137,  138,  154,  139,  140,  141,
  142,    0,    0,  131,  132,    0,  133,  134,  135,  136,
  137,  138,  176,  139,  140,  141,  142,    0,    0,  131,
  132,    0,  133,  134,  135,  136,  137,  138,  177,  139,
  140,  141,  142,    0,    0,   85,   85,    0,   85,   85,
   85,   85,   85,   85,  178,   85,   85,   85,   85,    0,
    0,  131,  132,    0,  133,  134,  135,  136,  137,  138,
   85,  139,  140,  141,  142,
};
static const YYINT yycheck[] = {                         14,
   15,   47,   30,   43,  144,   43,   34,   47,    1,  291,
   76,   77,   27,  272,   54,   55,  261,   57,  276,   57,
   60,  266,   60,   38,   52,  187,  275,  189,   74,  300,
   45,  274,   47,  282,   74,  306,  198,  286,  287,   54,
   55,  299,  285,  183,  303,  305,  291,   40,  267,   43,
  269,  270,  271,  272,  294,  299,  299,  300,  301,   74,
  200,   38,  305,   57,  307,  275,   60,   72,  287,  288,
   47,  287,  288,   78,   79,  294,   81,  287,  294,   94,
  304,   86,   87,  302,  303,  276,   91,   92,   93,  155,
  282,  282,  300,  304,  286,  286,  300,  305,  103,  104,
  305,  305,  294,  143,  144,  143,  144,  122,  113,  114,
  115,  187,  299,   35,  190,  143,  144,  302,  305,   41,
  300,  187,   44,  199,  300,  305,  131,  132,  133,  134,
  135,  136,  137,  138,  139,  140,  141,  142,   41,  303,
  145,   44,    0,  183,  149,  183,  267,    5,  269,  270,
  271,  272,  304,   57,  306,  183,   60,  304,  274,  304,
  200,  176,  200,  299,  300,  304,  287,  288,  272,  285,
  299,  276,  200,  294,  306,  180,  267,  192,  269,  270,
  271,  302,  303,  299,  300,  301,  201,  202,  299,  305,
  299,  307,  197,  306,  269,  268,  287,  288,  304,  257,
  258,  259,  260,  294,  262,  263,  264,  265,  306,  298,
  300,  302,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  299,  284,  285,  286,  287,  257,  286,  259,  260,
  261,  262,  263,  264,  265,  305,  299,  299,  300,  301,
  282,    0,  303,  305,  274,  307,  299,  277,  278,  279,
  280,  281,  282,  305,  284,  285,  286,  257,  305,  259,
  260,  305,  262,  263,  264,  265,  276,    5,   21,  299,
  300,  301,  192,   31,  182,  305,  274,  307,   -1,  277,
  278,  279,  280,  281,  282,   -1,  284,  285,  286,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  299,  300,  301,   -1,   -1,   -1,  305,  274,  307,
   -1,  277,  278,  279,  280,  281,  282,   -1,  284,  285,
  286,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  299,  300,  301,   -1,   -1,   -1,  305,
   -1,  307,  274,  275,   -1,  277,  278,  279,  280,  281,
  282,   -1,  284,  285,  286,  287,  274,  275,   -1,  277,
  278,  279,  280,  281,  282,   -1,  284,  285,  286,  287,
   -1,   -1,   -1,  274,  275,  307,  277,  278,  279,  280,
  281,  282,   -1,  284,  285,  286,  287,  274,   -1,  307,
  277,  278,  279,  280,  281,   -1,   -1,  284,  285,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  307,   -1,   -1,   -1,
   -1,   -1,  299,  300,  301,   -1,   -1,   -1,  305,  274,
  307,   -1,  277,  278,  279,  280,  281,   -1,  274,  284,
  285,  277,  278,  279,  280,  281,   -1,   -1,  284,  285,
   -1,   -1,   -1,   -1,  299,  300,  301,   -1,   -1,   -1,
  305,   -1,  307,  299,  300,  301,   -1,   -1,   -1,  305,
  274,  307,   -1,  277,  278,  279,  280,  281,   -1,  274,
  284,  285,  277,  278,  279,  280,  281,   -1,   -1,  284,
  285,   -1,   -1,   -1,   -1,  299,  300,  301,   -1,   -1,
   -1,  305,   -1,  307,  299,  300,  301,   -1,   -1,   -1,
  305,  274,  307,   -1,  277,  278,  279,  280,  281,   -1,
   -1,  284,  285,  275,   -1,  277,  278,  279,  280,  281,
  282,  273,  284,   -1,  286,  287,  299,  300,  301,   -1,
  282,  283,  305,   -1,  307,  287,  288,  289,  290,   -1,
  292,  293,  294,  295,  296,  297,  298,  273,   -1,  301,
   -1,   -1,  304,  305,   -1,   -1,  282,  283,   -1,   -1,
   -1,  287,  288,  289,  290,   -1,  292,  293,  294,  295,
  296,  297,  298,  299,  273,  301,   -1,   -1,  304,   -1,
   -1,   -1,   -1,  282,  283,   -1,   -1,   -1,  287,  288,
  289,  290,   -1,  292,  293,  294,  295,  296,  297,  298,
  273,   -1,  301,   -1,   -1,  304,   -1,   -1,   -1,  282,
  283,   -1,   -1,   -1,  287,  288,  289,  290,   -1,  292,
  293,  294,  295,  296,  297,  298,   -1,   -1,  301,  274,
  275,  304,  277,  278,  279,  280,  281,  282,   -1,  284,
  285,  286,  287,  274,  275,   -1,  277,  278,  279,  280,
  281,  282,   -1,  284,  285,  286,  287,   -1,  274,  275,
  305,  277,  278,  279,  280,  281,  282,   -1,  284,  285,
  286,  287,  274,  275,  305,  277,  278,  279,  280,  281,
  282,   -1,  284,  285,  286,  287,   -1,  274,  275,  305,
  277,  278,  279,  280,  281,  282,   -1,  284,  285,  286,
  287,   -1,   -1,  305,   -1,  274,  275,   -1,  277,  278,
  279,  280,  281,  282,  301,  284,  285,  286,  287,   -1,
   -1,  274,  275,   -1,  277,  278,  279,  280,  281,  282,
  299,  284,  285,  286,  287,   -1,   -1,  274,  275,   -1,
  277,  278,  279,  280,  281,  282,  299,  284,  285,  286,
  287,   -1,   -1,  274,  275,   -1,  277,  278,  279,  280,
  281,  282,  299,  284,  285,  286,  287,   -1,   -1,  274,
  275,   -1,  277,  278,  279,  280,  281,  282,  299,  284,
  285,  286,  287,   -1,   -1,  274,  275,   -1,  277,  278,
  279,  280,  281,  282,  299,  284,  285,  286,  287,   -1,
   -1,  274,  275,   -1,  277,  278,  279,  280,  281,  282,
  299,  284,  285,  286,  287,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 310
#define YYUNDFTOKEN 349
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"BOOL","VOID","CHAR","INT",
"STRING","INTP","CHARP","REALP","REAL","VAR","IF","ELSE","WHILE","DO","FOR",
"RRETURN","NNULL","AND","DIVIDE","ASSIGN","ISEQUAL","GREATER","GREATEREQ",
"LESS","LESSEQ","MINUS","NOT","NOTEQUAL","OR","PLUS","MULT","BAND","BOOL_TRUE",
"BOOL_FALSE","FUNC","CHARR","NUM","ID","HEX","DEC","REAL_NUMBER","STRING_ID",
"SEMI","COMMA","ABS","OBRACE","CBRACE","OBRACKET","CBRACKET","OSQRERACKET",
"CSQRERACKET","OCMNT","SINMGLE_COMMENT","CCMNT",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : START",
"START : PROGRAM",
"PROGRAM : FUNCTIONS",
"FUNCTIONS : FUNCTION FUNCTIONS",
"FUNCTIONS : FUNCTION",
"FUNCTION : FUNC TYPE id OBRACKET F_PARAMS CBRACKET CODE_BLOCK",
"FUNCTION : FUNC void id OBRACKET F_PARAMS CBRACKET CODE_BLOCK",
"BODY : DECLERATIONS STATMENTS RETURN_STATMENT",
"DECLERATIONS : FUNCTION DECLERATIONS",
"DECLERATIONS : VAR_DECLERACTION DECLERATIONS",
"DECLERATIONS :",
"F_PARAMS : F_PARAMSS",
"F_PARAMS :",
"F_PARAMSS : F_PARAMSS SEMI PARAM",
"F_PARAMSS : PARAM",
"PARAM : PARAM_TYPE IDS",
"VAR_DECLERACTION : VAR TYPE IDS SEMI",
"VAR_DECLERACTION : string SID SEMI",
"VAR_DECLERACTION : VAR TYPE ASSIGNMENT",
"IDS : id COMMA IDS",
"IDS : id",
"SID : id OSQRERACKET EXPR CSQRERACKET STRING_ASSIGNMENT COMMA SID",
"SID : id OSQRERACKET EXPR CSQRERACKET STRING_ASSIGNMENT",
"PARAM_TYPE : TYPE",
"PARAM_TYPE : string",
"TYPE : BOOL",
"TYPE : CHAR",
"TYPE : INT",
"TYPE : REAL",
"TYPE : INTP",
"TYPE : CHARP",
"TYPE : REALP",
"STATMENTS : STATMENT STATMENTS",
"STATMENTS : CODE_BLOCK STATMENTS",
"STATMENTS :",
"STATMENT : ASSIGNMENT",
"STATMENT : FUNC_CALL SEMI",
"STATMENT : IFS",
"STATMENT : LOOPS",
"CODE_BLOCK : OBRACE BODY CBRACE",
"SINGLE_STATMENT : STATMENT",
"ASSIGNMENT : ASSIGNMENT_VAR assign EXPR SEMI",
"ASSIGNMENT : BAND ASSIGNMENT_VAR assign EXPR SEMI",
"ASSIGNMENT : ASSIGNMENT_VAR assign BAND id OSQRERACKET EXPR CSQRERACKET SEMI",
"ASSIGNMENT : MULT ASSIGNMENT_VAR assign EXPR SEMI",
"STRING_ASSIGNMENT : assign string_id",
"STRING_ASSIGNMENT :",
"ASSIGNMENT_VAR : id",
"ASSIGNMENT_VAR : id OSQRERACKET EXPR CSQRERACKET",
"FUNC_CALL : id OBRACKET EXPR_LIST CBRACKET",
"FUNC_CALL : id OBRACKET CBRACKET",
"IFS : IF OBRACKET EXPR CBRACKET CODE_BLOCK",
"IFS : IF OBRACKET EXPR CBRACKET CODE_BLOCK ELSE CODE_BLOCK",
"IFS : IF OBRACKET EXPR CBRACKET SINGLE_STATMENT",
"IFS : IF OBRACKET EXPR CBRACKET CODE_BLOCK ELSE SINGLE_STATMENT",
"LOOPS : WHILE OBRACKET EXPR CBRACKET CODE_BLOCK",
"LOOPS : FOR OBRACKET ASSIGNMENT EXPR SEMI UPDATES CBRACKET CODE_BLOCK",
"LOOPS : WHILE OBRACKET EXPR CBRACKET SINGLE_STATMENT",
"LOOPS : FOR OBRACKET ASSIGNMENT EXPR SEMI UPDATES CBRACKET SINGLE_STATMENT",
"LOOPS : DO CODE_BLOCK WHILE OBRACKET EXPR CBRACKET SEMI",
"UPDATES : id plus plus",
"UPDATES : plus plus id",
"UPDATES : id minus minus",
"UPDATES : minus minus id",
"UPDATES : id assign EXPR",
"RETURN_STATMENT : RRETURN EXPR SEMI",
"RETURN_STATMENT : RRETURN SEMI",
"RETURN_STATMENT :",
"EXPR_LIST : EXPR_LIST COMMA EXPR",
"EXPR_LIST : EXPR",
"EXPR : EXPR PLUS EXPR",
"EXPR : EXPR MINUS EXPR",
"EXPR : EXPR MULT EXPR",
"EXPR : EXPR DIVIDE EXPR",
"EXPR : EXPR AND EXPR",
"EXPR : EXPR OR EXPR",
"EXPR : EXPR ISEQUAL EXPR",
"EXPR : EXPR NOTEQUAL EXPR",
"EXPR : EXPR GREATER EXPR",
"EXPR : EXPR GREATEREQ EXPR",
"EXPR : EXPR LESS EXPR",
"EXPR : EXPR LESSEQ EXPR",
"EXPR : NOT EXPR",
"EXPR : MULT EXPR",
"EXPR : MINUS EXPR",
"EXPR : BAND id",
"EXPR : NUMS",
"EXPR : BOOL_TRUE",
"EXPR : BOOL_FALSE",
"EXPR : ASSIGNMENT_VAR",
"EXPR : OBRACKET EXPR CBRACKET",
"EXPR : ABS EXPR ABS",
"EXPR : NNULL",
"EXPR : FUNC_CALL",
"EXPR : char",
"EXPR : string_id",
"NUMS : NUM",
"NUMS : HEX",
"NUMS : DEC",
"NUMS : REAL_NUMBER",
"id : ID",
"assign : ASSIGN",
"plus : PLUS",
"minus : MINUS",
"char : CHARR",
"void : VOID",
"string : STRING",
"string_id : STRING_ID",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 774 "proj.y"

#include "lex.yy.c"

char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

void main(){
	global=initGlobalScope();
    yyparse();
}

// char* freshVar1(char* code){
// 	globalVar++;
// 	char strNum[10];
// 	itoa(globalVar,strNum, 10);
// 	char *t = (char*)malloc(sizeof(char)*10);
// 	strcpy(t, "t");
// 	strcat(t, strNum);
// 	return t;
// }

char* freshVar(){
	globalVar++;
	countBeginFunc+=4;
	char strNum[10];
	itoa(globalVar,strNum, 10);
	char *t = (char*)malloc(sizeof(char)*10);
	strcpy(t, "t");
	strcat(t, strNum);
	return t;
}

char* freshLabel(){
	globalLabel++;
	char strNum[10];
	itoa(globalLabel,strNum, 10);
	char *t = (char*)malloc(sizeof(char)*10);
	strcpy(t, "L");
	strcat(t, strNum);
	return t;
}

char* convertToTacFormat(char *str){
	int i=0;
	while(str[i]!='\0'){
		if(str[i]=='\n' && str[i+1]=='#')
		  	str[i+1]='\t';
		
		i=i+1;
	}
	return str;
}

void yyerror(const char *msg)
{
	fflush(stdout);
	fprintf(stderr, "Error: %s at line %d\n", msg,yylineno);
	fprintf(stderr, "Parser does not expect '%s'\n",yytext);
}

int countPushParams(char* code)
{
	int i=0, count, countReduce = 0, numToReduce = 0;
	char strToReduce[5];
	count=countSubString(code, "PushParams")*4;
	
	if (code)
	{
		while(code[i] != '\0')
		{
			if(code[i+1] == 'P' && code[i+2] == 'o')
			{
				i+=11;
				while(code[i] != '\n')
				{
					strToReduce[countReduce] = code[i];
					countReduce++;
					i++;
				}
				
				strToReduce[countReduce] = '\0';
				numToReduce = atoi(strToReduce);
				count -= numToReduce;
				
			}
			countReduce = 0;

			while(code[i]!='\n')
			{	
				i++;
			}
			i++;
		}
	}
	return count;
}

int countSubString(char* source, char* find){
	int count = 0;
	const char *tmp = source;
	while(tmp = strstr(tmp, find))
	{
   		count++;
   		tmp++;
	}
	return count;
}
#line 722 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 56 "proj.y"
	{	
									/*Printtree($1,0); 
									printf("\n");*/
									printf("%s\n",yyval->code);

									scanTree(yystack.l_mark[0]->left,&global);
									checkMainOnce();
									printf("OK\n");}
break;
case 2:
#line 68 "proj.y"
	{
						
						yyval=mknode("PROGRAM",yystack.l_mark[0],NULL ,NULL,NULL);
							strcat(yyval->code,yystack.l_mark[0]->code);	

						}
break;
case 3:
#line 77 "proj.y"
	{
						
						yyval=mknode("FUNC_NODE",yystack.l_mark[-1],yystack.l_mark[0],NULL,NULL);
						strcat(yyval->code,yystack.l_mark[-1]->code);	
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[0]->code);
						}
break;
case 4:
#line 84 "proj.y"
	{
							yyval=mknode("FUNC_NODE",yystack.l_mark[0],NULL,NULL,NULL);
							strcat(yyval->code,yystack.l_mark[0]->code);	
						}
break;
case 5:
#line 93 "proj.y"
	{
							char num[33];

							yyval=mknode("FUNCTION",yystack.l_mark[-5],yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0]);
							strcat(yyval->code,yystack.l_mark[-4]->token);
							strcat(yyval->code,":\nBeginFunc ");
							strcat(yyval->code,itoa(countBeginFunc,num,10));
							strcat(yyval->code,";\n");
							strcat(yyval->code,yystack.l_mark[0]->code);	
							strcat(yyval->code,"\nEndFunc;");	
							countBeginFunc=0;
							globalVar=-1;
							globalLabel=-1;	}
break;
case 6:
#line 106 "proj.y"
	{
							char num[33];

							yyval=mknode("FUNCTION",yystack.l_mark[-5],yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0]);
							strcat(yyval->code,yystack.l_mark[-4]->token);
							strcat(yyval->code,":\nBeginFunc ");
							strcat(yyval->code,itoa(countBeginFunc,num,10));
							strcat(yyval->code,";\n");
							strcat(yyval->code,yystack.l_mark[0]->code);
							strcat(yyval->code,"\nEndFunc;");
							countBeginFunc=0;
							globalVar=-1;
							globalLabel=-1;}
break;
case 7:
#line 121 "proj.y"
	{yyval=mknode("BODY",yystack.l_mark[-2],yystack.l_mark[-1],yystack.l_mark[0],NULL);
							
							if(yystack.l_mark[-1]!=NULL)
							strcat(yyval->code,yystack.l_mark[-1]->code);
							if(yystack.l_mark[0] != NULL)
							strcat(yyval->code, yystack.l_mark[0]->code);}
break;
case 8:
#line 129 "proj.y"
	{yyval=mknode("DECLARATIONS",yystack.l_mark[-1],yystack.l_mark[0],NULL,NULL);}
break;
case 9:
#line 130 "proj.y"
	{yyval=mknode("DECLARATIONS",yystack.l_mark[-1],yystack.l_mark[0],NULL,NULL);}
break;
case 11:
#line 137 "proj.y"
	{yyval=yystack.l_mark[0];}
break;
case 12:
#line 138 "proj.y"
	{ yyval = NULL; }
break;
case 13:
#line 141 "proj.y"
	{yyval=mknode("FPARAM",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);}
break;
case 14:
#line 142 "proj.y"
	{yyval=mknode("FPARAM",NULL,yystack.l_mark[0],NULL,NULL);}
break;
case 15:
#line 148 "proj.y"
	{yyval=mknode(yystack.l_mark[-1]->token,yystack.l_mark[0],NULL,NULL,NULL);}
break;
case 16:
#line 152 "proj.y"
	{yyval=mknode("IDS",yystack.l_mark[-2],yystack.l_mark[-1],NULL,NULL);}
break;
case 17:
#line 153 "proj.y"
	{yyval=mknode("IDS",yystack.l_mark[-2],yystack.l_mark[-1],NULL,NULL);}
break;
case 18:
#line 154 "proj.y"
	{yyval=mknode("IDS",yystack.l_mark[-1],yystack.l_mark[0],NULL,NULL);}
break;
case 19:
#line 157 "proj.y"
	{yyval=mknode("ID",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);countBeginFunc+=4;}
break;
case 20:
#line 158 "proj.y"
	{yyval=mknode("ID",yystack.l_mark[0],NULL,NULL,NULL);countBeginFunc+=4;}
break;
case 21:
#line 162 "proj.y"
	{yyval=mknode("ID",yystack.l_mark[-6],yystack.l_mark[0],mknode("SIZE",yystack.l_mark[-4],NULL,NULL,NULL),yystack.l_mark[-2]);countBeginFunc+=4;}
break;
case 22:
#line 163 "proj.y"
	{yyval=mknode("ID",yystack.l_mark[-4],NULL,mknode("SIZE",yystack.l_mark[-2],NULL,NULL,NULL),yystack.l_mark[0]);countBeginFunc+=4;}
break;
case 23:
#line 167 "proj.y"
	{yyval=yystack.l_mark[0];}
break;
case 24:
#line 168 "proj.y"
	{yyval=yystack.l_mark[0];}
break;
case 25:
#line 171 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 26:
#line 172 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 27:
#line 173 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 28:
#line 174 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 29:
#line 175 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 30:
#line 176 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 31:
#line 177 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 32:
#line 181 "proj.y"
	{ yyval=mknode("STATMENT_NODE",yystack.l_mark[-1],yystack.l_mark[0],NULL,NULL);
							strcat(yyval->code,yystack.l_mark[-1]->code);
							strcat(yyval->code,"\n");
							if(yystack.l_mark[0]!=NULL)
							strcat(yyval->code,yystack.l_mark[0]->code);}
break;
case 33:
#line 186 "proj.y"
	{ yyval=mknode("STATMENT_NODE",yystack.l_mark[-1],yystack.l_mark[0],NULL,NULL);}
break;
case 35:
#line 190 "proj.y"
	{yyval=yystack.l_mark[0];}
break;
case 36:
#line 191 "proj.y"
	{yyval=yystack.l_mark[-1];}
break;
case 37:
#line 192 "proj.y"
	{yyval=yystack.l_mark[0];}
break;
case 38:
#line 193 "proj.y"
	{yyval=yystack.l_mark[0];}
break;
case 39:
#line 196 "proj.y"
	{yyval=yystack.l_mark[-1];}
break;
case 40:
#line 199 "proj.y"
	{
						yyval=mknode("BODY",mknode("STATMENT_NODE",yystack.l_mark[0],NULL,NULL,NULL),NULL,NULL,NULL);
						yyval->code=yystack.l_mark[0]->code;}
break;
case 41:
#line 204 "proj.y"
	{ yyval=mknode(yystack.l_mark[-2]->token,yystack.l_mark[-3],yystack.l_mark[-1],NULL,NULL);
						strcat(yyval->code, yystack.l_mark[-3]->code);
						strcat(yyval->code,yystack.l_mark[-1]->code);
						strcat(yyval->code,"\t");
						strcat(yyval->code,yystack.l_mark[-3]->var);
						strcat(yyval->code,":=");
						strcat(yyval->code,yystack.l_mark[-1]->var);}
break;
case 42:
#line 212 "proj.y"
	{ yyval=mknode(yystack.l_mark[-2]->token,mknode("&",yystack.l_mark[-3],NULL,NULL,NULL),yystack.l_mark[-1],NULL,NULL);
						strcat(yyval->code, yystack.l_mark[-3]->code);
						strcat(yyval->code,yystack.l_mark[-1]->code);
						strcat(yyval->code,"\t");
						strcat(yyval->code,yystack.l_mark[-3]->var);
						strcat(yyval->code,":=");
						strcat(yyval->code,yystack.l_mark[-1]->var);}
break;
case 43:
#line 220 "proj.y"
	{yyval=mknode(yystack.l_mark[-6]->token,yystack.l_mark[-7],mknode("&",yystack.l_mark[-4],NULL,mknode("SIZE",yystack.l_mark[-2],NULL,NULL,NULL),NULL),NULL,NULL);
						char tempFreshVar1[10], tempFreshVar2[10],*tmp=(char*)malloc(sizeof(char)*100000);
							strcpy(tempFreshVar1, freshVar());
							strcat(tmp, yystack.l_mark[-2]->code);
							strcat(tmp, "\t");
							strcat(tmp, tempFreshVar1);
							strcat(tmp, ":=");
							strcat(tmp, yystack.l_mark[-2]->var);
							strcat(tmp, "\t\n\t");
							strcpy(tempFreshVar2, freshVar());
							strcat(tmp, tempFreshVar2);
							strcat(tmp, ":=4*");
							strcat(tmp, tempFreshVar1);
							strcat(tmp, "\n\t");
							strcpy(tempFreshVar1, freshVar());
							strcat(tmp, tempFreshVar1);
							strcat(tmp, ":=");
							strcat(tmp, yystack.l_mark[-4]->token);
							strcat(tmp, "+");
							
							strcat(tmp, tempFreshVar2);
							strcat(tmp, "\n");

							strcat(yyval->code, yystack.l_mark[-7]->code);
							strcat(yyval->code,tmp);
							strcat(yyval->code,"\t");
							strcat(yyval->code,yystack.l_mark[-7]->var);
							strcat(yyval->code,":=");
							strcat(yyval->code,yystack.l_mark[-2]->var);}
break;
case 44:
#line 250 "proj.y"
	{ yyval=mknode(yystack.l_mark[-2]->token,mknode("*",yystack.l_mark[-3],NULL,NULL,NULL),yystack.l_mark[-1],NULL,NULL);		
							strcat(yyval->code, yystack.l_mark[-3]->code);
							strcat(yyval->code,yystack.l_mark[-1]->code);
							strcat(yyval->code,"\t");
							strcat(yyval->code,yystack.l_mark[-3]->var);
							strcat(yyval->code,":=");
							strcat(yyval->code,yystack.l_mark[-1]->var);}
break;
case 45:
#line 260 "proj.y"
	{ yyval=mknode(yystack.l_mark[-1]->token,yystack.l_mark[0],NULL,NULL,NULL);}
break;
case 46:
#line 261 "proj.y"
	{ yyval = NULL; }
break;
case 48:
#line 265 "proj.y"
	{yyval=mknode(yystack.l_mark[-3]->token,mknode("INDEX",yystack.l_mark[-1],NULL,NULL,NULL),NULL,NULL,NULL);
							yyval->isArray = 1;
							char tempFreshVar1[10], tempFreshVar2[10];
							strcpy(tempFreshVar1, freshVar());
							strcat(yyval->code, yystack.l_mark[-1]->code);
							strcat(yyval->code,"\t");
							strcat(yyval->code, tempFreshVar1);
							strcat(yyval->code, ":=");
							strcat(yyval->code, yystack.l_mark[-1]->var);
							strcat(yyval->code, "\t\n\t");
							strcpy(tempFreshVar2, freshVar());
							strcat(yyval->code, tempFreshVar2);
							strcat(yyval->code, ":=4*");
							strcat(yyval->code, tempFreshVar1);
							strcat(yyval->code, "\n\t");
							strcpy(tempFreshVar1, freshVar());
							strcat(yyval->code, tempFreshVar1);
							strcat(yyval->code, ":=");
							strcat(yyval->code, yystack.l_mark[-3]->token);
							strcat(yyval->code, "+");
							strcat(yyval->code, tempFreshVar2);
							strcat(yyval->code, "\n");
							strcat(yyval->var,"*(");
							strcat(yyval->var, tempFreshVar1);
							strcat(yyval->var,")");}
break;
case 49:
#line 293 "proj.y"
	{ yyval=mknode(yystack.l_mark[-3]->token,yystack.l_mark[-1],NULL,NULL,NULL); 
						char tempPushParams[33];
						strcat(yyval->code, yystack.l_mark[-1]->code);
						strcat(yyval->code, yystack.l_mark[-3]->code);
						strcpy(yyval->var,freshVar());
						itoa(countPushParams(yyval->code),tempPushParams, 10);
						basicOperationCode(&(yyval->code),"",yystack.l_mark[-3]->code,yyval->var," LCall ",yystack.l_mark[-3]->token,"_");
						strcat(yyval->code, "\tPopParams ");
						strcat(yyval->code, tempPushParams);
						strcat(yyval->code, "\n");}
break;
case 50:
#line 303 "proj.y"
	{ 
						yyval=mknode(yystack.l_mark[-2]->token,mknode("VARIABLES",NULL,NULL,NULL,NULL),NULL,NULL,NULL);
						strcat(yyval->code, yystack.l_mark[-2]->code);
						strcpy(yyval->var,freshVar());
						basicOperationCode(&(yyval->code),"",yystack.l_mark[-2]->code,yyval->var," LCall ",yystack.l_mark[-2]->token,"_"); }
break;
case 51:
#line 310 "proj.y"
	{
						
						yyval=mknode("IF",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
						yyval->begin = freshLabel();
						yyval->next = freshLabel();
						
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\tIfz ");
						strcat(yyval->code,yystack.l_mark[-2]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[0]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":");
						
						}
break;
case 52:
#line 328 "proj.y"
	{
					
						yyval=mknode("IF",yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0],NULL);
						yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,yystack.l_mark[-4]->code);
						strcat(yyval->code,"\tIfz ");
						strcat(yyval->code,yystack.l_mark[-4]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,"goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\t\n");
						strcat(yyval->code, yystack.l_mark[0]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");
						
						}
break;
case 53:
#line 352 "proj.y"
	{
						
						yyval=mknode("IF",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
						yyval->begin = freshLabel();
							yyval->next = freshLabel();
							strcat(yyval->code,yystack.l_mark[-2]->code);
							strcat(yyval->code,"\tIfz ");
							strcat(yyval->code,yystack.l_mark[-2]->var);
							strcat(yyval->code," goto ");
							strcat(yyval->code,yyval->begin);
							strcat(yyval->code,"\n");
							strcat(yyval->code,yystack.l_mark[0]->code);
							strcat(yyval->code,"\n\t");
							strcat(yyval->code,yyval->begin);
							strcat(yyval->code,":");
						
						}
break;
case 54:
#line 369 "proj.y"
	{ 
						
						yyval=mknode("IF",yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0],NULL);
							yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,yystack.l_mark[-4]->code);
						strcat(yyval->code,"\tIfz ");
						strcat(yyval->code,yystack.l_mark[-4]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,"goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\t\n");
						strcat(yyval->code, yystack.l_mark[0]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");
						
						}
break;
case 55:
#line 395 "proj.y"
	{ 
						
						yyval=mknode("WHILE",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
						yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,"\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\tifz ");
						strcat(yyval->code,yystack.l_mark[-2]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[0]->code);
						strcat(yyval->code,"\n\tgoto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");	
						
						}
break;
case 56:
#line 417 "proj.y"
	{ 
						
						yyval=mknode("FOR",yystack.l_mark[-5],yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0]);
								yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,yystack.l_mark[-5]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\n");
						strcat(yyval->code,yystack.l_mark[-4]->code);
						strcat(yyval->code,"\tifz ");
						strcat(yyval->code,yystack.l_mark[-4]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[0]->code);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\n\tgoto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");	
						
						}
break;
case 57:
#line 442 "proj.y"
	{ 
						
						yyval=mknode("WHILE",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
							yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,"\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\tifz ");
						strcat(yyval->code,yystack.l_mark[-2]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[0]->code);
						strcat(yyval->code,"\n\tgoto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");
						
						}
break;
case 58:
#line 464 "proj.y"
	{ 
						
						yyval=mknode("FOR",yystack.l_mark[-5],yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0]);
						yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,yystack.l_mark[-5]->code);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\n");
						strcat(yyval->code,yystack.l_mark[-4]->code);
						strcat(yyval->code,"\tifz ");
						strcat(yyval->code,yystack.l_mark[-4]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[0]->code);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\n\tgoto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");	
						
						}
break;
case 59:
#line 490 "proj.y"
	{
						
						yyval=mknode("DO WHILE",yystack.l_mark[-2],yystack.l_mark[-5], NULL, NULL);
						yyval->begin = freshLabel();
						yyval->next = freshLabel();
						strcat(yyval->code,"\t");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,":\n");
						strcat(yyval->code,yystack.l_mark[-5]->code);
						strcat(yyval->code,"\n");
						strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code,"\tifz ");
						strcat(yyval->code,yystack.l_mark[-2]->var);
						strcat(yyval->code," goto ");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,"goto ");
						strcat(yyval->code,yyval->begin);
						strcat(yyval->code,"\n\t");
						strcat(yyval->code,yyval->next);
						strcat(yyval->code,":\t");
						
						}
break;
case 60:
#line 515 "proj.y"
	{ yyval=mknode("=",yystack.l_mark[-2],mknode(yystack.l_mark[-1]->token,yystack.l_mark[-2],mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
break;
case 61:
#line 516 "proj.y"
	{ yyval=mknode("=",yystack.l_mark[0],mknode(yystack.l_mark[-1]->token,yystack.l_mark[0],mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
break;
case 62:
#line 517 "proj.y"
	{ yyval=mknode("=",yystack.l_mark[-2],mknode(yystack.l_mark[-1]->token,yystack.l_mark[-2],mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
break;
case 63:
#line 518 "proj.y"
	{ yyval=mknode("=",yystack.l_mark[0],mknode(yystack.l_mark[-1]->token,yystack.l_mark[0],mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
break;
case 64:
#line 519 "proj.y"
	{ yyval=mknode(yystack.l_mark[-1]->token,yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
							strcat(yyval->code,yystack.l_mark[0]->code);
							strcat(yyval->code,"\t");
							strcat(yyval->code,yystack.l_mark[-2]->token);
							strcat(yyval->code,":=");
							strcat(yyval->code,yystack.l_mark[0]->var);}
break;
case 65:
#line 528 "proj.y"
	{ yyval=mknode("RETURN",yystack.l_mark[-1],NULL,NULL,NULL);
						strcat(yyval->code, "\n");
						strcat(yyval->code, yystack.l_mark[-1]->code);
						strcat(yyval->code, "\tRETURN ");
						strcat(yyval->code, yystack.l_mark[-1]->var); }
break;
case 66:
#line 533 "proj.y"
	{ yyval=mknode("RETURN",NULL,NULL,NULL,NULL); 
						strcat(yyval->code, "");}
break;
case 68:
#line 538 "proj.y"
	{ yyval=mknode("VARIABLES",yystack.l_mark[0],yystack.l_mark[-2],NULL,NULL); 
							strcat(yyval->code,yystack.l_mark[-2]->code);
						strcat(yyval->code, "\tPushParams ");
						strcat(yyval->code, yystack.l_mark[-2]->var);
						strcat(yyval->code, "\n");
						strcat(yyval->code, yystack.l_mark[0]->code);
					}
break;
case 69:
#line 545 "proj.y"
	{yyval=mknode("VARIABLES",NULL,yystack.l_mark[0],NULL,NULL); 
					strcat(yyval->code,yystack.l_mark[0]->code);
							strcat(yyval->code, "\tPushParams ");
							strcat(yyval->code, yystack.l_mark[0]->var);
							strcat(yyval->code, "\n");}
break;
case 70:
#line 553 "proj.y"
	{
														yyval=mknode("+",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"+");
													}
break;
case 71:
#line 559 "proj.y"
	{
														yyval=mknode("-",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"-");


													}
break;
case 72:
#line 566 "proj.y"
	{
														yyval=mknode("*",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"*");

													}
break;
case 73:
#line 572 "proj.y"
	{
														yyval=mknode("/",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"/");


													}
break;
case 74:
#line 579 "proj.y"
	{
														yyval=mknode("&&",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"&&");	


													}
break;
case 75:
#line 586 "proj.y"
	{
														yyval=mknode("||",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"||");	


													}
break;
case 76:
#line 593 "proj.y"
	{
														yyval=mknode("==",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"==");


													}
break;
case 77:
#line 600 "proj.y"
	{
														yyval=mknode("!=",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"!=");	

													}
break;
case 78:
#line 606 "proj.y"
	{
														yyval=mknode(">",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,">");

													}
break;
case 79:
#line 612 "proj.y"
	{
														char *tmp = (char*)malloc(sizeof(char)*5000);
														char *temp1 =  (char*)malloc(sizeof(char)*100);
														char *temp2 =  (char*)malloc(sizeof(char)*100);
														char *temp3 =  (char*)malloc(sizeof(char)*100);
														yyval=mknode(">=",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(temp1, freshVar());
														strcpy(yyval->var,temp1);
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,">");
														strcpy(temp2,freshVar());
														strcpy(yyval->var,temp2);
														basicOperationCode(&tmp,yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"==");
														strcpy(temp3, freshVar());
														strcpy(yyval->var,temp3);
														basicOperationCode(&tmp,yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,temp1,temp2,"||");
														strcat(yyval->code,tmp);

													}
break;
case 80:
#line 630 "proj.y"
	{

														yyval=mknode("<",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"<");
													
													}
break;
case 81:
#line 637 "proj.y"
	{
														char *tmp = (char*)malloc(sizeof(char)*5000);
														char *temp1 =  (char*)malloc(sizeof(char)*100);
														char *temp2 =  (char*)malloc(sizeof(char)*100);
														char *temp3 =  (char*)malloc(sizeof(char)*100);
														yyval=mknode("<=",yystack.l_mark[-2],yystack.l_mark[0],NULL,NULL);
														strcpy(temp1, freshVar());
														strcpy(yyval->var,temp1);
														basicOperationCode(&(yyval->code),yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"<");
														strcpy(temp2,freshVar());
														strcpy(yyval->var,temp2);
														basicOperationCode(&tmp,yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,yystack.l_mark[-2]->var,yystack.l_mark[0]->var,"==");
														strcpy(temp3, freshVar());
														strcpy(yyval->var,temp3);
														basicOperationCode(&tmp,yystack.l_mark[-2]->code,yystack.l_mark[0]->code,yyval->var,temp1,temp2,"||");
														strcat(yyval->code,tmp);
													}
break;
case 82:
#line 655 "proj.y"
	{
														yyval=mknode("!",yystack.l_mark[0],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"",yystack.l_mark[0]->code,yyval->var,"!","",yystack.l_mark[0]->var);
													}
break;
case 83:
#line 660 "proj.y"
	{
														yyval=mknode("*",yystack.l_mark[0],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"",yystack.l_mark[0]->code,yyval->var,"*","",yystack.l_mark[0]->var);
													}
break;
case 84:
#line 665 "proj.y"
	{
														yyval=mknode("-",yystack.l_mark[0],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"",yystack.l_mark[0]->code,yyval->var,"-","",yystack.l_mark[0]->var);
													}
break;
case 85:
#line 670 "proj.y"
	{
														yyval=mknode("&",yystack.l_mark[0],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"",yystack.l_mark[0]->code,yyval->var,"&","",yystack.l_mark[0]->var);
													}
break;
case 86:
#line 675 "proj.y"
	{
														yyval=yystack.l_mark[0];
														yyval->var=yystack.l_mark[0]->token;
														yyval->code=(char*)malloc(sizeof(char)+1);
													}
break;
case 87:
#line 680 "proj.y"
	{
														yyval=mknode("true",NULL,NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"","",yyval->var,"true","","");
													}
break;
case 88:
#line 685 "proj.y"
	{
														yyval=mknode("false",NULL,NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"","",yyval->var,"false","","");	
													}
break;
case 89:
#line 691 "proj.y"
	{
														yyval=yystack.l_mark[0];
														yyval->var=yystack.l_mark[0]->token;
													}
break;
case 90:
#line 695 "proj.y"
	{yyval=yystack.l_mark[-1];}
break;
case 91:
#line 696 "proj.y"
	{
														yyval=mknode("ABS",yystack.l_mark[-1],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"",yystack.l_mark[-1]->code,yyval->var,"|","|",yystack.l_mark[-1]->var);
													}
break;
case 92:
#line 701 "proj.y"
	{
														yyval=mknode("NULL",NULL,NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),"","",yyval->var,"NULL","","");
													}
break;
case 93:
#line 706 "proj.y"
	{
														yyval=mknode("FUNC CALL",yystack.l_mark[0],NULL,NULL,NULL);
														
														strcpy(yyval->code, yystack.l_mark[0]->code);
														strcpy(yyval->var,yystack.l_mark[0]->var);
														
													}
break;
case 94:
#line 713 "proj.y"
	{
														yyval=mknode("CHAR VAR",yystack.l_mark[0],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[0]->code,"",yyval->var,yystack.l_mark[0]->var,"","");
													}
break;
case 95:
#line 718 "proj.y"
	{
														yyval=mknode("STRING VAR",yystack.l_mark[0],NULL,NULL,NULL);
														strcpy(yyval->var,freshVar());
														basicOperationCode(&(yyval->code),yystack.l_mark[0]->code,"",yyval->var,yystack.l_mark[0]->var,"","");
													}
break;
case 96:
#line 725 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 97:
#line 726 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 98:
#line 727 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 99:
#line 728 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 100:
#line 731 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);
						strcpy(yyval->var, yytext);
}
break;
case 101:
#line 736 "proj.y"
	{yyval=mknode("=",NULL,NULL,NULL,NULL);}
break;
case 102:
#line 739 "proj.y"
	{yyval=mknode("+",NULL,NULL,NULL,NULL);}
break;
case 103:
#line 742 "proj.y"
	{yyval=mknode("-",NULL,NULL,NULL,NULL);}
break;
case 104:
#line 745 "proj.y"
	{
						yytext[2] = '\0';
						yyval=mknode(&yytext[1],NULL,NULL,NULL,NULL);}
break;
case 105:
#line 750 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 106:
#line 753 "proj.y"
	{yyval=mknode(yytext,NULL,NULL,NULL,NULL);}
break;
case 107:
#line 756 "proj.y"
	{
				int i;char c;
				char *tmp;
				tmp=(char*)malloc(sizeof(char)*100);
				strcpy(tmp,yytext);
				/*Remove last " from the string variable*/
				for(i=1;yytext[i]!='\0';i++){
					c=yytext[i];
					if(yytext[i]=='"')
						yytext[i]='\0';
					}
				yyval=mknode(&yytext[1],NULL,NULL,NULL,NULL);
				yyval->code=(char*)malloc(sizeof(char)+1);
				yyval->var=tmp;
				}
break;
#line 1845 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
