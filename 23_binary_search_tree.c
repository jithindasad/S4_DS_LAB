#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// bst, all functns exact translation of algos 
//  as in cormen(CLRS Text), as anish sir took.
// root is given as global variable , 
// so that is not passed to insert,delete or search 
struct node 
{
	int data;
	struct node *left,*right,*parent;
}*root;

void inorder(struct node *x);
void preorder(struct node *x);
void postorder(struct node *x);

struct node* search(int k);
struct node* minimum(struct node *x);
void insert(struct node *z);
void transplant(struct node *u,struct node *v);
void delete(struct node *z);

int main()
{
	int option=0,temp1,temp2;
	while(option!= 7)
	{
		printf(" Enter option \n 1. Insert \n 2. Search \n 3. Delete \n 4. Inorder  \n 5. Preorder \n 6. postorder\n 7. Exit\n");
		scanf("%d",&option);
		if(option==1)
		{
			printf(" enter elemtn : ");
			scanf("%d",&temp1);
			struct node *new = (struct node *) malloc(sizeof(struct node));
			new -> data=temp1;
			insert(new);
		}
		else if(option==2)
		{
			printf(" enter element to search : ");
			scanf("%d",&temp1);
			struct node *temp= search(temp1);
			if(temp==NULL)
				printf(" element not found \n");
			else
				printf(" element found \n");
		}
		else if(option==3)
		{
			printf(" enter element to delete : ");
			scanf("%d",&temp1);
			struct node *temp= search(temp1);
			if(temp==NULL)
				printf(" element not found \n");
			else
			{
				delete(temp);
				printf(" element deleted \n");
			}	
		}
		else if(option==4)
			inorder(root);
		else if(option==5)
			preorder(root);
		else if(option==6)
			postorder(root);
		else if(option == 7)
			break;
		else
			printf(" invalid option");
		printf("\n");
		
		
	}
	
	
}

void inorder(struct node *x)
{
	if(x!=NULL)
	{
		inorder( x-> left);
		printf("%d ",x -> data);
		inorder(x -> right);
	}
}
void postorder(struct node *x)
{
	if(x!=NULL)
	{
		postorder( x-> left);
		postorder(x -> right);
		printf("%d ",x -> data);
	}
}
void preorder(struct node *x)
{
	if(x!=NULL)
	{
		printf("%d ",x -> data);
		preorder( x-> left);
		preorder(x -> right);
	}
}


struct node* search(int k)
{
	struct node *x=root; 
	while( x!= NULL && k!= x -> data)
	{
		if(k < x-> data)
			x= x-> left;
		else 
			x= x-> right;		
	}
	return x;
}
void insert(struct node *z)
{
	struct node *y=NULL;
	struct node *x=root;
	while(x != NULL )
	{
		y=x;
		if((z -> data) < (x -> data) )
			x= x -> left;
		else
			x= x -> right;
	}
	z -> parent = y;
	if ( y == NULL)
		root=z;
	else if( z -> data < y -> data)
		y -> left =z;
	else
		y -> right =z;
}
struct node *minimum(struct node *x)
{
	while(x -> left != NULL)
		x= x -> left;
	return x;
}
void transplant(struct node *u,struct node *v)
{
	if(u -> parent == NULL)
		root = v;
	else if(u == u->parent->left )
		u -> parent  -> left = v;
	else
		u -> parent -> right = v;
	if( v != NULL)
		v -> parent = u -> parent;
}
void delete(struct node *z)
{
	if( z -> left == NULL )
		transplant(z,z->right);
	else if(z-> right == NULL)
		transplant(z,z-> left);
	else
	{
		struct node *y = minimum(z -> right);
		if( y -> parent != z)
		{
			transplant(y, y->right);
			y -> right = z-> right;
			y -> right -> parent =y;
		}
		transplant(z,y);
		y-> left= z->left;
		y->left->parent =y;
		
	}

}

