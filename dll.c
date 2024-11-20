#include<stdio.h>
#include<stdlib.h>


struct node
{
int data;
struct node* next;
struct node* prev;
};

struct node* createnode(int newdata)
{
    struct node* nn=(struct node*)malloc(sizeof(struct node));
    nn->data=newdata;
    nn->prev=NULL;
    nn->next=NULL;
    return nn;
}

void forward(struct node* head)
{
    struct node* curr=head;
    while(curr!=NULL)
    {
        printf("%d",curr->data);
        curr=curr->next;
    }
    printf("\n");
}

void backward(struct node* tail)
{
    struct node* curr=tail;
    while(curr!=NULL)
    {
        printf("%d",curr->data);
        curr=curr->prev;
    }
printf("\n");
}

int findlength(struct node* head)
{
    int count=0;
    for(struct node* curr=head;curr!=NULL;curr=curr->next)
    {
        count++;
        
    }
    return count;
}


struct node* insertatbeg(struct node* head,int newdata)
{
struct node* nn=createnode(newdata);
nn->next=head;
if(head!=NULL)
{
  head->prev=nn;
}
return nn;
}

struct node* insertatend(struct node* head,int newdata)
{
    struct node* nn=createnode(newdata);
    struct node* curr=head;
    if(head==NULL)
    {
        head=nn;
    }
    else
    {
        while(curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=nn;
        nn->prev=curr;

    }
    return head;
}

struct node* insertatposition(struct node* head,int posi,int newdata)
{
    struct node* nn=createnode(newdata);
    if(posi==1)
    {
        nn->next=head;
        if(head!=NULL)
        {
            head->prev=nn;
        }
        head=nn;
        return head;
    }
    struct node* curr=head;
    int i;
    for(i=1;i<posi-1 && curr!=NULL;++i)
    {
        curr=curr->next;
    }
    if(curr==NULL)
    {
        printf("POSITION OUT OF BOUNDS: \n");
        free(nn);
        return head;
    }
    nn->prev=curr;
    nn->next=curr->next;
    curr->next=nn;
    if(nn->next!=NULL)
    {
        nn->next->prev=nn;
    
    }
    return head;

}

struct node* delhead(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    struct node* curr=head;
    head=head->next;
    if(head!=NULL)
    {
        head->prev=NULL;
    }
    free(curr);
    return head;

}

struct node* delend(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    if(head->next==NULL)
    {
        free(head);
        return NULL;
    }
    struct node* curr=head;
    while(curr->next!=NULL)
    {
        curr=curr->next;
    }
    curr->prev->next=NULL;
    free(curr);
    return head;
}

struct node* delatposi(struct node* head,int posi)
{
    int i;
    if(head==NULL)
    {
        return head;
    }
    struct node* curr=head;
    for(i=1;curr&&i<posi;++i)
    {
        curr=curr->next;
    }
    if(curr==NULL)
    {
        return head;
    }
    if(curr->prev)
    {
        curr->prev->next=curr->next;
    }
    if(curr->next)
    {
        curr->next->prev=curr->prev;
    }
    if(head==curr)
    {
        head=curr->next;
    }
    free(curr);
    return head;
}

int main()
{

    struct node* head=createnode(1);
    struct node* second=createnode(2);
    struct node* third=createnode(3);
   
    head->next=second;
    second->prev=head;
    second->next=third;
    third->prev=second;

    forward(head);
    backward(head);

    printf("Length of the list: %d \n",findlength(head));
    
    head=insertatbeg(head,0);
    printf("After inserting at the beginning:\n");
    forward(head);

    head=insertatend(head,4);
    printf("After inserting at the end:\n");
    forward(head);

 head=insertatposition(head,2,10);
    printf("After inserting in the middle:\n");
    forward(head);


head=delhead(head);
printf("After deleting head: \n");
forward(head);

head=delend(head);
printf("After deleting the endL \n");
forward(head);

head=delatposi(head,2);
printf("After deleting at teh specific position \n");
forward(head);

    return 0;
}