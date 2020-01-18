%{
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

scope* global;

%}

%token BOOL VOID CHAR INT STRING INTP CHARP REALP REAL VAR;
%token IF ELSE WHILE DO FOR RRETURN NNULL;

%token AND DIVIDE ASSIGN ISEQUAL GREATER GREATEREQ LESS LESSEQ MINUS NOT NOTEQUAL OR PLUS MULT BAND;

%token BOOL_TRUE BOOL_FALSE FUNC;

%token CHARR ;

%token NUM ID  HEX DEC REAL_NUMBER;

%token STRING_ID;

%token SEMI COMMA ABS OBRACE CBRACE OBRACKET CBRACKET OSQRERACKET CSQRERACKET;

%token OCMNT SINMGLE_COMMENT;
%token CCMNT;

%left AND OR 
%left ISEQUAL NOTEQUAL GREATER GREATEREQ LESS LESSEQ
%left PLUS MINUS 
%left MULT DIVIDE
%right ASSIGN NOT 

%%

START:					 PROGRAM {	
									/*Printtree($1,0); 
									printf("\n");*/
									scanTree($1->left,&global);
									checkMainOnce();
									printf("OK\n");}
						;
						/* 
The program can contain many functions above the main function
*/
PROGRAM:				FUNCTIONS  {
						
						$$=mknode("PROGRAM",$1,NULL ,NULL,NULL);
						
						}
						;	
						
						
FUNCTIONS:				FUNCTION FUNCTIONS{
						
						$$=mknode("FUNC_NODE",$1,$2,NULL,NULL);
						
						}
						| { $$ = NULL; };
						;

/*
FUNC_TYPE can be boolean , char , int , charp , intp or void.
The body can contain variable declarations, statements and return statment in this order only. */					
FUNCTION:				FUNC TYPE id OBRACKET F_PARAMS CBRACKET CODE_BLOCK {
						
							$$=mknode("FUNCTION",$2,$3,$5,$7);}
						| FUNC void id OBRACKET F_PARAMS CBRACKET CODE_BLOCK {
						
							$$=mknode("FUNCTION",$2,$3,$5,$7);}
						;
						
BODY:					DECLERATIONS STATMENTS RETURN_STATMENT {$$=mknode("BODY",$1,$2,$3,NULL);}
						;

DECLERATIONS:			FUNCTION DECLERATIONS {$$=mknode("DECLARATIONS",$1,$2,NULL,NULL);}
						| VAR_DECLERACTION STATMENTS DECLERATIONS {$$=mknode("DECLARATIONS",$1,$2,$3,NULL);}
						| { $$ = NULL; };
						;

						
/*
Function Parameters (can be empty)
*/					
F_PARAMS:				F_PARAMSS {$$=$1;}
						| { $$ = NULL; };
						;

F_PARAMSS:				F_PARAMSS SEMI PARAM {$$=mknode("FPARAM",$1,$3,NULL,NULL);}
						| PARAM {$$=mknode("FPARAM",NULL,$1,NULL,NULL);}
						;

/*
The types of the parameters can be boolean , char , int , charp , intp or string
*/
PARAM:					PARAM_TYPE IDS {$$=mknode($1->token,$2,NULL,NULL,NULL);}
						;
						

VAR_DECLERACTION:		VAR TYPE IDS SEMI {$$=mknode("IDS",$2,$3,NULL,NULL);}
						| string SID SEMI {$$=mknode("IDS",$1,$2,NULL,NULL);}
						| VAR TYPE ASSIGNMENT {$$=mknode("IDS",$2,$3,NULL,NULL);}
						;

IDS:					id COMMA IDS {$$=mknode("ID",$1,$3,NULL,NULL);}
						| id {$$=mknode("ID",$1,NULL,NULL,NULL);}
						;

						
SID:					id OSQRERACKET EXPR CSQRERACKET STRING_ASSIGNMENT COMMA SID {$$=mknode("ID",$1,$7,mknode("SIZE",$3,NULL,NULL,NULL),$5);}
						| id OSQRERACKET EXPR CSQRERACKET STRING_ASSIGNMENT{$$=mknode("ID",$1,NULL,mknode("SIZE",$3,NULL,NULL,NULL),$5);}
						
						;
						
PARAM_TYPE:				TYPE {$$=$1;}
						| string {$$=$1;} 
						;
						
