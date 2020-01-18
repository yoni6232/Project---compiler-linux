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
char* freshVar();
char* freshLabel();
char* itoa(int value, char* result, int base);
int countSubString(char* source, char* find);

scope* global;
int globalVar = -1;
int globalLabel = -1;
int countBeginFunc = 0;


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
									printf("%s\n",$$->code);

									scanTree($1->left,&global);
									checkMainOnce();
									printf("OK\n");}
						;
						/* 
The program can contain many functions above the main function
*/
PROGRAM:				FUNCTIONS  {
						
						$$=mknode("PROGRAM",$1,NULL ,NULL,NULL);
							strcat($$->code,$1->code);	

						}
						;	
						
						
FUNCTIONS:				FUNCTION FUNCTIONS{
						
						$$=mknode("FUNC_NODE",$1,$2,NULL,NULL);
						strcat($$->code,$1->code);	
						strcat($$->code,"\n");
						strcat($$->code,$2->code);
						}
						| FUNCTION {
							$$=mknode("FUNC_NODE",$1,NULL,NULL,NULL);
							strcat($$->code,$1->code);	
						}
						;

/*
FUNC_TYPE can be boolean , char , int , charp , intp or void.
The body can contain variable declarations, statements and return statment in this order only. */					
FUNCTION:				FUNC TYPE id OBRACKET F_PARAMS CBRACKET CODE_BLOCK {
							char num[33];

							$$=mknode("FUNCTION",$2,$3,$5,$7);
							strcat($$->code,$3->token);
							strcat($$->code,":\nBeginFunc ");
							strcat($$->code,itoa(countBeginFunc,num,10));
							strcat($$->code,";\n");
							strcat($$->code,$7->code);	
							strcat($$->code,"\nEndFunc;");	
							countBeginFunc=0;
							globalVar=-1;
							globalLabel=-1;	}
						| FUNC void id OBRACKET F_PARAMS CBRACKET CODE_BLOCK {
							char num[33];

							$$=mknode("FUNCTION",$2,$3,$5,$7);
							strcat($$->code,$3->token);
							strcat($$->code,":\nBeginFunc ");
							strcat($$->code,itoa(countBeginFunc,num,10));
							strcat($$->code,";\n");
							strcat($$->code,$7->code);
							strcat($$->code,"\nEndFunc;");
							countBeginFunc=0;
							globalVar=-1;
							globalLabel=-1;}
						;
						
BODY:					DECLERATIONS STATMENTS RETURN_STATMENT {$$=mknode("BODY",$1,$2,$3,NULL);
							
							if($2!=NULL)
							strcat($$->code,$2->code);
							if($3 != NULL)
							strcat($$->code, $3->code);}
						;

DECLERATIONS:			FUNCTION DECLERATIONS {$$=mknode("DECLARATIONS",$1,$2,NULL,NULL);}
				| VAR_DECLERACTION DECLERATIONS {$$=mknode("DECLARATIONS",$1,$2,NULL,NULL);}
				|
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

IDS:					id COMMA IDS {$$=mknode("ID",$1,$3,NULL,NULL);countBeginFunc+=4;}
						| id {$$=mknode("ID",$1,NULL,NULL,NULL);countBeginFunc+=4;}
						;

						
SID:					id OSQRERACKET EXPR CSQRERACKET STRING_ASSIGNMENT COMMA SID {$$=mknode("ID",$1,$7,mknode("SIZE",$3,NULL,NULL,NULL),$5);countBeginFunc+=4;}
						| id OSQRERACKET EXPR CSQRERACKET STRING_ASSIGNMENT{$$=mknode("ID",$1,NULL,mknode("SIZE",$3,NULL,NULL,NULL),$5);countBeginFunc+=4;}
						
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
						
						
STATMENTS:				STATMENT STATMENTS{ $$=mknode("STATMENT_NODE",$1,$2,NULL,NULL);
							strcat($$->code,$1->code);
							strcat($$->code,"\n");
							if($2!=NULL)
							strcat($$->code,$2->code);}
						| CODE_BLOCK STATMENTS { $$=mknode("STATMENT_NODE",$1,$2,NULL,NULL);}
						| 
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
						$$->code=$1->code;}
						;

