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
    return head;
}

void list_append(node* h, int row, int col, int val){
    // ����Ʈ�� ���ο� ���� �߰�(��������)
    node *s = h;
    node *p = h->next;
    node *new = (node*)malloc(sizeof(node));
    new->row = row;
    new->col = col;
    new->val = val;
    while(p->next != p){
        // until p = tail
        if ((p->row < row) || ((p->row == row) && (p->col < col))){
            s = p;
            p = p->next;
        } // if p(r,c) is smaller check next
        
        //    break;
        //} // if value already exists, += val
        else {
            break;
        } // else break
    }
    if ((p->col == col) && ((p->row == row))){
        p->val += val;
        free(new);
        if (p->val == 0){
            s->next = p->next;
            free(p);
        }
    }
    else {
        new->next = p;
        s->next = new;
    }
}

void list_print(node* h){
    node* n;
    n = h;
    while(n->next != n){
        printf("%d %d %d\n", n->row, n->col, n->val);
        n = n->next;
    }
}

node* smat_load(char* str, node* h){
    FILE* fp;
    char line[MAX];
    int last = 0;
    int row, col, val;
    if ((fopen_s(&fp, str, "rb")) != NULL){
        printf("������ �����ϴ�\n");
        return h;
    }
    /* first line */
    fgets(line, MAX, fp);
    if (line[strlen(line)-1] != 10) last = 1;
    // lastline = contents NULL
    else line[strlen(line)-2] = 0;
    // not lastline = contents CR LF NULL > contents NULL
    h->row = atoi(strtok(line, " "));
    h->col = atoi(strtok(NULL, " "));
    h->val = atoi(strtok(NULL, " "));
    /* second to last line */
    while(!last){
        fgets(line, MAX, fp);
        if (line[strlen(line)-1] != 10) last = 1;
        // lastline = contents NULL
        else line[strlen(line)-2] = 0;
        // not lastline = contents CR LF NULL > contents NULL
        row = atoi(strtok(line, " "));
        col = atoi(strtok(NULL, " "));
        val = atoi(strtok(NULL, " "));
        list_append(h, row, col, val);
    }
    fclose(fp);
    return h;
}

void smat_save(char *str, node* h){
    FILE* fp;
    node* n = h;
    char temp[MAX];
    if ((fopen_s(&fp, str, "wb")) != NULL){
        printf("���� ���� ����\n");
        return;
    }
    /* first to last-1 line*/
    while(n->next->next != n->next){
        sprintf(temp, "%d %d %d\n", n->row, n->col, n->val);
        fputs(temp, fp);
        n = n->next;
    }
    /* last line */
    sprintf(temp, "%d %d %d", n->row, n->col, n->val);
    fputs(temp, fp);
    fclose(fp);
}

void smat_print(node *h){
    node *n = h->next;
    int row = h->row;
    int col = h->col;
    int *mat = (int*)calloc(row*col, sizeof(int));
    while(n->next != n){
        mat[col*n->row + n->col] = n->val;
        n = n->next;
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) printf("%d ", mat[i*col+j]);
        printf("\n");
    }
}

node* smat_add(node *h1, node *h2){
    if (!(h1->row == h2->row) && (h1->col == h2->col)){
        printf("����� ũ�Ⱑ �ٸ��ϴ�!\n");
        return h1;
    }
    node* n;
    n = h2->next;
    while(n->next != n){
        list_append(h1, n->row, n->col, n->val);
        n = n->next;
    }
    return h1;
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
    node *h1 = list_init();
    node *h2 = list_init();
    int c;
    char file[MAX];
    do{
        printf("> ���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3: ���, 4:����, 0:����): ");
        c = option();
        switch (c){
            case 1:
                printf("���� �̸��� �Է��ϼ���: ");
                input(file);
                h1 = smat_load(file, h1);
                printf("��� ����� �����߽��ϴ�.\n");
                list_print(h1);
                break;
            case 2:
                printf("���� �̸��� �Է��ϼ���: ");
                input(file);
                h2 = smat_load(file, h2);
                printf("���� ��� ����Դϴ�.\n");
                list_print(h2);
                h1 = smat_add(h1, h2);
                printf("���� ����Դϴ�.\n");
                list_print(h1);
                break;
            case 3:
                printf("��� ����� ��� ���·� ����մϴ�.\n");
                smat_print(h1);
                break;
            case 4:
                printf("���� �̸��� �Է��ϼ���: ");
                input(file);
                smat_save(file, h1);
                printf("��� ����� ���Ͽ� �����߽��ϴ�.\n");
                break;
            default:
                break;
        }
    } while(c);
    printf("Bye~\n");
    return 0;
}
