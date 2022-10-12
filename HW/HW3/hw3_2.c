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
    printf("리스트 생성 완료! ");
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
    printf("(리스트 원소: ");
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
    printf("원소의 합: %d\n", sum);
    return sum;
}

node* make_list(void) {
    int n;
    printf("원소의 개수를 입력하세요: ");
    scanf("%d", &n);
    int a[n];
    printf("숫자를 입력하세요: ");
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

// 2. 숫자를 입력받아 숫자로 이루어진 단순연결 리스트를 만들고,
//    리스트 원소들의 합을 계산하는 프로그램 작성
//    비어있는 리스트는 0