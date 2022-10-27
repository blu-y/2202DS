// HW2 문제 1.
// 연결리스트를 사용한 희소행렬
// 1. 입력(file), 2. 행렬 더하기, 3.출력, 4.저장, 0 .종료
// 2016121150 윤준영

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct _node {
    /* define node struct */
    int row, col, val;
    struct _node *next;
} node;

node* list_init(void){
    /* initialize list
       return : list head node
    */
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));
    if (head==NULL || tail==NULL) return NULL;
    // if memory allocation fail, return NULL
    head->next = tail;
    tail->next = tail;
    return head;
}

void list_print(node * h){
    /* print list head to tail*/
    node* n;
    n = h;
    while(n->next != n){ // if not tail
        printf("%d %d %d\n", n->row, n->col, n->val);
        n = n->next;
    }
}

void list_append(node* h, int row, int col, int val, int mode){
    /* append new value in list, ascending
       input : head node, row, column, value, mode
       mode = 0(file load), 1(add sparse matrix)
    */ 
    node *s = h;
    node *p = h->next;
    node *new = (node*)malloc(sizeof(node));
    // order : s > new > p
    new->row = row;
    new->col = col;
    new->val = val;
    // fill new node infos
    while(p->next != p){
        // until p = tail
        if ((p->row < row) || ((p->row == row) && (p->col < col))){
            s = p;
            p = p->next;
        } // if p's row, column is smaller check next node
        else {
            break;
        } // else break
    }
    if (mode && ((p->col == col) && ((p->row == row)))){
        p->val += val;
        free(new);
        // in adding mode, if new row, column is same with p
        // add values and free new node
        if (p->val == 0){
            s->next = p->next;
            free(p);
            h->val -= 1;
        } // if added value is 0, delete node
    }
    else {
        new->next = p;
        s->next = new;
        if (mode) h->val += 1;
    } // insert new node between s and p
      // if adding mode, num of value(head->val) += 1
}

node* smat_load(char* str, node* h){
    /* load sparse matrix file to list
       input : filename, list head node
       return : list head node
    */
    FILE* fp;
    char line[MAX];
    int last = 0;
    int row, col, val;
    if ((fopen_s(&fp, str, "rb")) != NULL){
        printf("파일이 없습니다\n");
        return h;
    }
    /* first line -> head node */
    fgets(line, MAX, fp);
    if (line[strlen(line)-1] != 10) last = 1; // lastline == {CONTENTS, NULL}
    else line[strlen(line)-2] = 0; // not lastline == {CONTENTS,CR,LF,NULL} make {CONTENTS,NULL}
    h->row = atoi(strtok(line, " ")); // strtok separates string by " "
    h->col = atoi(strtok(NULL, " ")); // head node contains matrix size
    h->val = atoi(strtok(NULL, " ")); // and number of non 0 value
    /* second to last line -> append(sorted) */
    while(!last){
        fgets(line, MAX, fp);
        if (line[strlen(line)-1] != 10) last = 1; // lastline == {CONTENTS, NULL}
        else line[strlen(line)-2] = 0; // not lastline == {CONTENTS,CR,LF,NULL} make {CONTENTS,NULL}
        row = atoi(strtok(line, " ")); // strtok separates string by " "
        col = atoi(strtok(NULL, " "));
        val = atoi(strtok(NULL, " "));
        list_append(h, row, col, val, 0); // append to list (mode 0)
    }
    fclose(fp);
    return h;
}

void smat_save(char *str, node* h){
    /* load sparse matrix file to list
       input : filename, list head node
    */
    FILE* fp;
    node* n = h;
    char temp[MAX];
    if ((fopen_s(&fp, str, "wb")) != NULL){
        printf("파일 저장 실패\n");
        return;
    }
    /* first to last-1 line */
    while(n->next->next != n->next){
        // make string with row column value and new_line and write to file
        sprintf(temp, "%d %d %d\n", n->row, n->col, n->val);
        fputs(temp, fp);
        n = n->next;
    }
    /* last line */
    // make string with row column value and write to file
    sprintf(temp, "%d %d %d", n->row, n->col, n->val);
    fputs(temp, fp);
    fclose(fp);
}

void smat_print(node *h){
    /* print sparse matrix list with matrix form */
    node *n = h->next;
    int row = h->row;
    int col = h->col;
    int *mat = (int*)calloc(row*col, sizeof(int));
    while(n->next != n){
        mat[col*n->row + n->col] = n->val;
        n = n->next;
    } // make matrix with list
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) printf("%d ", mat[i*col+j]);
        printf("\n");
    } // print matrix[i*col+j] i=0~row-1, j=0~col-1
}

node* smat_add(node *h1, node *h2){
    /* add 2 sparse matrix with list form
       input : list1 head node, list2 head node
       return : list1 head node(summed)
    */
    if (!(h1->row == h2->row) && (h1->col == h2->col)){
        printf("행렬의 크기가 다릅니다!\n");
        return h1;
    } // if matrix size does not match
    node* n;
    n = h2->next;
    while(n->next != n){
        list_append(h1, n->row, n->col, n->val, 1);
        n = n->next;
    } // append head to tail (except head and tail) (add mode)
    return h1;
}

void input(char* s){
    /* get string and delete new_line */
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}

int option(void){
    /* get integer using input function */
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
        printf("> 원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3: 출력, 4:저장, 0:종료): ");
        c = option();
        switch (c){
            case 1:
                printf("파일 이름을 입력하세요: ");
                input(file);
                h1 = smat_load(file, h1);
                printf("희소 행렬을 생성했습니다.\n");
                list_print(h1);
                break;
            case 2:
                printf("파일 이름을 입력하세요: ");
                input(file);
                h2 = smat_load(file, h2);
                printf("더할 희소 행렬입니다.\n");
                list_print(h2);
                h1 = smat_add(h1, h2);
                printf("더한 결과입니다.\n");
                list_print(h1);
                break;
            case 3:
                printf("희소 행렬을 행렬 형태로 출력합니다.\n");
                smat_print(h1);
                break;
            case 4:
                printf("파일 이름을 입력하세요: ");
                input(file);
                smat_save(file, h1);
                printf("희소 행렬을 파일에 저장했습니다.\n");
                break;
            default:
                break;
        }
    } while(c); // if input is 0 or NULL break
    printf("Bye~\n");
    return 0;
}
