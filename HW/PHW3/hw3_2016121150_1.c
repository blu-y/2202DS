/*  HW3 문제 1.
    힙 정렬
    Input: .txt
        Data order: 이름 학번 학과
    Output: .out
        Sort order: 학과 학번
    > HW\PHW3\hw3_2016121150_1.exe student.txt
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
    int i = 0;
    // continue until different letter appear of end of string
    while(up(a->maj[i]) == up(b->maj[i]) && up(a->maj[i]) != 0 && up(b->maj[i]) != 0) i++;
    if (up(a->maj[i]) == up(b->maj[i])) {
        i = 0;
        while (up(a->id[i]) == up(b->id[i]) && up(a->id[i]) != 0 && up(b->id[i]) != 0) i++;
        return up(a->id[i]) - up(b->id[i]);
    }
    else return up(a->maj[i]) - up(b->maj[i]);
    printf("%s", up(a->maj[i]));
}

void upheap(student* S[], int k) {
    student* v = (student *)malloc(sizeof(student));
    memcpy(v, S[k], sizeof(student));
    while (cmp(S[k/2], v) <= 0) {
        memcpy(S[k], S[k/2], sizeof(student));
        k /= 2;
    }
    memcpy(S[k], v, sizeof(student));
    free(v);
}
void downheap(student* S[], int n, int k) {
    student* v = (student *)malloc(sizeof(student));
    int i;
    memcpy(v, S[k], sizeof(student));
    while (k <= n/2) {
        i = 2*k;
        if (i < n && cmp(S[i], S[i+1]) < 0) i++;
        if (cmp(v, S[i]) >= 0) break;
        memcpy(S[k], S[i], sizeof(student));
        k = i;
    }
    memcpy(S[k], v, sizeof(student));
    free(v);
}
void heap_sort(student* S[], int n) {
    student* tmp = (student *)malloc(sizeof(student));
    for (int i = 2; i < n; i++) upheap(S, i);
    for (int i = n-1; i >= 2; i--) {
        memcpy(tmp, S[1], sizeof(student));
        memcpy(S[1], S[i], sizeof(student));
        memcpy(S[i], tmp, sizeof(student));
        downheap(S, i-1, 1);
    }
    free(tmp);
}

int loadfile(char* fn, student* S[MAX]) {
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

void savefile(char* fn, student* S[], int n) {
    FILE* fp;
    char fno[MAX];
    strcpy(fno, fn);
    strcat(fno, ".out");
    char line[LINE_SIZE];
    fopen_s(&fp, fno, "w");
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
    printf("Save complete: %s\n", fno);
}

int main(int argc, char* argv[]) {
    student* S[MAX];
    argv[1] = "student.txt";
    int n = loadfile(argv[1], S);
    heap_sort(S, n);
    // for (int i = 1; i < n; i++) {
    //     printf("%s %s %s\n", S[i]->name, S[i]->id, S[i]->maj);
    // }
    savefile(argv[1], S, n);
    return 0;
}
