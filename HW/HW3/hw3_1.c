#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node *next;
} node;

node* init_list(void) {
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));
    // malloc이 NULL을 리턴할 경우 처리 방법은?
    if (head==NULL || tail==NULL) return NULL;
    head->next = tail;
    tail->next = tail;
    printf("리스트 생성 완료!\n");
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
    printf("리스트 원소: ");
    while(h != h->next) {
        printf("%d ", h->key);
        h = h-> next;
    }
    printf("\n");
}

int max_element(node *h) {
    int max = -999999; 
    //최대가 -1000000 아래이면 문제 발생 가능
    h = h->next;
    while (h->next != h){
        if (h->key >= max) max = h->key;
        h = h->next;
    }
    printf("가장 큰 원소의 값: %d\n", max);
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

// 1. 단순연결리스트를 만들고, 리스트 내의 원소들을 출력, 가장 큰 정수값을 출력
//    헤드 노드 주소를 받아 가장 큰 값을 반환하는 함수 int max_element(node *head)를 작성
//    비어있는 리스트는 -999999