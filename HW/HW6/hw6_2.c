#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _snode{
    int key;
    struct _snode *next;
} snode;

typedef struct {
    int num;
    snode *head;
} stack;

snode *shead, *stail;

void init_stack(void){
    shead = (snode*)malloc(sizeof(snode));
    stail = (snode*)malloc(sizeof(snode));
    shead->next = stail;
    stail->next = stail;
}

int push(int k){
    snode *t;
    if ((t = (snode*)malloc(sizeof(snode))) == NULL){
        printf("\n      Out of memory...");
        return -1;
    }
    t->key = k; t->next = shead->next; shead->next = t;
    return k;
}

int pop(void){
    snode *t;
    int i;
    if (shead->next == stail) /* if empty */ {
        printf("\n      Stack underflow.");
        return -1;
    }
    t = shead->next; i = t->key;
    shead->next = t->next; free(t);
    return i;
}

typedef struct _node{
    int key;
    struct _node *left;
    struct _node *right;
} node;

node *head, *tail;

void init_tree(void){
    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));
    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
}

node* make_node(int v, node* l, node* r){
    node* n = (node*)malloc(sizeof(node));
    n->left = l;
    n->right = r;
    n->key = v;
    return n;
}

void iterative_postorder_traverse(snode *n) {
   int tag; 
   snode *t = n;
   init_stack();
   push(t); push(1);
   while ((tag = pop())!= NULL) {
      t = pop();
      switch(tag) {
      case 1 :
         if (t == tail) break;
         push(t); push(2);
         push(t->right); push(1);
         push(t->left); push(1);
         break;
      case 2 :
         visit(t);
      }
   }
}