%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
	char *token; 
	struct node *left;
	struct node *right;
} node;
node *makeNode(char *token, node *left, node *right);
void printTree(node *tree, int tab);
void printTabs(int numOfTabs);
int yyerror(char *err);
%}

%union
{
    char *string;
    struct node *node;
}
                        /*values*/
%token <string> ID FUNC TRUE_VAL FALSE_VAL
%token <string> DECIMAL_INT_NUMBER HEX_INT_NUMBER REAL_NUMBER CHAR_VAL STRING_VAL
                       /*types*/
%token <string> CHAR INT REAL STRING INTP CHARP REALP VOID BOOL VAR 

                        /*STATEMENT*/
%token <string> ELSE IF PLUS MINUS MULT DIV WHILE DO FOR RETURN NONE NOT
%token <string> OP_EQ OP_OR OP_AND OP_GT OP_GE OP_LE OP_LT ASSIGN OP_NOT_EQ ADDRESS DER_ID

%type <string> type func_type premitiveValue unaryOp
%type <node> s initial code function procedure args_Id args body Update declaration stmt stringType math_expr string_Id addressOf bodyproc
%type <node> expr elementOfExpr assignment multiAssign funcarguments ifStmt Block nestedStmt forStmt whileStmt returnStmt doStmt longdeclaration
%type <node> Procstmt ProcifStmt ProcwhileStmt funcstmt ProcdoStmt ProcforStmt Blockproc ProcnestedStmt

%right UNARY
%left OP_OR
%left OP_AND
%left OP_EQ
%left OP_GT OP_GE OP_LE OP_LT
%left PLUS MINUS
%left MULT DIV
%left OP_NOT_EQ
%%

s: initial {
        printTree($1,0);
    };
initial    :   code { $$ = makeNode("CODE", $1, NULL); };

code:       function code{ $$ = makeNode("FUNCTION",$1, $2); }
    |       function { $$ = makeNode("FUNCTION",$1, NULL); }
    |       procedure code{ $$ = makeNode("FUNCTION",$1, $2); }
    |       procedure { $$ = makeNode("FUNCTION",$1, NULL); };

/*_____________ procedure / function ________________*/

function   :   FUNC func_type ID '(' args ')' '{' body  '}' {$$ = makeNode($3,NULL, makeNode("ARGS", $5,makeNode($2, NULL,$8))); };

procedure  :   FUNC VOID ID '(' args ')' '{' bodyproc '}' {$$ = makeNode($3,NULL, makeNode("ARGS", $5,makeNode("TYPE VOID", NULL,$8))); };


args       :   type args_Id args  { $$ = makeNode($1, $2, $3); }
           |   stringType args_Id args {$1 ->left->right = $2; $1->right =$3; $$=$1;}
           |   { $$ = NULL; };


args_Id    :   ID { $$ = makeNode($1, NULL, NULL); } 
           |   ID ';' { $$ = makeNode($1, NULL,NULL); }
           |   ID ',' args_Id { $$ = makeNode($1, NULL, $3); }
           |   { $$ = NULL; };

string_Id  :   ID '[' math_expr ']' { $$ = makeNode($1, makeNode("[]", NULL,$3), NULL); }
           |   assignment ';'{ $$ = $1; }
           |   ID '[' math_expr ']' ',' string_Id { $$ = makeNode($1, makeNode("[]", NULL,$3), $6); }
           |   ID '[' math_expr ']' ';' {$$ = makeNode($1, makeNode("[]", NULL,$3), NULL); };


  
type       :   BOOL { $$ = "BOOL"; }
           |   CHAR { $$ = "CHAR"; } 
		       |   INT { $$ = "INT"; }
		       |   REAL { $$ = "REAL"; }
		       |   INTP { $$ = "INT_PTR"; }
		       |   CHARP { $$ = "CHAR_PTR"; }
	         |   REALP { $$ = "REAL_PTR"; };


func_type  :   BOOL { $$ = "TYPE BOOL"; }
		       |   CHAR { $$ = "TYPE CHAR"; } 
		       |   INT { $$ = "TYPE INT"; }
	         |   REAL { $$ = "TYPE REAL"; }
	         |   INTP { $$ = "TYPE INT_PTR"; }
		       |   CHARP { $$ = "TYPE CHAR_PTR"; }
		       |   REALP { $$ = "TYPE REAL_PTR"; }
		       |   STRING {$$ = "TYPE STRING";};

stringType :   STRING string_Id { $$ =$2; };

body       :   declaration nestedStmt returnStmt { $$ = makeNode("BODY", makeNode("", $1, $2),$3); }
           |   declaration returnStmt {$$ = makeNode("BODY",$1, $2); }
           |   nestedStmt returnStmt { $$ = makeNode("BODY", $1 ,$2); };

bodyproc   :   declaration ProcnestedStmt { $$ = makeNode("BODY", makeNode("", $1, $2),NULL); }
           |   declaration {$$ = makeNode("BODY",$1, NULL); }
           |   ProcnestedStmt { $$ = makeNode("BODY", $1 ,NULL); };


