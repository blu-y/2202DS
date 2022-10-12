// HW1 문제 1.
// 문자열을 받아서 소문자를 모두 대문자로
// 바꾸어 출력하는 프로그램을 작성하시오.
// 2016121150 윤준영

#include <stdio.h>

char upper(char i){
    // make upper letter a~z to A~Z
    // if i is 97~122 then -32
    if (i>=97 && i<=122) i = i-32;
    return i;
}

int main(){
    char s[100];
    int n = 0;
    printf("Input a string: ");
    scanf("%s", s);
    // make upper letter until end of string('\0')
    while (s[n]!='\0'){
        s[n] = upper(s[n]);
        n++;
    }
    printf("-> %s\n", s);
    return 0;
}

// Input a string: adfa223x3299aasXX123
// -> ADFA223X3299AASXX123