ASSIGNMENT:				ASSIGNMENT_VAR assign EXPR SEMI{ $$=mknode($2->token,$1,$3,NULL,NULL);
						strcat($$->code, $1->code);
						strcat($$->code,$3->code);
						strcat($$->code,"\t");
						strcat($$->code,$1->var);
						strcat($$->code,":=");
						strcat($$->code,$3->var);}

						| BAND ASSIGNMENT_VAR assign EXPR SEMI{ $$=mknode($3->token,mknode("&",$2,NULL,NULL,NULL),$4,NULL,NULL);
						strcat($$->code, $2->code);
						strcat($$->code,$4->code);
						strcat($$->code,"\t");
						strcat($$->code,$2->var);
						strcat($$->code,":=");
						strcat($$->code,$4->var);}
						
						| ASSIGNMENT_VAR assign BAND id OSQRERACKET EXPR CSQRERACKET SEMI{$$=mknode($2->token,$1,mknode("&",$4,NULL,mknode("SIZE",$6,NULL,NULL,NULL),NULL),NULL,NULL);
						char tempFreshVar1[10], tempFreshVar2[10],*tmp=(char*)malloc(sizeof(char)*100000);
							strcpy(tempFreshVar1, freshVar());
							strcat(tmp, $6->code);
							strcat(tmp, "\t");
							strcat(tmp, tempFreshVar1);
							strcat(tmp, ":=");
							strcat(tmp, $6->var);
							strcat(tmp, "\t\n\t");
							strcpy(tempFreshVar2, freshVar());
							strcat(tmp, tempFreshVar2);
							strcat(tmp, ":=4*");
							strcat(tmp, tempFreshVar1);
							strcat(tmp, "\n\t");
							strcpy(tempFreshVar1, freshVar());
							strcat(tmp, tempFreshVar1);
							strcat(tmp, ":=");
							strcat(tmp, $4->token);
							strcat(tmp, "+");
							
							strcat(tmp, tempFreshVar2);
							strcat(tmp, "\n");

							strcat($$->code, $1->code);
							strcat($$->code,tmp);
							strcat($$->code,"\t");
							strcat($$->code,$1->var);
							strcat($$->code,":=");
							strcat($$->code,$6->var);}
						
						| MULT ASSIGNMENT_VAR assign EXPR SEMI{ $$=mknode($3->token,mknode("*",$2,NULL,NULL,NULL),$4,NULL,NULL);		
							strcat($$->code, $2->code);
							strcat($$->code,$4->code);
							strcat($$->code,"\t");
							strcat($$->code,$2->var);
							strcat($$->code,":=");
							strcat($$->code,$4->var);}

						;

STRING_ASSIGNMENT:		assign string_id { $$=mknode($1->token,$2,NULL,NULL,NULL);}
						|{ $$ = NULL; };
						;

ASSIGNMENT_VAR:			id
						| id OSQRERACKET EXPR CSQRERACKET {$$=mknode($1->token,mknode("INDEX",$3,NULL,NULL,NULL),NULL,NULL,NULL);
							$$->isArray = 1;
							char tempFreshVar1[10], tempFreshVar2[10];
							strcpy(tempFreshVar1, freshVar());
							strcat($$->code, $3->code);
							strcat($$->code,"\t");
							strcat($$->code, tempFreshVar1);
							strcat($$->code, ":=");
							strcat($$->code, $3->var);
							strcat($$->code, "\t\n\t");
							strcpy(tempFreshVar2, freshVar());
							strcat($$->code, tempFreshVar2);
							strcat($$->code, ":=4*");
							strcat($$->code, tempFreshVar1);
							strcat($$->code, "\n\t");
							strcpy(tempFreshVar1, freshVar());
							strcat($$->code, tempFreshVar1);
							strcat($$->code, ":=");
							strcat($$->code, $1->token);
							strcat($$->code, "+");
							strcat($$->code, tempFreshVar2);
							strcat($$->code, "\n");
							strcat($$->var,"*(");
							strcat($$->var, tempFreshVar1);
							strcat($$->var,")");}
						;
						
						
