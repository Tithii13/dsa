#include<stdio.h>
#define MAX 10


int hasht[MAX]={0};

int hash(int key)
{
    return key%MAX;
}

void insert(int key)
{
    int index=hash(key);
    
    while(hasht[index]!=0)
    {
        index=(index+1)%MAX;
    }
    hasht[index]=key;
}

void display()
{
    for(int i=0;i<MAX;i++)
    {
        printf("%d ",hasht[i]);
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
