// HW1 문제 2.
// 배열 세개를 입력받아 처음 두 개의 문자열을 
// 연결한 것을 세번째 문자열에 저장하는 함수 
// concat 를 작성하여 다음 프로그램을 완성하시오.
// 2016121150 윤준영

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


