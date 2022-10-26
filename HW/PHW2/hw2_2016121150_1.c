// HW2 ���� 1.
// ���Ḯ��Ʈ�� ����� ������
// 1. �Է�(file), 2. ��� ���ϱ�, 3.���, 4.����, 0 .����
// 2016121150 ���ؿ�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct _node {
    int row;
    int col;
    int val;
    struct _node *next;
} node;

node* list_init(void){
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));
    if (head==NULL || tail==NULL) return NULL;
    head->next = tail;
    tail->next = tail;
    printf("\nList init complete!\n");
    return head;
}

// row col val next
node* smat_load(char* s, node* h){
    FILE* fp;
    node* p;
    node* s;
    int t;
    if ((fopen_s(&fp, s, "rb")) != NULL){
        printf("������ �����ϴ�\n");
        return;
    }
    
    fgets(t, )
    while(1){

    }
}

node* list_append(node* head, int row, int col, int val){
    // ����Ʈ�� ���ο� ���� �߰�(��������)
    node *p;
    node *s;

}

void smat_save(char *s, node* h){
    FILE* fp;
    node* p;
    node* s;
}

void smat_print(node *head){

}

node* smat_add(node *h1, node *h2){

}

void input(char* s){
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}

int option(void){
    char s[5];
    input(s);
    return atoi(s);
}

int main(void){
    node *h1 = init_list();
    node *h2 = init_list();
    int c;
    char file[MAX];
    do{
        printf("���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3: ���, 4:����, 0:����): ");
        c = option();
        switch (c){
            case 1:
                printf("���� �̸��� �Է��ϼ���: ");
                input(file);
                h1 = smat_load(file, h1);
                printf("��� ����� �����߽��ϴ�.\n");
                print_list(h1);
                break;
            case 2:
                printf("���� �̸��� �Է��ϼ���: ");
                input(file);
                h2 = smat_load(file, h2);
                printf("���� ��� ����Դϴ�.\n");
                print_list(h2);
                h1 = smat_sum(h1, h2);
                printf("���� ����Դϴ�.");
                print_list(h1);
                break;
            case 3:
                printf("��� ����� ��� ���·� ����մϴ�.");
                smat_print(h1);
                break;
            case 4:
                printf(" ���� �̸��� �Է��ϼ���: ");
                input(file);
                smat_save(file, h1);
                printf("��� ����� ���Ͽ� �����߽��ϴ�.");
                break;
            default:
                break;
        }
    } while(c);
    printf("Bye~\n");
    return 0;
}

/*
> ���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3:���, 4:����, 0:����): 1
���� �̸��� �Է��ϼ���: array1.txt
�������� �����߽��ϴ�.
4 6 5
0 4 2
1 1 3
2 2 -3
2 5 8
3 1 4
> ���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3:���, 4:����, 0:����): 2
���� �̸��� �Է��ϼ���: array1.txt
���� ��� ����Դϴ�.
4 6 5
0 4 2
1 1 3
2 2 -3
2 5 8
3 1 4
���� ����Դϴ�.
4 6 6
0 4 2
1 1 3
1 2 4
1 4 3
2 5 11
3 1 4
> ���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3:���, 4:����, 0:����): 3
��� ����� ��� ���·� ����մϴ�.
0 0 0 0 2 0
0 3 4 0 3 0
0 0 0 0 0 11
0 4 0 0 0 0
> ���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3:���, 4:����, 0:����): 4
���� �̸��� �Է��ϼ���: array3.txt
��� ����� ���Ͽ� �����߽��ϴ�.
> ���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3:���, 4:����, 0:����): 0
Bye~
*/