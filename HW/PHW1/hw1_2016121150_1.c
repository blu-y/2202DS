// HW1 ���� 1.
// ���ڿ��� �޾Ƽ� �ҹ��ڸ� ��� �빮�ڷ�
// �ٲپ� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
// 2016121150 ���ؿ�

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

