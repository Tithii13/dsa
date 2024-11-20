#include<stdio.h>
#include<stdlib.h>

struct node
{
int data;
struct node* next;
};

void insert(struct node* head,int ndata)
{
struct node* nn=(struct node*)malloc(sizeof(struct node));
nn->data=ndata;
nn->next=NULL;
struct node* temp=head;
while(temp->next!=NULL)
{
temp=temp->next;
}
temp->next=nn;
}

struct node* rev(struct node* head)
{
struct node* prev=NULL;
struct node* curr=head;
struct node* next=NULL;
while(curr!=NULL)
{
next=curr->next;
curr->next=prev;
prev=curr;
curr=next;
}
return prev;
}

int ispal(struct node* head)
{
if(head==NULL||head->next==NULL)
{
return 1;
}
struct node* slow=head;
struct node* fast=head;
while(fast!=NULL&&fast->next!=NULL)
{
slow=slow->next;
fast=fast->next->next;
}
struct node* sh=rev(slow);
struct node* fh=head;
while(sh!=NULL)
{
if(fh->data!=sh->data)
{
return 0;
}
fh=fh->next;
sh=sh->next;
}
return 1;
}

void printl(struct node* head)
{
struct node* temp=head;
while(temp!=NULL)
{
printf("%d ",temp->data);
temp=temp->next;
}
printf("\n");
}

int main()
{ 
struct node* head=(struct node*)malloc(sizeof(struct node));
head->next=NULL;
insert(head,1);
insert(head,2);
insert(head,1);

if(ispal(head->next))
{
printf("Yes\n");
}
else
{
printf("No\n");}

return 0;
}