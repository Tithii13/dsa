#include<stdio.h>
#include<stdlib.h>

struct node
{
char data;
struct node* left;
struct node* right;
};

int countnodes=0;
int countleaf=0;

struct node* init(char n)
{
struct node* s=(struct node*)malloc(sizeof(struct node));
s->data=n;
s->left=NULL;
s->right=NULL;
return s;
}

struct node* insert()
{
char data;
printf("Enter the data (-)to stop: ");
scanf(" %c",&data);

if(data=='-')
{
return NULL;
}

struct node* n=init(data);
printf("Enter the left child of %c : \n",data);
n->left=insert();
printf("Enter the right child of %c : \n",data);
n->right=insert();
return n;
}

int countnode(struct node* s)
{
if(s==NULL)
{
return 0;
}
countnodes++;
countnode(s->left);
countnode(s->right);
return countnodes;
}

int countleafnode(struct node* s)
{
if(s==NULL)
{
return 0;
}
if(s->left==NULL&&s->right==NULL)
{
countleaf++;
}
countleafnode(s->left);
countleafnode(s->right);
return countleaf;
}

int height(struct node* s)
{
if(s==NULL)
{
return -1;
}
int leftheight=height(s->left);
int rightheight=height(s->right);
return (leftheight>rightheight?leftheight:rightheight)+1;
}

int heightofnode(struct node* s, char target)
{
if(s==NULL)
{
return -1;
}
if(s->data==target)
{
return height(s);
}
int leftheight=heightofnode(s->left,target);
if(leftheight!=-1)
{
return leftheight;
}
return heightofnode(s->right,target);
}

struct node* cet(char* postfix)
{
struct node* stack[100];
int top=-1;
for(int i=0;postfix[i]!='\0';i++)
{
if((postfix[i]>='a'&&postfix[i]<='z')||(postfix[i]>='A' &&postfix[i]<='Z'))
{
stack[++top]=init(postfix[i]);
} 
else
{
struct node* opnode=init(postfix[i]);
opnode->right=stack[top--];
opnode->left=stack[top--];
stack[++top]=opnode;
}
}
return stack[top];
}

void preorder(struct node* n)
{
if(n==NULL)
{
return;
}
printf("%c ",n->data);
preorder(n->left);
preorder(n->right);
}

int main()
{
char h;
struct node* n=insert();
preorder(n);
printf("\n");
printf("Number of nodes in the tree: %d \n",countnode(n));
printf("Number of leafnodes in the tree: %d \n",countleafnode(n));
printf("Enter the node you want the height: ");
scanf(" %c",&h);
printf("Height of the given node: %d",heightofnode(n,h));
char postfix[]="ab+cde+**";
struct node* exptree=cet(postfix);
preorder(exptree);
 
return 0;
}