#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
typedef struct Stack
{
    int top;
    int size;
    char* array;
}Stack;

Stack* stack;

 Stack* int_stack(int size)
{
stack = (Stack*)malloc(sizeof(Stack)); 
stack->array=(char*)malloc(size* sizeof(char));
stack->top=-1;
stack->size=size;
return stack;
}

void push(Stack* stack,char item)
{
    if(stack->top==stack->size-1)
    {
        printf("Stack is full!");
    }
    else
    {
        stack->top++;
        stack->array[stack->top]=item;
        //printf(" %c ",item);
    }
}

char pop(Stack* stack)
{ char n;
    if(stack->top==-1)
    {
        printf("Stack is Empty!");
    }
    else
    {
     n=stack->array[stack->top];
     stack->top--;
     return n;
    }
    
}

void display(Stack* stack)
{ int i;
    if(stack->top==-1)
    {
        printf("Stack id Empty!\n");
    }
    else
    {
        for(i=stack->top;i>=0;i--)
        {
            printf("| %d |\n",stack->array[i]);
        }


    }
}

int is_operator(char ch)
{
    if(ch=='+'||ch=='-'||ch=='/'||ch=='*'||ch=='^')
    {
        return 1;
    }
    else{
        return 0;
    }
}

int perform_operation(int op1, int op2,char op)
{
    switch(op)
    {
        case '+':
        return op1+op2;
        break;
        case '-':
        return op1-op2;
        break;
        case '*':
        return op1*op2;
        break;
        case '/':
        return op1/op2;
        break;
        case '^':
        return pow(op1,op2);
        break;
        default:
        return 0;
    
    }
}
int main()
{
    char n[25]={'\0'},el;
    int i=0;
    int op2,op1,res;
    printf("Enter the postfix expression: ");
    scanf("%s",&n);
    stack=int_stack(strlen(n));

    while(i<strlen(n))
    {
    el=n[i];
    if(isdigit(el))
    { 
    push(stack,el-'0');
    
    }
    else if(is_operator(el))
    {
         op2=pop(stack);
         op1=pop(stack);
         res=perform_operation(op1,op2,el);
         push(stack,res);
        
    }
    i++;
    }
    printf("--------\n");
    display(stack);
    //display(stack);
return 0;
}