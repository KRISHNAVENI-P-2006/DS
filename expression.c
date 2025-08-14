#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }
int isEmpty() { return top == -1; }

int precedence(char op) {
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^');
}

void reverse(char* exp) {
    int i, j;
    char temp;
    for(i=0, j=strlen(exp)-1; i<j; i++, j--) {
        temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

// Infix to Postfix
void infixToPostfix(char infix[MAX], char postfix[MAX]) {
    top = -1;
    int k=0;
    for(int i=0; infix[i]; i++) {
        char c = infix[i];
        if(isalnum(c)) {
            postfix[k++] = c;
        }
        else if(c=='(') {
            push(c);
        }
        else if(c==')') {
            while(!isEmpty() && peek()!='(') {
                postfix[k++] = pop();
            }
            pop();
        }
        else if(isOperator(c)) {
            while(!isEmpty() && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }
    while(!isEmpty()) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

// Infix to Prefix
void infixToPrefix(char infix[], char prefix[MAX]) {
    char rev[MAX], postfix[MAX];
    strcpy(rev, infix);
    reverse(rev);
    for(int i=0; rev[i]; i++) {
        if(rev[i]=='(') rev[i] = ')';   //Swap between ( and )
        else if(rev[i]==')') rev[i] = '(';
    }
    infixToPostfix(rev, postfix);
    reverse(postfix);
    strcpy(prefix, postfix);
}

// Evaluate postfix expression
int evalPostfix(char exp[MAX]) {
    int evalStack[MAX], evalTop = -1;
    for(int i=0; exp[i]; i++) push(exp[i]);  
    int size = top + 1;

    // Process stack from bottom to top (same as original order)
    for(int i=0; i<size; i++) {
        char c = stack[i];
        if(isdigit(c)) {
            evalStack[++evalTop] = c - '0';   //To convert char to int
        }
        else if(isOperator(c)) {
            int b = evalStack[evalTop--];
            int a = evalStack[evalTop--];
            switch(c) {
                case '+': evalStack[++evalTop] = a + b; break;
                case '-': evalStack[++evalTop] = a - b; break;
                case '*': evalStack[++evalTop] = a * b; break;
                case '/': evalStack[++evalTop] = a / b; break;
                case '^': evalStack[++evalTop] = pow(a, b); break;
            }
        }
    }
    top = -1; // clear
    return evalStack[evalTop];
}

// Evaluate using stack storing expression (for prefix)
int evalPrefix(char exp[MAX]) {
    int evalStack[MAX], evalTop = -1;
    for(int i=0; exp[i]; i++) push(exp[i]);  // store in stack
    int size = top + 1;

    // Process stack from top to bottom (reverse order)
    for(int i=size-1; i>=0; i--) {
        char c = stack[i];
        if(isdigit(c)) {
            evalStack[++evalTop] = c - '0';
        }
        else if(isOperator(c)) {
            int a = evalStack[evalTop--];
            int b = evalStack[evalTop--];
            switch(c) {
                case '+': evalStack[++evalTop] = a + b; break;
                case '-': evalStack[++evalTop] = a - b; break;
                case '*': evalStack[++evalTop] = a * b; break;
                case '/': evalStack[++evalTop] = a / b; break;
                case '^': evalStack[++evalTop] = pow(a, b); break;
            }
        }
    }
    top = -1; // clear
    return evalStack[evalTop];
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];
    int choice;

    while(1) {
        printf("\n--- Menu ---\n");
        printf("1. Infix to Postfix \n");
        printf("2. Infix to Prefix \n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if(choice == 3) exit(0);

        printf("Enter infix expression: ");
        gets(infix);

        switch(choice) {
            case 1:
                infixToPostfix(infix, postfix);
                printf("Postfix Expression : %s\n", postfix);
                printf("Result: %d\n", evalPostfix(postfix));
                break;
            case 2:
                infixToPrefix(infix, prefix);
                printf("Prefix Expression : %s\n", prefix);
                printf("Result: %d\n", evalPrefix(prefix));
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
}
