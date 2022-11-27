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
#define NAME_SIZE 24
#define ID_SIZE 12
#define MAJ_SIZE 12
#define LINE_SIZE 48

typedef struct {
    char name[NAME_SIZE];
    char id[ID_SIZE];
    char maj[MAJ_SIZE];
} student;

int main(int argc, char* argv[]) {
    student* s = (student *)malloc(sizeof(student));
    strcpy(s->name, "Kim");
    strcpy(s->id, "88302032");
    strcpy(s->maj, "CS");
    printf("%s %s %s\n", s->name, s->id, s->maj);
    char line[LINE_SIZE];
    strcpy(line, s->name);
    strcat(line, " ");
    strcat(line, s->id);
    strcat(line, " ");
    strcat(line, s->maj);
    strcat(line, "\n");
    printf("%s", line);
    FILE* fp = fopen("test.txt.out", "w");
    fputs(line, fp);
    fputs(line, fp);
    fputs(line, fp);
    fputs(line, fp);
    fputs(line, fp);
    fclose(fp);
}
