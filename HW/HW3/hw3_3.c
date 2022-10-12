#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct _dnode {
    int key;
    struct _dnode *prev;
    struct _dnode *next;
} dnode;

dnode *head, *tail;

void init_dlist(void) {
    head = (dnode*)malloc(sizeof(dnode));
    tail = (dnode*)malloc(sizeof(dnode));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
    printf("����Ʈ ���� �Ϸ�! \n");
}

dnode *insert_dnode_ptr(int k, dnode *t) {
    /* insert k, before t */
    dnode *i;
    if (t==head) return NULL;
    i = (dnode*)malloc(sizeof(dnode));
    i->key = k;
    t->prev->next = i;
    i->prev = t->prev;
    t->prev = i;
    i->next = t;
    return i;
}

void print_dlist(dnode *p) {
    while(p != tail) {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

void reverse_list(dnode *h){
    // find number elements of dlist: n
    int n = 0;
    while (h->next != tail){
        h = h->next;
        n = n+1;
    }
    // now h = tail->prev
    // make reverse_array
    int *s = (int *)calloc(n, sizeof(int));
    for (int j = 0; j<n; j++){
        s[j] = h->key;
        h = h->prev;
    }
    // now h = head
    h = h->next;
    for (int j = 0; j<n; j++){
        h->key = s[j];
        h = h->next;
    }
    free(s);
}

void reverse_list_p(){
    dnode *p;
    dnode *np;
    p = head->next;
    while(p!=tail){
        np = p->next;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        head->next->prev = p;
        p->next = head->next;
        p->prev = head;
        head->next = p;
        p = np;
    }
}

int main() {
    int i;
    init_dlist();
    for (i=1; i<=10; i++) {
        insert_dnode_ptr(i,tail);
    }
    printf("����Ʈ ����: ");
    print_dlist(head->next);
    reverse_list(head);
    //reverse_list_p();
    printf("reverse_list ���: ");
    print_dlist(head->next);

}

// 3. 1���� 10������ ���ڷ� �̷���� ���߿��� ����Ʈ�� �����,
//    ���߿��� ����Ʈ�� ������ ������ �ݴ�� �ϴ� reverse_list �Լ��� �ۼ� �� ���
//    (tip) ���� ���� ���