FUNC_CALL:				id OBRACKET EXPR_LIST CBRACKET { $$=mknode($1->token,$3,NULL,NULL,NULL); 
						char tempPushParams[33];
						strcat($$->code, $3->code);
						strcat($$->code, $1->code);
						strcpy($$->var,freshVar());
						itoa(countPushParams($$->code),tempPushParams, 10);
						basicOperationCode(&($$->code),"",$1->code,$$->var," LCall ",$1->token,"_");
						strcat($$->code, "\tPopParams ");
						strcat($$->code, tempPushParams);
						strcat($$->code, "\n");}
						| id OBRACKET CBRACKET { 
						$$=mknode($1->token,mknode("VARIABLES",NULL,NULL,NULL,NULL),NULL,NULL,NULL);
						strcat($$->code, $1->code);
						strcpy($$->var,freshVar());
						basicOperationCode(&($$->code),"",$1->code,$$->var," LCall ",$1->token,"_"); }
						;					

IFS:					IF OBRACKET EXPR CBRACKET CODE_BLOCK{
						
						$$=mknode("IF",$3,$5,NULL,NULL);
						$$->begin = freshLabel();
						$$->next = freshLabel();
						
						strcat($$->code,$3->code);
						strcat($$->code,"\tIfz ");
						strcat($$->code,$3->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n");
						strcat($$->code,$5->code);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":");
						
						}
						| IF OBRACKET EXPR CBRACKET CODE_BLOCK ELSE CODE_BLOCK{
					
						$$=mknode("IF",$3,$5,$7,NULL);
						$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,$3->code);
						strcat($$->code,"\tIfz ");
						strcat($$->code,$3->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n");
						strcat($$->code,$5->code);
						strcat($$->code,"\n\t");
						strcat($$->code,"goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\t\n");
						strcat($$->code, $7->code);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");
						
						}
						| IF OBRACKET EXPR CBRACKET SINGLE_STATMENT{
						
						$$=mknode("IF",$3,$5,NULL,NULL);
						$$->begin = freshLabel();
							$$->next = freshLabel();
							strcat($$->code,$3->code);
							strcat($$->code,"\tIfz ");
							strcat($$->code,$3->var);
							strcat($$->code," goto ");
							strcat($$->code,$$->begin);
							strcat($$->code,"\n");
							strcat($$->code,$5->code);
							strcat($$->code,"\n\t");
							strcat($$->code,$$->begin);
							strcat($$->code,":");
						
						}
						| IF OBRACKET EXPR CBRACKET CODE_BLOCK ELSE SINGLE_STATMENT { 
						
						$$=mknode("IF",$3,$5,$7,NULL);
							$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,$3->code);
						strcat($$->code,"\tIfz ");
						strcat($$->code,$3->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n");
						strcat($$->code,$5->code);
						strcat($$->code,"\n\t");
						strcat($$->code,"goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\t\n");
						strcat($$->code, $7->code);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");
						
						}
						;
						
LOOPS:					WHILE OBRACKET EXPR CBRACKET CODE_BLOCK{ 
						
						$$=mknode("WHILE",$3,$5,NULL,NULL);
						$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,"\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\n");
						strcat($$->code,$3->code);
						strcat($$->code,"\tifz ");
						strcat($$->code,$3->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n");
						strcat($$->code,$5->code);
						strcat($$->code,"\n\tgoto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");	
						
						}
						| FOR OBRACKET ASSIGNMENT EXPR SEMI UPDATES CBRACKET CODE_BLOCK{ 
						
						$$=mknode("FOR",$3,$4,$6,$8);
								$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,$3->code);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\n");
						strcat($$->code,$4->code);
						strcat($$->code,"\tifz ");
						strcat($$->code,$4->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n");
						strcat($$->code,$8->code);
						strcat($$->code,"\n");
						strcat($$->code,$6->code);
						strcat($$->code,"\n\tgoto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");	
						
						}
						| WHILE OBRACKET EXPR CBRACKET SINGLE_STATMENT{ 
						
						$$=mknode("WHILE",$3,$5,NULL,NULL);
							$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,"\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\n");
						strcat($$->code,$3->code);
						strcat($$->code,"\tifz ");
						strcat($$->code,$3->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n");
						strcat($$->code,$5->code);
						strcat($$->code,"\n\tgoto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");
						
						}
						| FOR OBRACKET ASSIGNMENT EXPR SEMI UPDATES CBRACKET SINGLE_STATMENT{ 
						
						$$=mknode("FOR",$3,$4,$6,$8);
						$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,$3->code);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\n");
						strcat($$->code,$4->code);
						strcat($$->code,"\tifz ");
						strcat($$->code,$4->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n");
						strcat($$->code,$8->code);
						strcat($$->code,"\n");
						strcat($$->code,$6->code);
						strcat($$->code,"\n\tgoto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");	
						
						}
						
						| DO CODE_BLOCK WHILE OBRACKET EXPR CBRACKET SEMI{
						
						$$=mknode("DO WHILE",$5,$2, NULL, NULL);
						$$->begin = freshLabel();
						$$->next = freshLabel();
						strcat($$->code,"\t");
						strcat($$->code,$$->begin);
						strcat($$->code,":\n");
						strcat($$->code,$2->code);
						strcat($$->code,"\n");
						strcat($$->code,$5->code);
						strcat($$->code,"\tifz ");
						strcat($$->code,$5->var);
						strcat($$->code," goto ");
						strcat($$->code,$$->next);
						strcat($$->code,"\n\t");
						strcat($$->code,"goto ");
						strcat($$->code,$$->begin);
						strcat($$->code,"\n\t");
						strcat($$->code,$$->next);
						strcat($$->code,":\t");
						
						}		
						;
						
