#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node *next;
} node;

node* init_list(void) {
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));
    // malloc�� NULL�� ������ ��� ó�� �����?
    if (head==NULL || tail==NULL) return NULL;
    head->next = tail;
    tail->next = tail;
    printf("����Ʈ ���� �Ϸ�!\n");
    return head;
}

node *insert_after(int k, node* t) {
    node *s;
    if (!t || t->next == t) return t;
    s = (node*)malloc(sizeof(node));
    if (s==NULL) return s;
    s->key = k;
    s->next = t->next;
    t->next = s;
    return s;
}

void print_list(node* h) {
    h = h->next;
    printf("����Ʈ ����: ");
    while(h != h->next) {
        printf("%d ", h->key);
        h = h-> next;
    }
    printf("\n");
}

int max_element(node *h) {
    int max = -999999; 
    //�ִ밡 -1000000 �Ʒ��̸� ���� �߻� ����
    h = h->next;
    while (h->next != h){
        if (h->key >= max) max = h->key;
        h = h->next;
    }
    printf("���� ū ������ ��: %d\n", max);
    return max;
}

int main() {
    node *head = init_list();
    //node *p;
    insert_after(1,head);
    insert_after(6,head);
    insert_after(3,head);
    insert_after(4,head);
    print_list(head);
    max_element(head);
}

// 1. �ܼ����Ḯ��Ʈ�� �����, ����Ʈ ���� ���ҵ��� ���, ���� ū �������� ���
//    ��� ��� �ּҸ� �޾� ���� ū ���� ��ȯ�ϴ� �Լ� int max_element(node *head)�� �ۼ�
//    ����ִ� ����Ʈ�� -999999