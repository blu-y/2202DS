#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct _dnode
{
    int key;
    struct _dnode *prev;
    struct _dnode *next;
} dnode;

dnode *head, *tail;
void init_dlist(void)
{
    head = (dnode*)malloc(sizeof(dnode));
    tail = (dnode*)malloc(sizeof(dnode));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
}

dnode *insert_dnode_ptr(int k, dnode *t) /* insert k, before t */
{
    dnode *i;
    if (t == head)
        return NULL;
    i = (dnode*)malloc(sizeof(dnode));
    i->key = k;
    t->prev->next = i;
    t->prev = i;
    i->prev = t->prev;
    i->next = t;
    return i;
}

void print_dlist(dnode *p)
{
    while (p != tail)
    {
        printf("%d ", p->key);
        p = p->next;
    }
}

void print_element(dnode *p)
{
    printf("%d ", p->key);
}

int main()
{
    int i;
    init_dlist();
    for (i=1; i<=10; i++) {
        insert_dnode_ptr(i, tail);
    }
    print_dlist(head->next);

    return 0;
}