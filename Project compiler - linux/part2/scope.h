#ifndef SCOPE
#define SCOPE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"



typedef struct var{
    char* type;
    char* id;
    struct var* next;
} var;

typedef struct scope{
    char* scope_id;
    struct scope* next;
    struct scope* upperScope;
    struct scope* innerScope;
    struct var *vars;
    int isFunction; //function or not function
    char* return_type; //if a function, what it should to return
    struct var* params; //if a function, what are the params
} scope;
char* getExprType(node tree,scope scp);
void scanTree(node* tree,scope** scope);

scope* initGlobalScope();

void printParamsOrVars(scope* scope,int choose,int tab);

scope* initScope(char* scope_name,int isFunction, char* type);

void printSymbolTable(scope* global,int tab);

int idType(char* id);

void getVarArry(node *tree,int type,var** array,char* typeID, var* firstVar, scope scp,node *treetmp);


var* getLastVar(var *array);

scope* getLastScope(scope *scp);

void printError(char* error);

int checkBrotherExist(scope* start,char* scopeName);

void checkMainOnce();

void CheckStatement(node tree,scope scp);

char* getVarType(scope scp,char* var);

char* getFuncType(scope scp,char* func);

char* getExprType(node tree,scope scp);

int isNumber(char* string);

char* getMyFuncReturn(scope scp);

void checkFunctionCall(node tree,scope scp,var* params,int s);


var* getFuncParams(scope scp,char* func);
#endif

