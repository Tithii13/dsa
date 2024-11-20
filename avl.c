#include<stdio.h>
#include<stdlib.h>

struct node
{
int data;
struct node* left;
struct node* right;
int height;
};

int height(struct node* s)
{
if(s==NULL)
{
return 0;
}
return s->height;
}

int maxi(int a,int b)
{
return (a>b)?a:b;
}

struct node* newnode(int data)
{
struct node* n=(struct node*)malloc(sizeof(struct node));
n->data=data;
n->left=NULL;
n->right=NULL;
n->height=1;
return n;
}

struct node* rightrotate(struct node* s)
{
struct node* x=s->left;
struct node* y=x->right;
x->right=s;
s->left=y;
s->height=maxi(height(s->left),height(s->right))+1;
x->height=maxi(height(x->left),height(x->right))+1;
return x;
}

struct node* leftrotate(struct node* s)
{
struct node* x=s->right;
struct node* y=x->left;
x->left=s;
s->right=y;
s->height=maxi(height(s->left),height(s->right));
x->height=maxi(height(x->left),height(x->right));
return x;
}

int getbalance(struct node* s)
{
if(s==NULL)
{
return 0;
}
return height(s->left)-height(s->right);
}

struct node* insert(struct node* s, int data)
{
if(s==NULL)
{
printf("Inserted node: %d\n ",data);
return newnode(data);
}
if(data<s->data)
{
s->left=insert(s->left,data);
}
else if(data>s->data)
{
s->right=insert(s->right,data);
}
s->height=maxi(height(s->left),height(s->right))+1;
int b=getbalance(s);

printf("Node: %d, Balance Factor: %d\n",s->data,b);

if(b>1&&data<s->left->data)
{
printf("Unbalanced at %d : Left Left Case: Performing Right Rotation\n",s->data);
return rightrotate(s);
}

if(b>1&&data>s->left->data)
{
printf("Unbalanced at %d : Left Right Case: Performing Left Rotation on Left Child and Right Rotation\n",s->data);
s->left=leftrotate(s);
return rightrotate(s);
}

if(b<-1&&data>s->right->data)
{
printf("Unbalanced at %d : Right Right Case: Performing Left Rotation\n",s->data);
return leftrotate(s);
}

if(b<-1&&data<s->right->data)
{
printf("Unbalanced at %d :Right Left Case: Performing Right Rotation on Right Child and Left Rotation\n",s->data);
s->right=leftrotate(s);
return leftrotate(s);
}
return s;
}

void preorder(struct node* s)
{
if(s==NULL)
{
return;
}
printf("%d ",s->data);
preorder(s->left);
preorder(s->right);
}

int main()
{
struct node* root=NULL;
root=insert(root,30);
root=insert(root,40);
root=insert(root,50);
root=insert(root,25);
root=insert(root,35);
root=insert(root,45);
root=insert(root,42);
root=insert(root,47);
preorder(root);
return 0;
}