declaration:   function declaration { $$ = makeNode("FUNCTION", $1, $2); }
           |   stringType declaration {$$ = makeNode("STRING",$1,$2);}
           |   VAR type longdeclaration ';' declaration { $$ = makeNode($2,$3,$5);}
           |   { $$ = NULL; };

longdeclaration : assignment ',' longdeclaration {$1->right=$3;$$=$1;}
                | ID ',' longdeclaration {$$ = makeNode($1,NULL,$3);}
                | assignment  {$$=$1;}
                | ID  { $$ = makeNode($1, NULL, NULL); } 
                |   { $$ = NULL; };


nestedStmt :   stmt { $$ = $1; }
           |   stmt nestedStmt { $1->right = $2; $$ = $1; };

ProcnestedStmt :   Procstmt { $$ = $1; }
               |   Procstmt ProcnestedStmt { $1->right = $2; $$ = $1; };

Procstmt   :   assignment ';' {$$ = $1;}
           |   funcstmt {$$=$1;}
           |   ProcifStmt {$$=$1;}
           |   ProcwhileStmt { $$ = $1;}
           |   ProcdoStmt { $$ = $1;}
           |   Blockproc {$$ = $1;}
           |   ProcforStmt {$$ = $1;};

stmt       :   assignment ';' {$$ = $1;}
           |   funcstmt {$$=$1;}
           |   ifStmt {$$=$1;}
           |   whileStmt { $$ = $1;}
           |   doStmt { $$ = $1;}
           |   Block {$$ = $1;}
           |   forStmt {$$ = $1;};

funcstmt   :   ID ASSIGN ID '(' funcarguments ')' ';' { $$ = makeNode($2,makeNode($1,NULL,makeNode($3,$5,NULL)),NULL); }
           |   ID '(' funcarguments ')' ';' {$$ = makeNode($1,$3,NULL);};

funcarguments   :   { $$ = NULL; }
                |  math_expr ',' funcarguments {$1->right=$3;$$=$1;}
                |  math_expr{ $$ = $1; } ;


assignment :   ID ASSIGN math_expr { $$ = makeNode($2,makeNode($1,NULL, $3), NULL);}
           |   ID ASSIGN expr { $$ = makeNode($2,makeNode($1,NULL, $3), NULL);}
           |  ADDRESS ID ASSIGN expr { $$ = makeNode($1,makeNode($3,makeNode($2,NULL, $4), NULL), NULL);}
           |   ID ASSIGN STRING_VAL {$$ = makeNode($2, makeNode($1, makeNode($3,NULL, NULL), NULL), NULL);}
           |   ID '[' math_expr ']' ASSIGN STRING_VAL {$$ = makeNode($5, makeNode($1, makeNode("[]",NULL,$3),NULL),makeNode($6,NULL,NULL));}
           |   ID '[' math_expr ']' ASSIGN CHAR_VAL {$$ = makeNode($5, makeNode($1, makeNode("[]",NULL,$3),NULL),makeNode($6,NULL,NULL));}
           |   ID '[' math_expr ']' ASSIGN ID {$$ = makeNode($5, makeNode($1, makeNode("[]",NULL,$3),NULL),makeNode($6,NULL,NULL));};


multiAssign:   assignment { $$ = $1; }
           |   assignment ',' multiAssign { $$ = makeNode("", $1, $3); }
           |   { $$ = NULL; };


ifStmt         :   IF '(' expr ')' stmt { $$ = makeNode("IF",$3,$5);}
               |   IF '(' expr ')' stmt ELSE stmt { $$ = makeNode("IF-ELSE", makeNode("", $3, makeNode("", $5,$7)), NULL); };

ProcifStmt     :   IF '(' expr ')' Procstmt { $$ = makeNode("IF",$3,$5);}
               |   IF '(' expr ')' Procstmt ELSE Procstmt { $$ = makeNode("IF-ELSE", makeNode("", $3, makeNode("", $5,$7)), NULL); };

whileStmt      :  WHILE '(' expr ')' stmt { $$ = makeNode($1, $3, $5); };

ProcwhileStmt  :   WHILE '(' expr ')' Procstmt { $$ = makeNode($1, $3, $5); };

doStmt         :   DO Block WHILE '(' expr ')' { $$ = makeNode($1, makeNode("", $2,NULL), makeNode($3, $5, NULL)); };

ProcdoStmt     :   DO Blockproc WHILE '(' expr ')' { $$ = makeNode($1, makeNode("", $2,NULL), makeNode($3, $5, NULL)); };

forStmt        :   FOR '(' assignment ';' expr ';' Update ')' stmt { $$ = makeNode($1, makeNode("INITS", $3, makeNode("EXPR", $5, makeNode("UPDATE", $7, $9))), NULL); };

ProcforStmt    :   FOR '(' assignment ';' expr ';' Update ')' Procstmt { $$ = makeNode($1, makeNode("INITS", $3, makeNode("EXPR", $5, makeNode("UPDATE", $7, $9))), NULL); };

