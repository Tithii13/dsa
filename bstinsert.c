#include<stdio.h>
#include<stdlib.h>

struct node
{
int data;
struct node* left;
struct node* right;
};

struct node* init(int n)
{
struct node* s=(struct node*)malloc(sizeof(struct node));
s->data=n;
s->left=NULL;
s->right=NULL;
return s;
}

struct node* insert(struct node* s ,int n)
{
if(s==NULL)
{
return init(n);
}
if(s->data<n)
{
s->right=insert(s->right,n);
//printf("Inserted %d at the right of %d.\n",n,s->data);
}
if(s->data>n)
{
s->left=insert(s->left,n);
//printf("Inserted %d at the left of %d.\n",n,s->data);
}
return s;
}

int findmin(struct node* s)
{
while(s&&s->left!=NULL)
{
s=s->left;
}
return s->data;
}

int findmax(struct node* s)
{
while(s&&s->right!=NULL)
{
s=s->right;
}
return s->data;
}

struct node* findsucc(struct node* s, int data)
{
struct node* succ=NULL;	
while(s!=NULL)
{
if(data<s->data)
{
succ=s;
s=s->left;
}
else if(data>s->data)
{
s=s->right;
}
else
{
if(s->right)
{
succ=s->right;
while(succ->left!=NULL)
{
succ=succ->left;
}
}
break;
}
}
return succ;
}

struct node* finpred(struct node* s,int data)
{
struct node* pred=NULL;
while(s!=NULL)
{
if(data>s->data)
{
pred=s;
s=s->right;
}
else if(data<s->data)
{
s=s->left;
}
else
{
if(s->left)
{
pred=s;
while(pred->right!=NULL)
{
pred=pred->right;
}
}
break;
}
}
return pred;
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

void inorder(struct node* s)
{
if(s==NULL)
{
return;
}
inorder(s->left);
printf("%d ",s->data);
inorder(s->right);

}

int main()
{
struct node* root=NULL;
int input,succprec;
printf("Enter the data and give -1 to stop: \n");
while(1)
{
printf("Enter the data in the BST: ");
scanf("%d",&input);
if(input==-1)
{
break;
}
root=insert(root,input);
}
preorder(root);
inorder(root);
printf("\n");
printf("Minimum in the tree : %d \n",findmin(root));
printf("Maximum in the tree : %d\n",findmax(root));

printf("Enter the node you want to check its successor and predecessor: ");
scanf("%d",&succprec);

struct node* suc=findsucc(root,succprec);
if(suc!=NULL)
{
printf("Successor of %d is %d \n",succprec,suc->data);
}
else
{
printf("No successor");
}

struct node* pred=finpred(root,succprec);
if(pred!=NULL)
{
printf("Predecessor of %d is %d \n",succprec,pred->data);
}
else
{
printf("No predecessor");
}
return 0;
}
