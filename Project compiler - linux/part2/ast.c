#include "ast.h"

node* mknode(char* token,node* left,node* mid1,node* mid2, node* right)
{
	node *newnode = (node*)malloc(sizeof(node));
   	char *newstr = (char*)malloc(sizeof(token)+1);
   	strcpy (newstr, token);
    newnode->token = newstr;
	newnode->left=left;
	newnode->mid1=mid1;
	newnode->mid2=mid2;
	newnode->right=right;
	return newnode;
}

int isTerminal(node* tree){
	
	if(tree){
		return (tree->left == NULL) && (tree->mid1 == NULL) && (tree->mid2 == NULL) && (tree->right == NULL);
	}
	return 1;
}

int AllChildTerminal(node* tree){
	if(tree->left){
		if(isTerminal(tree->left)){
			if(tree->mid1){
				if(isTerminal(tree->mid1)){
					if(tree->mid2){
						if(isTerminal(tree->mid2)){
							if(tree->right){
								return isTerminal(tree->right);
							}else{
								return 1;
							}
						}else{
							return 0;
						}
					}else{
						return 1;
					}
				}else{
					return 0;
				}
			}else{
				return 1;
			}
		}else{
			return 0;
		}
	}else{
		return 1;
	}
}
			

void Printtree(node* tree,int tab){
	
	if(isTerminal(tree)){
		printf(" %s",tree->token);
		return;
	}
	
	if(strcmp("FUNC_NODE",tree->token) && strcmp("STATMENT_NODE",tree->token)){
		
		for(int i=0;i<tab;i++)
			printf("    ");
		printf("(%s",tree->token);
		
	}
	else{
		tab--;
	}
	
	if(tree->left){
		if(!isTerminal(tree->left) )
			printf("\n");
		//printf("%s\t", tree->token);
		Printtree(tree->left,tab+1);	
	}
				
	if(tree->mid1){
		if(!isTerminal(tree->mid1))
			printf("\n");	
		Printtree(tree->mid1,tab+1);

	}
				
	if(tree->mid2 ){
		if(!isTerminal(tree->mid2))
			printf("\n");
		Printtree(tree->mid2,tab+1);

	}
				
	if(tree->right){
		if(!isTerminal(tree->right))
			printf("\n");
		Printtree(tree->right,tab+1);
	}
	
	if((strcmp("FUNC_NODE",tree->token) && strcmp("STATMENT_NODE",tree->token)) || AllChildTerminal(tree)){
		if(!isTerminal(tree->left) || !isTerminal(tree->mid1) || !isTerminal(tree->mid2) || !isTerminal(tree->right)){
			printf("\n");
			for(int i=0;i<tab;i++)
				printf("    ");
			printf(")");
		}else{
			printf(")\n");
			for(int i=0;i<tab;i++)
				printf("    ");
		}	
	}
	
	
}

void pre(node* tree,int tab){
	if(tree){
	printf("( %s\n",tree->token);
	if(tree->left){
		for(int i=0;i<tab;i++)
		printf("|    ");
		printf("A: ");
		pre(tree->left,tab+1);
	}
	if(tree->mid1){
		for(int i=0;i<tab;i++)
		printf("|    ");
		printf("B: ");
		pre(tree->mid1,tab+1);
	}
	if(tree->mid2){
		for(int i=0;i<tab;i++)
		printf("|    ");
		printf("C: ");
		pre(tree->mid2,tab+1);
	}
	if(tree->right){
		for(int i=0;i<tab;i++)
		printf("|    ");
		printf("D: ");
		pre(tree->right,tab+1);
	}
	}
	else
		return;

}
