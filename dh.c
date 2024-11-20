#include<stdio.h>
#define MAX 10

int hasht[MAX]={0};
int hash(int key)
{
    return key%MAX;
}
int hash2(int key)
{
    return 7-(key%7);
}

void insert(int key)
{
    int index=hash(key);
    int steps=hash2(key);
    int i=0;
    while(hasht[index]!=0)
    {
        index=(index+steps)%MAX;
        i++;
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