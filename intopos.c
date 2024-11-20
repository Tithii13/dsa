#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct stack
{
    int top;
    char* s;
    int size;
};

struct stack* createstack(int n)
{
struct stack* s1=(struct stack*)malloc(sizeof(struct stack));
s1->top=-1;
s1->s=(char*)malloc(sizeof(char)*n);
s1->size=n;
return s1;
}

int isemp(struct stack* st)
{
    return st->top==-1;
}

int isfull(struct stack* st)
{
    return st->top==st->size-1;
}

void push(struct stack* s1,char n)
{
    if(isfull(s1))
    {
        printf("Stack full\n");
    }
    else{
        s1->top++;
        s1->s[s1->top]=n;
    }
}

int isop(char c)
{
    if(c=='+' || c=='-'||c=='/'||c=='*'||c=='^')
{
    return 1;
}
}
int checkprec(char c)
{
    if(c=='+' || c=='-')
    {
     return 1;
    }
    if(c=='/'||c=='*')
    {
  return 2;
    }
    if(c=='^')
    {
return 3;
    }
    return 0;
}

char pop(struct stack* s1)
{
    char c;
    if (isemp(s1))
    {
        printf("Empty\n");
    }
    else
    {
    c=s1->s[s1->top];
    s1->top--;
    return c;    
    }
}
int ishighprec(char top,char curr)
{
    int topprec=checkprec(top);
    int currprec=checkprec(curr);
    return topprec > currprec ||(topprec==currprec && curr!='^');
}

char peek(struct stack* s1)
{
    if(isemp(s1))
    {
        printf("Underflow\n");
        return -1;
    }
    else{
        return s1->s[s1->top];
    }
}

char* intopos(char* infix)
{
int size=strlen(infix);
char* postfix=(char*)malloc(sizeof(char)*(size+1));
int x=0;
struct stack* s2=createstack(size);
int i;
for(i=0;i<size;i++)
{
    if(infix[i]=='(')
    {
        push(s2,'(');
        continue;
    }
    if(isop(infix[i]))
    {
        postfix[x++]=infix[i];
        continue;
    }
    if(infix[i]==')')
    {
        while(!isemp(s2)&&peek(s2)!='(')
        {
            postfix[x++]=pop(s2);

        }
        pop(s2);
        continue;
    }
    while(!isemp(s2) &&ishighprec(peek(s2),infix[i]))
    {
        postfix[x++]=pop(s2);
         push(s2,infix[i]);
    }
    push(s2,infix[i]);
}
    while(!isemp(s2))
    {
        postfix[x++]=pop(s2);
    }
    postfix[x]='\0';
    return postfix;
    }



void display(struct stack* s1)
{
    int i;
    for(i=s1->top;i>=0;i--)
    {
        printf(" %c ",s1->s[i]);
    }
}

int main()
{
    char i1[]="a/b+(c-d)";
    char* p1=intopos(i1);
    printf("%s\n",p1);


}