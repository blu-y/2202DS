// HW1 ���� 2.
// �迭 ������ �Է¹޾� ó�� �� ���� ���ڿ��� 
// ������ ���� ����° ���ڿ��� �����ϴ� �Լ� 
// concat �� �ۼ��Ͽ� ���� ���α׷��� �ϼ��Ͻÿ�.
// 2016121150 ���ؿ�

#include <stdio.h>

char *concat(char c1[], char c2[]){
    int n=0, m=0;
    //count length of c1
    while (c1[n]!='\0') n++;
    //put c2 on the end of c1
    while (c2[m]!='\0'){
        c1[n+m] = c2[m];
        m++;
    }
    //declare end of string
    c1[n+m] = '\0';
    return c1;
}

main(){
    char s1[100];
    char s2[100];
    char *s3;
    scanf("%s", s1);
    scanf("%s", s2);
    s3 = concat(s1, s2);
    printf("-->%s\n", s3);
}

// abfdf
// ffff
// -> adfdfffff


