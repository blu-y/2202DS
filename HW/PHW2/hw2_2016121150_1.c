// HW2 문제 1.
// 연결리스트를 사용한 희소행렬
// 1. 입력(file), 2. 행렬 더하기, 3.출력, 4.저장, 0 .종료
// 2016121150 윤준영

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
        printf("파일이 없습니다\n");
        return;
    }
    
    fgets(t, )
    while(1){

    }
}

node* list_append(node* head, int row, int col, int val){
    // 리스트에 새로운 값을 추가(오름차순)
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
        printf("원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3: 출력, 4:저장, 0:종료): ");
        c = option();
        switch (c){
            case 1:
                printf("파일 이름을 입력하세요: ");
                input(file);
                h1 = smat_load(file, h1);
                printf("희소 행렬을 생성했습니다.\n");
                print_list(h1);
                break;
            case 2:
                printf("파일 이름을 입력하세요: ");
                input(file);
                h2 = smat_load(file, h2);
                printf("더할 희소 행렬입니다.\n");
                print_list(h2);
                h1 = smat_sum(h1, h2);
                printf("더한 결과입니다.");
                print_list(h1);
                break;
            case 3:
                printf("희소 행렬을 행렬 형태로 출력합니다.");
                smat_print(h1);
                break;
            case 4:
                printf(" 파일 이름을 입력하세요: ");
                input(file);
                smat_save(file, h1);
                printf("희소 행렬을 파일에 저장했습니다.");
                break;
            default:
                break;
        }
    } while(c);
    printf("Bye~\n");
    return 0;
}

/*
> 원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3:출력, 4:저장, 0:종료): 1
파일 이름을 입력하세요: array1.txt
희소행렬을 생성했습니다.
4 6 5
0 4 2
1 1 3
2 2 -3
2 5 8
3 1 4
> 원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3:출력, 4:저장, 0:종료): 2
파일 이름을 입력하세요: array1.txt
더할 희소 행렬입니다.
4 6 5
0 4 2
1 1 3
2 2 -3
2 5 8
3 1 4
더한 결과입니다.
4 6 6
0 4 2
1 1 3
1 2 4
1 4 3
2 5 11
3 1 4
> 원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3:출력, 4:저장, 0:종료): 3
희소 행렬을 행렬 형태로 출력합니다.
0 0 0 0 2 0
0 3 4 0 3 0
0 0 0 0 0 11
0 4 0 0 0 0
> 원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3:출력, 4:저장, 0:종료): 4
파일 이름을 입력하세요: array3.txt
희소 행렬을 파일에 저장했습니다.
> 원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3:출력, 4:저장, 0:종료): 0
Bye~
*/