#include<stdio.h>
#include<stdlib.h>

struct node
{
    float coef;
    int exp;
    struct node* next;
};

struct node* insert(struct node* n,int co,int exp)
{
    struct node* temp;
    struct node* newp=malloc(sizeof(struct node));
    newp->coef=co;
    newp->exp=exp;
    newp->next=NULL;

    if(n==NULL||exp>n->exp)
    {
        newp->next=n;
        n=newp;
    }
    else
    {
        temp=n;
        while(temp->next!=NULL&&temp->next->exp>exp)
        {
        temp=temp->next;
        temp->next=newp;
        }
    }
        return n;
    }

struct node* create(struct node* head)
{
    int n,i;
    float coef;
    int expo;
    printf("Enter the number of terms: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the coefficient for term %d :",i+1);
        scanf("%f",&coef);
        printf("Enter the exponent for term %d: ",i+1);
        scanf("%d",&expo);
        head=insert(head,coef,expo);
    }
    return head;
}

void print(struct node* head)
{
    if(head==NULL)
    {
    printf("NO polynomial\n");
    }
    else{
        struct node* temp=head;
        while(temp!=NULL)
        {
            printf("%f*x^%d ",temp->coef,temp->exp);
            temp=temp->next;
            if(temp!=NULL)
            {
                printf("+");
            }
        }
        printf("\n");
    }
}

