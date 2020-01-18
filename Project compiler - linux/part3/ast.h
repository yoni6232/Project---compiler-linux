#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node{
	char *token;
	char *code;
	char *var;
	char *begin;
	char *next;
	int isArray;
	struct node *left;
	struct node *mid1;
	struct node *mid2;
	struct node *right;
	
} node;

node* mknode(char* token,node* left,node* mid1,node* mid2, node* right);
void Printtree(node* tree,int tab);
int isTerminal(node* tree);
int AllChildTerminal(node* tree);
void pre(node* tree,int tab);
void basicOperationCode(char **souceCode,char* code1,char* code2,char* souceVar,char* var1,char* var2,char* operation);


#endif