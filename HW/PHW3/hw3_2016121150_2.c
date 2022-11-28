/*  HW3 문제 2.
    연결법을 사용한 해쉬 테이블의 구현
    Input: .txt
        Data order: 이름 학번 전공
    Output: .out
        Sort order: 학번
    > HW\PHW3\hw3_2016121150_2.exe infile.txt
    2016121150 윤준영 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define NAME_SIZE 12
#define ID_SIZE 12
#define MAJ_SIZE 12
#define LINE_SIZE 36

typedef struct _stdt {
    char name[NAME_SIZE];
    int id;
    char maj[MAJ_SIZE];
    struct _stdt* left;
    struct _stdt* right;
} stdt;

int up(int i) {
    // upper letter
    if (i >=97 && i <= 122) i -=32;
    return i;
}
int idcmp(stdt* a, stdt* b) {
    return a->id - b->id;
}
void input(char* s){
    /* get string and delete new_line */
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}
int str2int(void){
    /* get integer using input function */
    char s[ID_SIZE];
    input(s);
    return atoi(s);
}

void bintree_init(stdt** s) {
    *s = (stdt *)malloc(sizeof(stdt));
    (*s)->id = INT_MAX;
    (*s)->left = NULL;
    (*s)->right = NULL;
}

void data_insert(stdt* S, stdt* s, int* n) {
    stdt* p = S;
    printf("test\n");
    while (p != NULL) {
        // go left if p>s, go right if p<s
        if (idcmp(p, s) > 0) p = p->left;
        else p = p->right;
    }
    memcpy(p, s, sizeof(stdt));
}
int data_load(char* fn, stdt* S, int* n) {
    // input: file name, student struct array
    // output: number of student
    FILE* fp;
    stdt* s;
    char line[LINE_SIZE];
    char *lp;
    int i = 0;
    if ((fopen_s(&fp, fn, "r")) != NULL) {
        printf("\nWrong File!");
        return i;
    } // return 0 no file
    while(!feof(fp)) {
        fgets(line, sizeof(line), fp);
        // remove \n if exist
        if (line[strlen(line)-1] == 10) line[strlen(line)-1] = 0;
        s = (stdt *)malloc(sizeof(stdt));
        //printf("%s\n", &line);
        lp = strtok(line, " ");     // get name
        strcpy(s->name, lp);
        lp = strtok(NULL, " ");     // get id
        s->id = atoi(lp);
        lp = strtok(NULL, " ");     // get major
        strcpy(s->maj, lp);
        data_insert(S, s, (int *)n);
    }
    fclose(fp);
    printf("Records ard loaded to binary tree !");
    return i;
}
void inorder_save(FILE* fp, stdt* s, int* n, int m) {
    char line[LINE_SIZE];
    while (s != NULL) {
        inorder_save(fp, s->left, (int *)n, m);
        sprintf(line, "%s %d %s", s->name, s->id, s->maj);
        if (*n < m) strcat(line, "\n");
        fputs(line, fp);
        (*n)++;
        inorder_save(fp, s->right, (int *)n, m);
    }
}
void data_save(char* fn, stdt* S, int n) {
    FILE* fp;
    char line[LINE_SIZE];
    fopen_s(&fp, fn, "w");
    inorder_save(fp, S, &n, n);
    fclose(fp);
    printf("%d records are saved in %s\n", n, fn);
}
void data_find(stdt* S, int id) {
    stdt *s;
    if (s) printf("found! : [%s %s %s]", s->name, s->id, s->maj);
    else printf("[%s] is not found");
}
void data_delete(stdt* S, int id) {
    stdt *s;
    if (s) printf("[%s %s %s] is deleted!", s->name, s->id, s->maj);
    else printf("[%s] is not found");
}

int main(void) {
    // for (int i = 1; i < n; i++) {
    //     printf("%s %s %s\n", S[i]->name, S[i]->id, S[i]->maj);
    // }

    // stdt* s = (stdt *)malloc(sizeof(stdt));
    stdt* S;
    stdt* s = (stdt *)malloc(sizeof(stdt));
    bintree_init(&S);
    int c = 0;
    int n = 0;
    int id;
    char fn[MAX];
    do {
        printf("\n Select one (1:load, 2:insert, 3:find, 4:delete, 5:Save, 6:Quit : ");
        c = str2int();
        switch (c) {
            case 1: // load
                printf("Input file name : ");
                // input(fn); ////
                strcpy(fn, "infile.txt"); ////
                n = data_load(fn, S, &n);
                break;
            case 2: // insert
                printf("Input Name : ");
                input(s->name);
                printf("Input Id : ");
                s->id = str2int();
                printf("Input Major : ");
                input(s->maj);
                data_insert(S, s, &n);
                printf("Data Inserted!");
                break;
            case 3: // find
                printf("Input Id : ");
                id = str2int();
                data_find(S, id);
                break;
            case 4: // delete
                printf("Input Id : ");
                id = str2int();
                data_delete(S, id);
                break;
            case 5: // Save
                printf("Input file name : ");
                input(fn);
                data_save(fn, S, n);
                break;
            default:
                break;
        }
    } while (c != 6);
    printf("Good bye~\n");
    return 0;
}