TYPE:					BOOL {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| CHAR {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| INT {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| REAL {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| INTP {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| CHARP  {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| REALP {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						;
						
						
STATMENTS:				STATMENT STATMENTS{ $$=mknode("STATMENT_NODE",$1,$2,NULL,NULL);}
						| CODE_BLOCK STATMENTS { $$=mknode("STATMENT_NODE",$1,$2,NULL,NULL);}
						| { $$ = NULL; };
						;
						
STATMENT:				ASSIGNMENT{$$=$1;}		
						| FUNC_CALL	SEMI{$$=$1;}	
						| IFS {$$=$1;}
						| LOOPS {$$=$1;}
						;

CODE_BLOCK:				OBRACE BODY CBRACE {$$=$2;}
						;

SINGLE_STATMENT:		STATMENT {
						$$=mknode("BODY",mknode("STATMENT_NODE",$1,NULL,NULL,NULL),NULL,NULL,NULL);
						}
						;

ASSIGNMENT:				ASSIGNMENT_VAR assign EXPR SEMI{ $$=mknode($2->token,$1,$3,NULL,NULL);}

						| BAND ASSIGNMENT_VAR assign EXPR SEMI{ $$=mknode($3->token,mknode("&",$2,NULL,NULL,NULL),$4,NULL,NULL);}
						
						| ASSIGNMENT_VAR assign BAND id OSQRERACKET EXPR CSQRERACKET SEMI{$$=mknode($2->token,$1,mknode("&",$4,NULL,mknode("SIZE",$6,NULL,NULL,NULL),NULL),NULL,NULL);}
						
						| MULT ASSIGNMENT_VAR assign EXPR SEMI{ $$=mknode($3->token,mknode("*",$2,NULL,NULL,NULL),$4,NULL,NULL);}

						;

STRING_ASSIGNMENT:		assign string_id { $$=mknode($1->token,$2,NULL,NULL,NULL);}
						|{ $$ = NULL; };
						;

ASSIGNMENT_VAR:			id
						| id OSQRERACKET EXPR CSQRERACKET {$$=mknode($1->token,mknode("INDEX",$3,NULL,NULL,NULL),NULL,NULL,NULL);}
						;
						
						
FUNC_CALL:				id OBRACKET EXPR_LIST CBRACKET { $$=mknode($1->token,$3,NULL,NULL,NULL); }
						| id OBRACKET CBRACKET { $$=mknode($1->token,mknode("VARIABLES",NULL,NULL,NULL,NULL),NULL,NULL,NULL); }
						;					

IFS:					IF OBRACKET EXPR CBRACKET CODE_BLOCK{
						
						$$=mknode("IF",$3,$5,NULL,NULL);
						
						}
						| IF OBRACKET EXPR CBRACKET CODE_BLOCK ELSE CODE_BLOCK{
					
						$$=mknode("IF",$3,$5,$7,NULL);
						
						}
						| IF OBRACKET EXPR CBRACKET SINGLE_STATMENT{
						
						$$=mknode("IF",$3,$5,NULL,NULL);
						
						}
						| IF OBRACKET EXPR CBRACKET CODE_BLOCK ELSE SINGLE_STATMENT { 
						
						$$=mknode("IF",$3,$5,$7,NULL);
						
						}
						;
						
LOOPS:					WHILE OBRACKET EXPR CBRACKET CODE_BLOCK{ 
						
						$$=mknode("WHILE",$3,$5,NULL,NULL);
						
						}
						| FOR OBRACKET ASSIGNMENT EXPR SEMI UPDATES CBRACKET CODE_BLOCK{ 
						
						$$=mknode("FOR",$3,$4,$6,$8);
						
						}
						| WHILE OBRACKET EXPR CBRACKET SINGLE_STATMENT{ 
						
						$$=mknode("WHILE",$3,$5,NULL,NULL);
						
						}
						| FOR OBRACKET ASSIGNMENT EXPR SEMI UPDATES CBRACKET SINGLE_STATMENT{ 
						
						$$=mknode("FOR",$3,$4,$6,$8);
						
						}
						
						| DO CODE_BLOCK WHILE OBRACKET EXPR CBRACKET SEMI{
						
						$$=mknode("DO WHILE",$5,$2, NULL, NULL);
						
						}		
						;
						
UPDATES:				id plus plus{ $$=mknode("=",$1,mknode($2->token,$1,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| plus plus id { $$=mknode("=",$3,mknode($2->token,$3,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| id minus minus { $$=mknode("=",$1,mknode($2->token,$1,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| minus minus id { $$=mknode("=",$3,mknode($2->token,$3,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| id assign EXPR { $$=mknode($2->token,$1,$3,NULL,NULL);}
						;
						
				
RETURN_STATMENT:		RRETURN EXPR SEMI { $$=mknode("RETURN",$2,NULL,NULL,NULL); }
						| RRETURN SEMI { $$=mknode("RETURN",NULL,NULL,NULL,NULL); }
						|
						;

EXPR_LIST:				EXPR_LIST COMMA EXPR { $$=mknode("VARIABLES",$1,$3,NULL,NULL); }
						| EXPR{$$=mknode("VARIABLES",NULL,$1,NULL,NULL); }
						;						
	

						
EXPR:					EXPR PLUS EXPR				{$$=mknode("+",$1,$3,NULL,NULL);}
						| EXPR MINUS EXPR			{$$=mknode("-",$1,$3,NULL,NULL);}
						| EXPR MULT EXPR			{$$=mknode("*",$1,$3,NULL,NULL);}
						| EXPR DIVIDE EXPR			{$$=mknode("/",$1,$3,NULL,NULL);}
						| EXPR AND EXPR				{$$=mknode("&&",$1,$3,NULL,NULL);}
						| EXPR OR EXPR				{$$=mknode("||",$1,$3,NULL,NULL);}
						| EXPR ISEQUAL EXPR			{$$=mknode("==",$1,$3,NULL,NULL);}
						| EXPR NOTEQUAL EXPR		{$$=mknode("!=",$1,$3,NULL,NULL);}
						| EXPR GREATER EXPR			{$$=mknode(">",$1,$3,NULL,NULL);}
						| EXPR GREATEREQ EXPR		{$$=mknode(">=",$1,$3,NULL,NULL);}
						| EXPR LESS EXPR			{$$=mknode("<",$1,$3,NULL,NULL);}
						| EXPR LESSEQ EXPR			{$$=mknode("<=",$1,$3,NULL,NULL);}
						| NOT EXPR					{$$=mknode("!",$2,NULL,NULL,NULL);}
						| MULT EXPR					{$$=mknode("^",$2,NULL,NULL,NULL);}
						| MINUS EXPR 				{$$=mknode("-",$2,NULL,NULL,NULL);}
						| BAND id					{$$=mknode("&",$2,NULL,NULL,NULL);}
						| NUMS						{$$=$1;}
						| BOOL_TRUE					{$$=mknode("true",NULL,NULL,NULL,NULL);}
						| BOOL_FALSE				{$$=mknode("false",NULL,NULL,NULL,NULL);}
						| ASSIGNMENT_VAR			{$$=$1;}
						| OBRACKET EXPR CBRACKET	{$$=$2;}
						| ABS id ABS 				{$$=mknode("ABS",$2,NULL,NULL,NULL);}
						| NNULL						{$$=mknode("NULL",NULL,NULL,NULL,NULL);}
						| FUNC_CALL					{ $$=mknode("FUNC CALL",$1,NULL,NULL,NULL);}
						| char						{$$=mknode("CHAR VAR",$1,NULL,NULL,NULL);}
						| string_id					{$$=mknode("STRING VAR",$1,NULL,NULL,NULL);}

						;	
						
NUMS:					NUM				{$$=mknode(yytext,NULL,NULL,NULL,NULL);}	
						| HEX			{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| DEC   		{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| REAL_NUMBER	{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						;
						
id:						ID 	{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						;

assign:					ASSIGN {$$=mknode("=",NULL,NULL,NULL,NULL);}
						;

plus:					PLUS {$$=mknode("+",NULL,NULL,NULL,NULL);}
						;
						
minus:					MINUS {$$=mknode("-",NULL,NULL,NULL,NULL);}
						;
						
char:					CHARR {
						yytext[2] = '\0';
						$$=mknode(&yytext[1],NULL,NULL,NULL,NULL);}
						;

void:					VOID {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						;

string:					STRING {$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						;

string_id:				STRING_ID {
						int i;char c;
						//Remove last " from the string variable
						for(i=1;yytext[i]!='\0';i++){
							c=yytext[i];
							if(yytext[i]=='"')
								yytext[i]='\0';
							}
						$$=mknode(&yytext[1],NULL,NULL,NULL,NULL);	
						}
						;

%%

#include "lex.yy.c"

int main(){
	
	global=initGlobalScope();
    return yyparse();
	
}

void yyerror(const char *msg)
{
	fflush(stdout);
	fprintf(stderr, "Error: %s at line %d\n", msg,yylineno);
	fprintf(stderr, "Parser does not expect '%s'\n",yytext);
}


