#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int prec(char c)
{
if(c=='^')
{
return 3;
}
else if(c=='*'||c=='/')
{
return 2;
}
else if(c=='+'||c=='-')
{
return 1;
}
else
{
return -1;
}
}

char ass(char c)
{
if(c=='^')
{
return 'R';
}
else
{
return 'L';
}
}

void intopost(char s[])
{
char res[20];
int resindex=0;
int len=strlen(s);
char stack[20];
int stackindex=-1;
int i;
for(i=0;i<len;i++)
{
char c=s[i];
if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>=0&&c<=9))
{
res[resindex++]=c;
}
else if(c=='(')
{
stack[++stackindex]=c;
}
else if(c==')')
{
while(stackindex>=0&&stack[stackindex]!='(')
{
res[resindex++]=stack[stackindex--];
}
stackindex--;
}
else
{
while(stackindex>=0&&(prec(s[i])<prec(stack[stackindex])||prec(s[i])==prec(stack[stackindex])&&ass(s[i])=='L'))
{
res[resindex++]=stack[stackindex--];
}
stack[++stackindex]=c;
}
}
while(stackindex>=0)
{
res[resindex++]=stack[stackindex--];
}
res[resindex]='\0';
printf("%s\n",res);
}
int main()
{
char exp[]="A+B*C+D";
clrscr();
intopost(exp);
return 0;
}