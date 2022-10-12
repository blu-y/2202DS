#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node *next;
} node;

node* init_list(void) {
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));
    if (head==NULL || tail==NULL) return NULL;
    head->next = tail;
    tail->next = tail;
    printf("����Ʈ ���� �Ϸ�! ");
    return head;
}

node *insert_after(int k, node* t) {
    node *s;
    if (!t || t->next == t) return t;
    s = (node*)malloc(sizeof(node));
    if (s==NULL) return s;
    s->key = k;
    s->next = t-> next;
    t->next = s;
    return s;
}

void print_list(node* h) {
    h = h->next;
    printf("(����Ʈ ����: ");
    while(h != h->next) {
        printf("%d ", h->key);
        h = h-> next;
    }
    printf(")\n");
}

int sum_list(node *h) {
    int sum = 0;
    h = h->next;
    while (h->next != h){
        sum += h->key;
        h = h->next;
    }
    printf("������ ��: %d\n", sum);
    return sum;
}

node* make_list(void) {
    int n;
    printf("������ ������ �Է��ϼ���: ");
    scanf("%d", &n);
    int a[n];
    printf("���ڸ� �Է��ϼ���: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    node *head = init_list();
    node *l = head;
    for (int i = 0; i < n; i++){
        //printf("%d, %d ", i, a[i]);
        l = insert_after(a[i],l);
    }
    print_list(head);
    return head;
}

int main() {
    node *head = make_list();
    sum_list(head);
}

// 2. ���ڸ� �Է¹޾� ���ڷ� �̷���� �ܼ����� ����Ʈ�� �����,
//    ����Ʈ ���ҵ��� ���� ����ϴ� ���α׷� �ۼ�
//    ����ִ� ����Ʈ�� 0