Block          :   '{' '}' {$$ = makeNode("BLOCK",NULL, NULL);}
               |   '{' declaration nestedStmt returnStmt '}' { $$ = makeNode("BLOCK", makeNode("", $2, $3),$4); };
               |   '{' declaration returnStmt '}' { $$ = makeNode("BLOCK", $2, $3); };
               |   '{' nestedStmt returnStmt '}' { $$ = makeNode("BLOCK", $2, $3); };
               |   '{' declaration ProcnestedStmt '}' { $$ = makeNode("BLOCK", makeNode("", $2, $3),NULL);}
               |   '{' declaration '}' {$$ = makeNode("BLOCK",$2, NULL); }
                |  '{' ProcnestedStmt '}' { $$ = makeNode("BLOCK", $2 ,NULL); };
               


Blockproc      :   '{' '}' {$$ = makeNode("BLOCK",NULL, NULL);}
               |   '{' declaration ProcnestedStmt '}' { $$ = makeNode("BLOCK", makeNode("", $2, $3),NULL);}
               |   '{' declaration '}' {$$ = makeNode("BLOCK",$2, NULL); }
           |  '{' ProcnestedStmt '}' { $$ = makeNode("BLOCK", $2 ,NULL); };

math_expr  :   elementOfExpr { $$ = $1;}  
           |   math_expr PLUS math_expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);}
           |   math_expr MINUS math_expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |   math_expr MULT math_expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |   math_expr DIV math_expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);};

expr       :   elementOfExpr {$$ = $1;}
           |   '(' expr ')' {$$ = makeNode("",$2, NULL);}
		       |   expr OP_EQ expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |  MULT '(' expr ')' {$$ = makeNode("*",$3, NULL);}
		       |   expr OP_AND expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
		       |   expr OP_OR expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
		       |   expr OP_GT expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
		       |   expr OP_GE expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
		       |   expr OP_LE expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
		       |   expr OP_LT expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |   expr OP_NOT_EQ expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |   expr PLUS expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);}
           |   expr MINUS expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |   expr MULT expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);} 
           |   unaryOp expr %prec UNARY { $$ = makeNode($1, $2, NULL); }
           |   expr DIV expr {$1->right = $3; $$ = makeNode($2, $1 ,NULL);}
           |   addressOf { $$ = $1; };


elementOfExpr  :   premitiveValue {$$ = makeNode($1,NULL, NULL); }
               |   '|' ID '|' { $$ = makeNode("STR_LEN", makeNode($2, NULL, NULL), NULL); };


premitiveValue :   CHAR_VAL { $$ = $1; }
               |   HEX_INT_NUMBER  { $$ = $1; }
               |   DECIMAL_INT_NUMBER  {$$ = $1; }
               |   REAL_NUMBER { $$ = $1; }
               |   ID { $$ = $1; }
               |   TRUE_VAL { $$ = $1;}
               |   NONE { $$ = $1; }
               |   DER_ID { $$ = $1; }
               |   FALSE_VAL { $$ = $1;};

addressOf      :   ADDRESS ID { $$ = makeNode($1, makeNode($2, NULL, NULL), NULL); }
               |   ADDRESS ID '[' expr ']' { $$ = makeNode($1, makeNode($2, makeNode("[]", $4, NULL), NULL), NULL); };

returnStmt     :   RETURN math_expr ';' { $$ = makeNode("RET", $2, NULL); } ;

Update         :   ID PLUS PLUS { $$ = makeNode("++", makeNode($1, NULL, NULL), NULL); }
               |   ID MINUS MINUS { $$ = makeNode("--", makeNode($1, NULL, NULL), NULL); }
               |   multiAssign { $$ = $1; };

unaryOp         :   PLUS { $$ = $1; }
                |   MINUS { $$ = $1; }
                |   NOT {$$ = $1;};

%%
#include "lex.yy.c"
int main()
{
    return yyparse();
}
node *makeNode(char *token, node *left, node *right) {
    node *newnode = (node*)malloc(sizeof(node));
    char *newstr = (char*)malloc(sizeof(token) + 1);
    strcpy(newstr, token);
    newnode->left = left;
    newnode->right = right;
    newnode->token = newstr;
    return newnode;
}

void printTree (node *tree, int tab){
    int nextTab = tab;
    if (strlen(tree->token) > 0) {
        printTabs(tab);
        printf ("(%s", tree->token);
        if (tree->left != NULL) {
            printf("\n");
        }
    }
    if (tree->left) {
        if (strlen(tree->token) == 0) {
            nextTab = tab - 1;
        }
        printTree(tree->left, nextTab + 1);
        if (strlen(tree->token) > 0) {
            printTabs(tab);
        }
    }
    if (strlen(tree->token) > 0) {
        printf (")\n");
    }
    if (tree->right) {
        printTree (tree->right, tab);
    }
}

void printTabs(int numOfTabs) {
    int i;
    for (i = 0; i < numOfTabs; i++) {
        printf ("\t");
    }
}

int yyerror(char *err) {
  int yydebug = 1;
  fflush(stdout);
  fprintf(stderr, "Error: %s at line %d\n", err, yylineno);
  fprintf(stderr, "does not accept '%s'\n", yytext);
  return 0;
}