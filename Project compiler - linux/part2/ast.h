#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node{
	char *token;
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

#endif