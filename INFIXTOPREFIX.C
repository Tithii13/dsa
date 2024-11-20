#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    char *data;
    int top;
    int size;
} Stack;

Stack* createStack(int n) {
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->size=n;
    s->data=(char*)malloc(sizeof(char) * n);
    s->top=-1;
    return s;
}

int isStackEmpty(Stack *s) {
    return s->top==-1;
}

int isStackFull(Stack *s) {
    return s->top==(s->size-1);
}

void push(Stack *s, char data) {
    if (isStackFull(s)) {
        printf("STACK IS FULL\n");
        return;
    }
    s->data[++s->top]=data;
}

char pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("STACK IS EMPTY\n");
        return -1;
    }
    return s->data[s->top--];
}

char peek(Stack *s) {
    if (isStackEmpty(s)) {
        printf("STACK UNDERFLOW\n");
        return -1;
    }
    return s->data[s->top];
}

int isOperand(char c) {
    return c!='+' && c!='-' && c!='*' && c!='/' && c!='^' && c!='(' && c!=')';
}

int checkPrecedence(char opr) {
    if (opr=='+' || opr=='-') {
        return 1;
    }
    if (opr=='*' || opr=='/') {
        return 2;
    }
    if (opr=='^') {
        return 3;
    }
    return 0;
}

int isHigherPrecedence(char top, char curr) {
    int topPrec=checkPrecedence(top);
    int currPrec=checkPrecedence(curr);
    return topPrec > currPrec || (topPrec==currPrec && curr!='^');
}

char* infixToPostfix(char *infix) {
    int size=strlen(infix);
    char *postfix=(char*)malloc(sizeof(char) * (size + 1));
    int x=0;
    Stack *s=createStack(size);
    
    for (int i=0; i < size; i++) {
        if (infix[i]=='(') {
            push(s, '(');
            continue;
        }
        if (isOperand(infix[i])) {
            postfix[x++]=infix[i];
            continue;
        }
        if (infix[i]==')') {
            while (!isStackEmpty(s) && peek(s)!='(') {
                postfix[x++]=pop(s);
            }
            pop(s);
            continue;
        }
        while (!isStackEmpty(s) && isHigherPrecedence(peek(s), infix[i])) {
            postfix[x++]=pop(s);
        }
        push(s, infix[i]);
    }
    while (!isStackEmpty(s)) {
        postfix[x++]=pop(s);
    }
    postfix[x]='\0';
    return postfix;
}

void reverseString(char *s) {
    int n=strlen(s);
    for (int i=0; i < n / 2; i++) {
        char temp=s[i];
        s[i]=s[n-i-1];
        s[n-i-1]=temp;
    }
}

void swapParentheses(char *s) {
    for (int i=0; s[i]!='\0'; i++) {
        if (s[i]=='(') {
            s[i]=')';
        } else if (s[i]==')') {
            s[i]='(';
        }
    }
}

char* infixToPrefix(char *infix) {
    reverseString(infix);
    swapParentheses(infix);
    char *postfix=infixToPostfix(infix);
    reverseString(postfix);
    return postfix;
}

int main() {
    char i1[]="(a+b)*(c-d)";
    char i2[]="a+b*(c^d-e)";
    char i3[]="((a+b)*(c+d)/(e-f))+g";
    char *p1=infixToPrefix(i1);
    char *p2=infixToPrefix(i2);
    char *p3=infixToPrefix(i3);
    printf("FIRST CONVERSION: %s\n", p1);
    printf("SECOND CONVERSION: %s\n", p2);
    printf("THIRD CONVERSION: %s\n", p3);

    return 0;
}
