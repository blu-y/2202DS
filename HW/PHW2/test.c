#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void input(char* s){
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}

int option(void){
    printf("원하는 작업을 선택하세요 (1:입력, 2:행렬 더하기, 3: 출력, 4:저장, 0:종료): ");
    char s[5];
    input(s);
    return atoi(s);
}

void test(char *s){
    FILE* fp;
    char line[MAX];
    int t;
    if ((fopen_s(&fp, s, "rb")) != NULL){
        printf("파일이 없습니다\n");
        return;
    }
    fgets(line, MAX, fp);
    printf("%s\n", line);
}

int main(void){
    char s[MAX];
    int c;
    do{
        c = option();
        switch (c){
            case 1:
                printf("파일 이름을 입력하세요: ");
                fgets(s, MAX, stdin);
                test(s);
                printf("%s", s);
                break;
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            default:
                break;
        }
    } while(c);
    printf("Bye~\n");
    return 0;
}