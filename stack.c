#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define size 10

struct stack
{
    int top;
    int *s;
}s1;

void ini()
{
s1.s=malloc(size *sizeof(int));
s1.top=-1;
}

bool isEmpty()
{
    if(s1.top==-1)
    {
       return true;
    }
    else
    {
        return false;
    }
}


bool isFull()
{
    if(s1.top==size-1)
    {
        return true;
    }
    else{
        return false;
    }
}



void push(int b)
{
if(isFull())
{
    printf("STACK IS FULL \n");
}
else
{
s1.top=s1.top+1;
s1.s[s1.top]=b;
}
}


int pop()
{  
    int a;
    if(isEmpty())
    {
        printf("STACK IS EMPTY \n");
    }
    else
    {
    a=s1.s[s1.top];
    s1.top--;
    return a;
    }
}

void peek()
{
    if(isEmpty())
    {
      printf("STACK IS EMPTY \n");  
    }
    else
    {
    printf("THE TOPMOST ELEMENT IN THE STACK IS: %d \n",s1.s[s1.top]);
    }
}


void display()
{
    int i,a;
    if(isEmpty())
    {
        printf("STACK IS EMPTY \n");
    }
    else{

      for(i=s1.top;i>=0;i--)
    {
        
        printf("Element : %d",s1.s[i]);
    }
}
}


void main()
{
int menu,c;
ini();

while(1)
{ 
    printf("\n------------------------------------\n");
    printf("PRESS 1 TO PUSH \n");
    printf("PRESS 2 TO POP \n");
    printf("PRESS 3 TO PEEK \n");
    printf("PRESS 4 TO CHECK IF STACK IS EMPTY \n");
    printf("PRESS 5 TO CHECK IF STACK IS FULL \n");
    printf("PRESS 6 TO DISPLAY STACK \n");
    printf("PRESS 7 TO EXIT \n");
    printf("\n------------------------------------\n");
    
    printf("ENTER YOUR CHOICE: ");
    scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        printf("ENTER THE ELEMENT TO BE PUSHED: ");
        scanf("%d",&c);
        push(c);
        printf("PUSHED SUCCESSFULLY\n");
        break;

        case 2:
        printf("ELEMENT POPPED : %d",pop());
        break;

        case 3:
        peek();
        break;

        case 4:
        if(isEmpty())
        {
            printf("STACK IS EMPTY \n");
        }
        else
        {
            printf("STACK IS NOT EMPTY \n");
        }
        break;

        case 5:
        if(isFull())
        {
            printf("STACK IS FULL \n");
        }
        else
        {
            printf("STACK IS NOT FULL\n");
        }
        break;
        
        case 6:
        display();
        break;

        case 7:
        exit(0);
        break;

        default:
        printf("ENTER VALID NUMBER!!\n");
        break;

    }

}

}