
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Stack 
{
     char *data;
     int top;
     int size;
}Stack;

Stack* create(int n) 
{
Stack *s=(Stack*)malloc(sizeof(Stack));
s->size=n;
s->data=(char*)malloc(sizeof(char)*n);
s->top=-1;
return s;
}

int isEmpty(Stack *s)
{
return s->top==-1;
}

int isFull(Stack *s) 
{
return s->top==(s->size-1);
}

void push(Stack *s, char data)
{
if (isFull(s))
{
printf("STACK IS FULL\n");
return;
}
s->data[++s->top]=data;
}

char pop(Stack *s) 
{
if (isEmpty(s)) {
printf("STACK IS EMPTY\n");
return -1;
}
return s->data[s->top--];
}

char peek(Stack *s)
{
if (isEmpty(s)) 
{
printf("STACK UNDERFLOW\n");
return -1;
}
return s->data[s->top];
}

int isOperand(char c) 
{
return c!='+' && c!='-' && c!='*' && c!='/' && c!='^' && c!='(' && c!=')';
}


int checkPrec(char opr) {
if (opr=='+'||opr=='-') {
return 1;
}
if (opr=='*'||opr=='/')
{
return 2;
}
if (opr=='^')
 {
return 3;
}
return 0;
}


int isPrecHigh(char top, char curr)
 {
int topPrec=checkPrec(top);
int currPrec=checkPrec(curr);
return topPrec>currPrec||(topPrec==currPrec && curr!='^');
}

char* getPostfix(char *infix) 
{
int size=strlen(infix);
char *postfix=(char*)malloc(sizeof(char)*(size + 1));
int x=0;
Stack *s=create(size);
for (int i=0; i < size; i++) 
{
if (infix[i]=='(') {
push(s, '(');
continue;
}
if (isOperand(infix[i])) {
postfix[x++]=infix[i];
continue;
}
if (infix[i]==')') {
while (!isEmpty(s) && peek(s) != '(') {
postfix[x++]=pop(s);
}
pop(s);
continue;
}
while (!isEmpty(s) && isPrecHigh(peek(s),infix[i])) {
postfix[x++]=pop(s);
}
push(s, infix[i]);
}
while (!isEmpty(s)) {
postfix[x++]=pop(s);
}
postfix[x]='\0';
return postfix;
}
void reverseString(char *s) {
int n=strlen(s);
for (int i=0; i<n/2; i++) {
char temp=s[i];
s[i]=s[n-i-1];
s[n-i-1]=temp;
}
}
void swapParentheses(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
if (s[i] == '(') {
s[i] = ')';
} else if (s[i] == ')') {
s[i] = '(';
}
}
}
char* getPrefix(char *infix) {
reverseString(infix);
swapParentheses(infix);
char *postfix = getPostfix(infix);
reverseString(postfix);
return postfix;
}
int main() {
char infix[] = "((a/b)+c)-(d+(e*f))";
char infix2[] = "a^b*(c+d)" ;
char infix3[] = "x*y+z*p/(r+e)" ;
char *prefix = getPrefix(infix);
char *prefix2 = getPrefix(infix2) ;
char *prefix3 = getPrefix(infix3) ;
printf("Prefix1: %s\n", prefix);
printf("Prefix2: %s\n",prefix2) ;
printf("Prefix3: %s\n",prefix3) ;
return 0;
}

