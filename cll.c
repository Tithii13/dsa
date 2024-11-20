#include<stdio.h>
#include<stdlib.h>

struct node
{
int data;
struct node* next;
};

struct node* createnode(int newdata)
{
    struct node* nn=(struct node*)malloc(sizeof(struct node));
    nn->data=newdata;
    nn->next=nn;
    return nn;
}

struct node* insertempty(struct node* last,int newdata)
{
    if(last!=NULL)
    {
        return last;
    }
    struct node* nn=createnode(newdata);
    last=nn;
    return last;
}
struct node* insertatbeg(struct node* last,int newdata)
{
    struct node* nn=createnode(newdata);
    if(last==NULL)
    {
        nn->next=nn;
        return nn;
    }
    nn->next=last->next;
    last->next=nn;
    return last;

}

struct node* insertatend(struct node* tail,int newdata)
{
    struct node* nn=createnode(newdata);
    if(tail==NULL)
    {
        tail=nn;
        nn->next=nn;
    }
    else{
        nn->next=tail->next;
        tail->next=nn;
        tail=nn;
    }
    return tail;
}

struct node* insertatposi(struct node* last,int data,int pos)
{
    int i;
    if(last==NULL)
    {
        if(pos!=1)
        {
            printf("INVALID POSITION \n");
            return last;
        }
        struct node* nn=createnode(data);
        last=nn;
        last->next=last;
        return last;
    }
    struct node* nn=createnode(data);
    struct node* curr=last->next;
    if(pos==1)
    {
        nn->next=curr;
        last->next=nn;
        return last;
    }
    for(i=1;i<pos-1;++i)
    {
        curr=curr->next;
        if(curr==last->next)
        {
            printf("INVALID POSITION \n");
            return last;
        }
    }
    nn->next=curr->next;
    curr->next=nn;
    if(curr==last)
    {
        last=nn;
        return last;
    }

}

/*void delfirst(struct node** head)
{
    struct node *prev=*head,*next=*head;
    if(*head==NULL)
    {
         printf("\nLIST IS EMPTY\n");
return;

    }
    if(prev->next==*head)
    {
        free(prev);
        *head=NULL;
    }
    else{

    
    while(prev->next!=*head)
    {
        prev=prev->next;
       // next=prev->next;
        
    }
   prev->next=(*head)->next;
    prev->next=next->next;
    *head=(*head)->next;
    free(next);
    return;
    }
   
}*/

struct node* delfirst(struct node* tail)
{
    if(tail==NULL)
    {
        return tail;
    }
    if(tail->next==tail)
    {
        free(tail);
        tail=NULL;
        return tail;
    }
    struct node* temp=tail->next;
    tail->next=temp->next;
    free(temp);
    temp=NULL;
    return tail;

}

void printlist(struct node* last)
{
    if(last==NULL)
    {
        return;
    }
    struct node* head=last->next;
    while(1)
    {
    printf("%d",head->data);
    head=head->next;
    if(head==last->next)
    {break;}
    printf("\n");
}
}

int main()
{
    struct node* last=NULL;
   

   /*  printf("\nGIVE THE ELEMENT TO BE INSERTED: ");
    scanf("%d",&n);
    */
    last=insertempty(last,1);
    printf("\nafter insertion: \n");
    printlist(last);

    /*
    printf("\nGIVE THE ELEMENT TO BE INSERTED: ");
    scanf("%d",&n);
*/
    last=insertatbeg(last,8);
    printf("\nafter insertion at beginning: \n");
    printlist(last);
 
 
    last=insertatend(last,2);
    printf("\nafter insertion at end: \n");
    printlist(last);


    last=insertatposi(last,-1,2);
    printf("\nafter insertion at specific position: \n");
    printlist(last);

    last=delfirst(last);
    printf("\nafter deleting first node \n");
    printlist(last);
    return 0;
}