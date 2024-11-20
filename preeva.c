#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

struct stack
{
int top;
int* data;
int size;
};

struct stack* init(int n)
{
struct stack* s=(struct stack*)malloc(sizeof(struct stack));
s->data=(int*)malloc(sizeof(int)*n);
s->top=-1;
s->size=n;
return s;
}

int isemp(struct stack* s)
{
return s->top==-1;
}

void push(struct stack* s, int c)
{
s->data[++s->top]=c;
}

int pop(struct stack* s)
{
if(isemp(s))
{
return -1;
}
return s->data[s->top--];
}

int evapre(char* pre)
{
int n=strlen(pre);
struct stack* s=init(100);
for(int i=n-1;i>=0;i--)
{
char c=pre[i];
if(isdigit(c))
{
push(s,c-'0');
}
else
{
int a=pop(s);
int b=pop(s);
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
char prefix[]="-+*23*549";
printf("result: %d",evapre(prefix));
return 0;
}