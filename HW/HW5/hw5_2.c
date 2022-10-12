#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int num;
    node *head;
} stack;

typedef struct _node{
    int key;
    struct _node *next;
} node;

node *head, *tail;

void init_stack(void){
    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));
    head->next = tail;
    tail->next = tail;
}

int push(int k){
    node *t;
    if ((t = (node*)malloc(sizeof(node))) == NULL){
        printf("\n      Out of memory...");
        return -1;
    }
    t->key = k; t->next = head->next; head->next = t;
    return k;
}

int pop(void){
    node *t;
    int i;
    if (head->next == tail) /* if empty */ {
        printf("\n      Stack underflow.");
        return -1;
    }
    t = head->next; i = t->key;
    head->next = t->next; free(t);
    return i;
}

void clear_stack(void){
    node *t, *s;
    t = head->next;
    while (t != tail){
        s = t; t = t->next;
        free(s);
    }
    head->next = tail;
}

int get_stack_top(void){
    return (top<0) ? -1 : stack[top];
}

int is_stack_empty(void){
    return (top<0);
}

int is_operator(int k){
    return (k=='+' || k=='-' || k=='*' || k=='/');
}

int precedence(int op){
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

void postfix(char *dst, char *src){
    char c;
    init_stack();
    while (*src) {
	if (*src== '(') {
	    push(*src); src++;
	}
	else if (*src== ')') {
	    while (get_stack_top() != '(') {
	*dst++ = pop(); *dst++ = ' ';
	    }
	    pop(); src++;
	}
	else if (is_operator(*src)) {
	    while (!is_stack_empty() &&
             precedence(get_stack_top())>= precedence(*src)){
	      *dst++ = pop(); *dst++ = ' ';
	    }
	    push(*src); src++;
	}	
	else if (*src>= '0' && *src<= '9') {
	    do {
	        *dst++ = *src++;
    	    } while (*src>= '0' && *src<= '9');
	    *dst++ = ' ';
	}
	else src++;
    }
    while (!is_stack_empty()) {
	*dst++ = pop(); *dst++ = ' ';
    }
    dst--; *dst= 0;
}