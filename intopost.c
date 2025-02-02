#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack
{
char* data;
int top;
int size;
};

struct stack* init(int n)
{
struct stack* s=(struct stack*)malloc(sizeof(struct stack));
s->data=(char*)malloc(sizeof(char)*n);
s->top=-1;
s->size=n;
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

void push(struct stack* s, char c)
{
if(isfull(s))
{
return;
}
s->data[++s->top]=c;
}

char pop(struct stack* s)
{
if(isemp(s))
{
return -1;
}
return s->data[s->top--];
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

char peek(struct stack* s)
{
if(isemp(s))
{
return -1;
}
return s->data[s->top];
}

int ishigh(char top,char curr)
{
int topp=checkprec(top);
int currp=checkprec(curr);
return topp>currp || (topp==currp && currp!='^');
}

char* intopo(char* infix)
{
int size=strlen(infix);
char* postfix=(char*)malloc(sizeof(char)*(size+1));
int x=0;
struct stack* s=init(size);
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
while(!isemp(s)&&peek(s)!='(')
{
postfix[x++]=pop(s);
}
pop(s);
}
else
{
while(!isemp(s)&&ishigh(peek(s),infix[i]))
{
postfix[x++]=pop(s);
}
push(s,infix[i]);
}
}
while(!isemp(s))
{
postfix[x++]=pop(s);
}
postfix[x]='\0';
return postfix;
}
void reversestring(char* s)
{
int n=strlen(s);
for(int i=0;i<n/2;i++)
{
char temp=s[i];
s[i]=s[n-i-1];
s[n-i-1]=temp;
}
}

void swapparantheses(char* s)
{
for(int i=0;s[i]!='\0';i++)
{
if(s[i]=='(')
{
s[i]=')';
}
else if(s[i]==')')
{
s[i]='(';
}
}
}

char* intopre(char* infix)
{
reversestring(infix);
swapparantheses(infix);
char* postfix=intopo(infix);
reversestring(postfix);
return postfix;
}

int main()
{
char i[]="(a+b)*(c+d)";
char* p1=intopre(i);
printf("%s",p1);
return 0;
}