UPDATES:				id plus plus{ $$=mknode("=",$1,mknode($2->token,$1,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| plus plus id { $$=mknode("=",$3,mknode($2->token,$3,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| id minus minus { $$=mknode("=",$1,mknode($2->token,$1,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| minus minus id { $$=mknode("=",$3,mknode($2->token,$3,mknode("1",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL); }
						| id assign EXPR { $$=mknode($2->token,$1,$3,NULL,NULL);
							strcat($$->code,$3->code);
							strcat($$->code,"\t");
							strcat($$->code,$1->token);
							strcat($$->code,":=");
							strcat($$->code,$3->var);}
						;
						
				
RETURN_STATMENT:		RRETURN EXPR SEMI { $$=mknode("RETURN",$2,NULL,NULL,NULL);
						strcat($$->code, "\n");
						strcat($$->code, $2->code);
						strcat($$->code, "\tRETURN ");
						strcat($$->code, $2->var); }
						| RRETURN SEMI { $$=mknode("RETURN",NULL,NULL,NULL,NULL); 
						strcat($$->code, "");}
						|
						;

EXPR_LIST:				EXPR_LIST COMMA EXPR { $$=mknode("VARIABLES",$3,$1,NULL,NULL); 
							strcat($$->code,$1->code);
						strcat($$->code, "\tPushParams ");
						strcat($$->code, $1->var);
						strcat($$->code, "\n");
						strcat($$->code, $3->code);
					}
						| EXPR{$$=mknode("VARIABLES",NULL,$1,NULL,NULL); 
					strcat($$->code,$1->code);
							strcat($$->code, "\tPushParams ");
							strcat($$->code, $1->var);
							strcat($$->code, "\n");}
						;						
	

EXPR:					EXPR PLUS EXPR				{
														$$=mknode("+",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"+");
													}

						| EXPR MINUS EXPR			{
														$$=mknode("-",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"-");


													}
						| EXPR MULT EXPR			{
														$$=mknode("*",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"*");

													}
						| EXPR DIVIDE EXPR			{
														$$=mknode("/",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"/");


													}
						| EXPR AND EXPR				{
														$$=mknode("&&",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"&&");	


													}
						| EXPR OR EXPR				{
														$$=mknode("||",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"||");	


													}
						| EXPR ISEQUAL EXPR			{
														$$=mknode("==",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"==");


													}
						| EXPR NOTEQUAL EXPR		{
														$$=mknode("!=",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"!=");	

													}
						| EXPR GREATER EXPR			{
														$$=mknode(">",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,">");

													}
						| EXPR GREATEREQ EXPR		{
														char *tmp = (char*)malloc(sizeof(char)*5000);
														char *temp1 =  (char*)malloc(sizeof(char)*100);
														char *temp2 =  (char*)malloc(sizeof(char)*100);
														char *temp3 =  (char*)malloc(sizeof(char)*100);
														$$=mknode(">=",$1,$3,NULL,NULL);
														strcpy(temp1, freshVar());
														strcpy($$->var,temp1);
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,">");
														strcpy(temp2,freshVar());
														strcpy($$->var,temp2);
														basicOperationCode(&tmp,$1->code,$3->code,$$->var,$1->var,$3->var,"==");
														strcpy(temp3, freshVar());
														strcpy($$->var,temp3);
														basicOperationCode(&tmp,$1->code,$3->code,$$->var,temp1,temp2,"||");
														strcat($$->code,tmp);

													}
						| EXPR LESS EXPR			{

														$$=mknode("<",$1,$3,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"<");
													
													}
						| EXPR LESSEQ EXPR			{
														char *tmp = (char*)malloc(sizeof(char)*5000);
														char *temp1 =  (char*)malloc(sizeof(char)*100);
														char *temp2 =  (char*)malloc(sizeof(char)*100);
														char *temp3 =  (char*)malloc(sizeof(char)*100);
														$$=mknode("<=",$1,$3,NULL,NULL);
														strcpy(temp1, freshVar());
														strcpy($$->var,temp1);
														basicOperationCode(&($$->code),$1->code,$3->code,$$->var,$1->var,$3->var,"<");
														strcpy(temp2,freshVar());
														strcpy($$->var,temp2);
														basicOperationCode(&tmp,$1->code,$3->code,$$->var,$1->var,$3->var,"==");
														strcpy(temp3, freshVar());
														strcpy($$->var,temp3);
														basicOperationCode(&tmp,$1->code,$3->code,$$->var,temp1,temp2,"||");
														strcat($$->code,tmp);
													}

						| NOT EXPR					{
														$$=mknode("!",$2,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"",$2->code,$$->var,"!","",$2->var);
													}
						| MULT EXPR					{
														$$=mknode("*",$2,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"",$2->code,$$->var,"*","",$2->var);
													}
						| MINUS EXPR 				{
														$$=mknode("-",$2,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"",$2->code,$$->var,"-","",$2->var);
													}
						| BAND id					{
														$$=mknode("&",$2,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"",$2->code,$$->var,"&","",$2->var);
													}
						| NUMS						{
														$$=$1;
														$$->var=$1->token;
														$$->code=(char*)malloc(sizeof(char)+1);
													}
						| BOOL_TRUE					{
														$$=mknode("true",NULL,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"","",$$->var,"true","","");
													}
						| BOOL_FALSE				{
														$$=mknode("false",NULL,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"","",$$->var,"false","","");	
													}

						| ASSIGNMENT_VAR			{
														$$=$1;
														$$->var=$1->token;
													}
						| OBRACKET EXPR CBRACKET	{$$=$2;}
						| ABS EXPR ABS 				{
														$$=mknode("ABS",$2,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"",$2->code,$$->var,"|","|",$2->var);
													}
						| NNULL						{
														$$=mknode("NULL",NULL,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),"","",$$->var,"NULL","","");
													}
						| FUNC_CALL					{
														$$=mknode("FUNC CALL",$1,NULL,NULL,NULL);
														
														strcpy($$->code, $1->code);
														strcpy($$->var,$1->var);
														
													}
						| char						{
														$$=mknode("CHAR VAR",$1,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,"",$$->var,$1->var,"","");
													}
						| string_id					{
														$$=mknode("STRING VAR",$1,NULL,NULL,NULL);
														strcpy($$->var,freshVar());
														basicOperationCode(&($$->code),$1->code,"",$$->var,$1->var,"","");
													}
						;	
						
NUMS:					NUM				{$$=mknode(yytext,NULL,NULL,NULL,NULL);}	
						| HEX			{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| DEC   		{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						| REAL_NUMBER	{$$=mknode(yytext,NULL,NULL,NULL,NULL);}
						;
						
id:						ID 	{$$=mknode(yytext,NULL,NULL,NULL,NULL);
						strcpy($$->var, yytext);
}
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
				char *tmp;
				tmp=(char*)malloc(sizeof(char)*100);
				strcpy(tmp,yytext);
				//Remove last " from the string variable
				for(i=1;yytext[i]!='\0';i++){
					c=yytext[i];
					if(yytext[i]=='"')
						yytext[i]='\0';
					}
				$$=mknode(&yytext[1],NULL,NULL,NULL,NULL);
				$$->code=(char*)malloc(sizeof(char)+1);
				$$->var=tmp;
				}
				;

%%

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
