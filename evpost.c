#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

struct stack
{
int* data;
int top;
int size;
};

struct stack* init(int n)
{
struct stack* s=(struct stack*)malloc(sizeof(struct stack));
s->data=(int*)malloc(sizeof(int)*n);
s->size=n;
s->top=-1;
return s;
}

int isemp(struct stack* s)
{
return s->top==-1;
}

int isfull(struct stack* s)
{
return s->top==s->size-1;
}

void push(struct stack* s, int value)
{
if(isfull(s))
{
return;
}
s->data[++s->top]=value;
}

int pop(struct stack* s)
{
if(isemp(s))
{
return -1;
}
return s->data[s->top--];
}

int evpost(char* postfix)
{
struct stack* s=init(100);
for(int  i=0;postfix[i]!='\0';i++)
{
char c=postfix[i];
if(isdigit(c))
{
push(s,c-'0');
}
else
{
int b=pop(s);
int a=pop(s);
switch(c)
{
case '+':
push(s,a+b);
break;
case '-':
push(s,a-b);
break;
case '*':
push(s,a*b);
break;
case '/':
push(s,a/b);
break;
case '^':
push(s,(int)pow(a,b));
break;
}
}
}
return pop(s);
}

int main()
{
char postfix[]="231*+9-";
printf("Result of postfix: %d",evpost(postfix));
return 0;
}