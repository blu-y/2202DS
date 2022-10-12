#include <stdio.h>

void print_arr(char s[], int n){
    // print arr
    // input : array, size of array
    for (int i=0; i<n; i++) printf("%c", s[i]);
    printf("\n");
}

char *concat(char c1[], char c2[], char c3){
    int n=0, m=0;
    while (c1[n]!='\0') n++;
    while (c2[m]!='\0'){
        c1[n+m] = c2[m];
        m++;
    }
    c1[n+m] = '\0';
    printf("%s\n", c1);
    c3 = c1;
    return c3;
}

main(){
    char s1[100];
    char s2[100];
    char *s3;
    scanf("%s", s1);
    scanf("%s", s2);
    s3 = concat(s1, s2, s3);
    printf("-->%s\n", s3);
}