#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node
{
int data;
struct node *next;
};


struct node* createnode(int newdata)
{
struct node* newnode=(struct node*)malloc(sizeof(struct node));
newnode->data=newdata;
newnode->next=NULL;
return newnode;
}


struct node* insertatfirst(struct node* head,int newdata)
{
    struct node* nn=createnode(newdata);
    nn->next=head;
    printf("INSERTED\n");
    return nn;
}

struct node* insertatend(struct node* head,int newdata)
{
    struct node* nn=createnode(newdata);
    if(head==NULL)
    {
        return nn;
    }
    struct node* last=head;
    while(last->next!=NULL)
    {
        last=last->next;
    }
    last->next=nn;
    return head;

}

struct node* insertafter(struct node* head,int key,int newdata)
{
struct node* curr=head;
while(curr!=NULL)
{
    if(curr->data==key)
    {
        break;
        
    }
    curr=curr->next;
}
    if(curr==NULL)
    {
        return head;
    }
    struct node* nn=createnode(newdata);
    nn->next=curr->next;
    curr->next=nn;
    return head;
}


struct node* insertatposition(struct node* head,int position,int newdata)
{
    struct node* nn=createnode(newdata);
    int i;
    if(position==1)
    {
        nn->next=head;
        head=nn;
        return head;
    }

    struct node* curr=head;
    for(i=1;i<position-1&&curr!=NULL;++i)
    {
        curr=curr->next;
    }
    if(curr==NULL)
    {
        printf("Position out of bound! \n");
        free(nn);
        return head;
    }
    nn->next=curr->next;
    curr->next=nn;
    return head;
}

void printlist(struct node* head)
{
    while(head!=NULL)
    {
        printf("%d\n",head->data);
        head=head->next;
    }

}


struct node* delhead(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }

  struct node* temp=head;
  head=head->next;
  free(temp);
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
    struct node* seclast=head;
    while(seclast->next->next!=NULL)
    {
        seclast=seclast->next;
    }
    free(seclast->next);
    seclast->next=NULL;

    return head;
}


struct node* delnode(struct node* head,int position)
{
    struct node* prev;
    struct node* temp=head;
    int i;

if(temp==NULL)
{
    return head;
}
if(position==1)
{
    head=temp->next;
    free(temp);
    return head;
}
for(i=1;temp!=NULL&&i<position;i++)
{
    prev=temp;
    temp=temp->next;
}
if(temp!=NULL)
{
 prev->next=temp->next;
 free(temp);
}
else
{
    printf("Data not found \n");
}
return head;
}

bool searchkey(struct node* head,int key)
{
if(head==NULL)
{
return 0;
}
if(head->data==key)
{
    return 1;
}
return searchkey(head->next,key);
}


struct node* sortlist(struct node* head)
{
    struct node* current=head;
    struct node* index=NULL;
    int temp;

    printf("Sort current %d\n",current->data);
    if(head==NULL)
    {
        return NULL;

    }
    else{
        while(current!=NULL)
        {
            index=current->next;
            //printf("Sort current %d\n",current->data);
            while(index!=NULL)
            { 
                //printf("Sort index %d\n",index->data);
                if(current->data > index->data)
                {
                temp=current->data;
                current->data=index->data;
                index->data=temp;
                
                }
                index=index->next;
                
            }
            current=current->next;
            
        }
    }
    return head;

}
int main()

{
     struct node* head=createnode(2);
     head->next=createnode(3);
     head->next->next=createnode(4);
     head->next->next->next=createnode(5);

     printf("Linked List: \n");
     printlist(head);

     printf("INSERTION AT FIRST: \n");
     int data=1;
     head=insertatfirst(head,data);

     printf("After insertion: \n");
     printlist(head);

 printf("INSERT AT END :\n");
 int data2=6;
 head=insertatend(head,data2);

 printf("After inserting at end: \n");
 printlist(head);

 int key,data3;
 key=4;
 data3=33;

 head=insertafter(head,key,data3);
 printf("After inserting after 4 : \n");
 printlist(head);

 int data4=22;
 int posi=2;
 head=insertatposition(head,key,data4);
printf("After insertion after the 2nd position: \n");
printlist(head);

head=delhead(head);
printf("Deletion of 1st Node : \n");
printlist(head);

head=delend(head);
printf("Deleting end: \n");
printlist(head);

int po=2;
head=delnode(head,po);
printf("Deletion at 2nd: \n");
printlist(head);

int k=33;
if(searchkey(head,k))
{
   printf("33 FOUND\n");
}
else{
printf("33 NOT FOUND\n");

}

printf("Before SORTED LIST \n");
printlist(head);
printf("After SORTED LIST \n");
head=sortlist(head);
printf("SORTED LIST \n");
printlist(head);

return 0;
}