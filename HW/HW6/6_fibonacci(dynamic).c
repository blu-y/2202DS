#include <stdio.h>

int fib[100] = {0};

int fibonacci(int n){
    if (fib[n]!=0) return fib[n];
    if (n==1 || n==2) fib[n]=1;
    else fib[n] = fibonacci(n-1)+fibonacci(n-2);
    return fib[n];
}

int main(){
    int i;
    scanf("%d", &i);
    int f = fibonacci(i);
    printf("%dth fibonacci number: %d\n", i, f);
}

// dynamic programming