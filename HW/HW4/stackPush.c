#include <stdlib.h>
#include <stdio.h>

typedef struct _node* nodeptr;
typedef struct _node{
	int value[10];
	nodeptr next;
} node;

typedef struct  {
	int num;
	nodeptr head;
} stack;

int pop(stack* stk) {
	
}

void push(stack* stk, int v) {
	if (stk->num % 10 == 0) {
		node* n = (node*)malloc(sizeof(node));
		n->value[0] = v;
		stk->num++;
		n->next = stk->head;
		stk->head = n;
	}
	else {
		int i = stk->num % 10;
		stk->head->value[i] = v;
		stk->num++;
	}
}

stack* init_stack() {
	stack* s = malloc(sizeof(stack));
	s->num = 0;
	s->head = NULL;
	return s;
}

printstack(stack* s) {
	node* n = s->head;
	int num = s->num;
	while (num > 0) {
		printf("%d ", n->value[(num-1)%10]);
		num--;
		if (num % 10 == 0) n = n->next;
	}
	printf("\n");
}

main() {
	stack *s = init_stack();
	push(s, 1);
	push(s, 2);
	push(s, 3);
	push(s, 4);
	push(s, 5);
	push(s, 6);
	push(s, 7);
	push(s, 8);
	push(s, 9);
	push(s, 10);
	push(s, 11);
	printstack(s);
}
