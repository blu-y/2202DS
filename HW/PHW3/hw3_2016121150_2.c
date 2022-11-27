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
#define SENTINEL "ZZZZZZZZZZZ 999999999 ZZZZZZZZZZZ"

typedef struct {
    char name[NAME_SIZE];
    char id[ID_SIZE];
    char maj[MAJ_SIZE];
} student;

int up(int i) {
    // upper letter
    if (i >=97 && i <= 122) i -=32;
    return i;
}
int cmp(student* a, student* b) {
    // return +: a > b
    // return 0: a = b
    // return -: a < b
    // continue until different letter or until end of string
    // if different letter return a-b(major)
    // if same end of string return a-b(id)
    int i = 0;
    while(up(a->maj[i]) == up(b->maj[i]) && up(a->maj[i]) != 0 && up(b->maj[i]) != 0) i++;
    if (up(a->maj[i]) == up(b->maj[i])) return atoi(a->id) - atoi(b->id);
    else return up(a->maj[i]) - up(b->maj[i]);
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

int data_load(char* fn, student* S[MAX]) {
    // input: file name, student struct array
    // output: number of student
    FILE* fp;
    student* s;
    char line[LINE_SIZE] = SENTINEL;
    char *lp;
    int i = 0;
    if ((fopen_s(&fp, fn, "r")) != NULL) {
        printf("\nWrong File!");
        return i;
    } // return 0 no file
    while(1) {
        // remove \n if exist
        if (line[strlen(line)-1] == 10) line[strlen(line)-1] = 0;
        s = (student *)malloc(sizeof(student));
        //printf("%s\n", &line);
        lp = strtok(line, " ");     // get name
        strcpy(s->name, lp);
        lp = strtok(NULL, " ");     // get id
        strcpy(s->id, lp);
        lp = strtok(NULL, " ");     // get major
        strcpy(s->maj, lp);
        S[i++] = s;
        if (feof(fp)) break;
        fgets(line, sizeof(line), fp);
    }
    fclose(fp);
    return i;
}
void data_save(char* fn, student* S[], int n) {
    FILE* fp;
    char line[LINE_SIZE];
    fopen_s(&fp, fn, "w");
    for (int i = 1; i < n; i++){
        strcpy(line, S[i]->name);
        strcat(line, " ");
        strcat(line, S[i]->id);
        strcat(line, " ");
        strcat(line, S[i]->maj);
        if (i < n-1) strcat(line, "\n");
        fputs(line, fp);
    }
    fclose(fp);
    printf("%d records are saved in %s\n", n, fn);
}
void data_insert(student* S[]) {
    student* s = (student *)malloc(sizeof(student));
    printf("Input Name : ");
    input(s->name);
    printf("Input Id : ");
    input(s->id);
    printf("Input Major : ");
    input(s->maj);
    // insert
    printf("Data Inserted!");
}
void data_find(student* S[], int id) {
    student *s;
    if (s) printf("found! : [%s %s %s]", s->name, s->id, s->maj);
    else printf("[%s] is not found");
}
void data_delete(student* S[], int id) {
    student *s;
    if (s) printf("[%s %s %s] is deleted!", s->name, s->id, s->maj);
    else printf("[%s] is not found");
}

int main(void) {
    // for (int i = 1; i < n; i++) {
    //     printf("%s %s %s\n", S[i]->name, S[i]->id, S[i]->maj);
    // }

    // student* s = (student *)malloc(sizeof(student));
    student* S[MAX];
    int c = 0;
    int n;
    int id;
    char fn[MAX];
    do {
        printf("\n Select one (1:load, 2:insert, 3:find, 4:delete, 5:Save, 6:Quit : ");
        c = str2int();
        switch (c) {
            case 1: // load
                printf("Input file name : ");
                input(fn);
                n = data_load(fn, S);
                printf("Records ard loaded to binary tree !");
                break;
            case 2: // insert
                data_insert(S);
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
    return 0;
}
