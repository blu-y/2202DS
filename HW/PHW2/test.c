#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void input(char* s){
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}

int option(void){
    printf("���ϴ� �۾��� �����ϼ��� (1:�Է�, 2:��� ���ϱ�, 3: ���, 4:����, 0:����): ");
    char s[5];
    input(s);
    return atoi(s);
}

void test(char *s){
    FILE* fp;
    char line[MAX];
    int t;
    if ((fopen_s(&fp, s, "rb")) != NULL){
        printf("������ �����ϴ�\n");
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
                printf("���� �̸��� �Է��ϼ���: ");
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