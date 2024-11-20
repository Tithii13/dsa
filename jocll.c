#include<stdio.h>
#include<stdlib.h>

struct node
{
int data;
struct node* next;
};

struct node* ccl(int n)
{
struct node* head=NULL;
struct node* temp=NULL;
struct node* tail=NULL;

for(int i=1;i<=n;i++)
{
struct node* nn=(struct node*)malloc(sizeof(struct node));
nn->data=i;
nn->next=NULL;
if(head==NULL)
{
head=nn;
tail=nn;
}
else
{
tail->next=nn;
tail=nn;
}
}
if(tail!=NULL)
{
tail->next=head;
}
return head;
}

int josephus(struct node* head,int k)
{
struct node* curr=head;
struct node* prev=NULL;
while(curr!=NULL)
{
for(int c=1;c<k;c++)
{]
prev=curr;
curr=curr->next;
}
prev->next=curr->next;
printf("Eliminated: %d\n",curr->data);
free(curr);
curr=prev->next;
}
return curr->data;
}


int main()
{
int n=7;
int k=3;
struct node* head=cll(n);
int surv=josephus(head,k);
printf("Survivor: %d\n ",surv);
return 0;
}
