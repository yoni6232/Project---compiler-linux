%{
#include "y.tab.h"
extern int yylineno;

%}
%x C_COMMENT

%%
"/*"				{BEGIN(C_COMMENT);}
<C_COMMENT>"*/"		{BEGIN(INITIAL);}
<C_COMMENT>.		{ }
<C_COMMENT>\n 		{ }


"function"				return FUNC;
"bool"					return BOOL;
"char"					return CHAR;
"void"					return VOID;
"int"					return INT;
"real"					return REAL;
"var"					return VAR;
"string" 				return STRING;
"int* "|"int *"			return INTP;
"char* "|"char *"		return CHARP;
"real* "|"real *"		return REALP;
"if" 					return IF;
"else"					return ELSE;
"while"					return WHILE;
"do"					return DO;
"for"					return FOR;
"return" 				return RRETURN;
"null" 					return NNULL;


"&&" 					return AND;
"/" 					return DIVIDE;
"=" 					return ASSIGN;
"==" 					return ISEQUAL;
">" 					return GREATER;
">=" 					return GREATEREQ;
"<" 					return LESS;
"<=" 					return LESSEQ;
"-" 					return MINUS;
"!" 					return NOT;
"!=" 					return NOTEQUAL;
"||" 					return OR;
"+" 					return PLUS;
"*" 					return MULT;
"&" 					return BAND;

"true"					return BOOL_TRUE;
"false"					return BOOL_FALSE;
";"						return SEMI;
","						return COMMA;
"|"						return ABS;
"{" 					return OBRACE;
"}" 					return CBRACE;
"(" 					return OBRACKET;
")" 					return CBRACKET;
"["						return OSQRERACKET;
"]"						return CSQRERACKET;
'(\\.|[^"\\])'  			return CHARR;

0|[1-9][0-9]* 			    return NUM;
[A-Za-z][a-zA-Z0-9_]*       return ID;
\"(\\.|[^"\\])*\"           return STRING_ID;
0[1-9][0-9]*			return DEC;
0[x|X][0-9A-F]+ 		return HEX;
[0-9]*[\.]?[0-9]+|[-+]?[0-9]*[\.]?[0-9]+([eE][-+]?[0-9]+)?	{ return REAL_NUMBER; };


[ \t\f\v]				;
[\n]					{ yylineno = yylineno + 1; }

. 						return yytext[0];

%%
