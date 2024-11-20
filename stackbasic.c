#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack
{
char* data;
int top;
int size;
};

struct stack* crstack(int n)
{
struct stack* s=(struct stack*)malloc(sizeof(struct stack));
s->data=(char*)malloc(sizeof(char)*n);
s->top=-1;
s->size=n;
return s;
}

int isempty(struct stack* s)
{
return s->top==-1;
}

int isfull(struct stack* s)
{
return s->top==(s->size-1);
}

void push(struct stack* s, char data)
{
if(isfull(s))
{
return;
}
s->data[++s->top]=data;
}

char pop(struct stack* s)
{
if(isempty(s))
{
return -1;
}
return s->data[s->top--];
}

char peek(struct stack* s)
{
if(isempty(s))
{
return -1;
}
return s->data[s->top];
}

int isopd(char c)
{
return c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='^'&&c!='('&&c!=')';
}

int checkprec(char c)
{
if(c=='+'||c=='-')
{
return 1;
}
else if(c=='*'||c=='/')
{
return 2;
}
else if(c=='^')
{
return 3;
}
else
{
return 0;
}
}

int ishigh(char top,char curr)
{
int topp=checkprec(top);
int curp=checkprec(curr);
return topp>curp||(topp==curp && curp!='^');
}
char* intopo(char* infix)
{
int size=strlen(infix);
char* postfix=(char*)malloc(sizeof(char)*(size+1));
int x=0;
struct stack* s=crstack(size);
for(int i=0;i<size;i++)
{
if(infix[i]=='(')
{
push(s,'(');
}
else if(isopd(infix[i]))
{
postfix[x++]=infix[i];
}
else if(infix[i]==')')
{
while(!isempty(s)&&peek(s)!='(')
{
postfix[x++]=pop(s);
}
pop(s);
}
else
{
while(!isempty(s)&&ishigh(peek(s),infix[i]))
{
postfix[x++]=pop(s);
}
push(s,infix[i]);
}
}
while(!isempty(s))
{
postfix[x++]=pop(s);
}
postfix[x]='\0';
return postfix;
}

int main()
{
char i[]="(a+b)*(c+d)";

char *p1=intopo(i);
printf("%s",p1);
return 0;
}

