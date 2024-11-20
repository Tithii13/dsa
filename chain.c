#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* next;
};

struct node* hasht[10];
int hash(int key)
{
    return key%10;
}
void insert(int key)
{
    int index=hash(key);
    struct node* nn=(struct node*)malloc(sizeof(struct node));
    nn->data=key;
    nn->next=NULL;
    
    if(hasht[index]==NULL)
    {
        hasht[index]=nn;
    }
    else{
        struct node* temp=hasht[index];
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=nn;
    }

}

void display()
{
    for(int i=0;i<10;i++)
    {
        struct node* temp=hasht[i];
        printf("INDEX: %d ",i);
        while(temp)
        {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    insert(12);
    insert(22);
    insert(32);
    insert(42);
    
    display();
    return 0;

}