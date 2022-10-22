#include<stdio.h>
#define MAX 46

int fibos[MAX] = {0};
int fibo1(int n){
    int fib;
    //if (fibos[n]!=0) return fibos[n];
    if (n==1 || n==2) fib = 1;
    else fib = fibo1(n-1)+fibo1(n-2);
    //fibos[n] = fib;
    //fibos[n+1] = fibos[n] + fibos[n-1];
    return fib;
}
int fibo2(int n){
    int fib;
    if (fibos[n]!=0) return fibos[n];
    if (n==1 || n==2) fib = 1;
    else fib = fibo2(n-1)+fibo2(n-2);
    fibos[n] = fib;
    fibos[n+1] = fibos[n] + fibos[n-1];
    return fib;
}

void foo(int *p){
    int i,j;
    for (i=0; i<=1; i++)
        for (j=2; j<=4; j++)
            printf("%d ", p[i*6+j]);
}

int main(){
    int i,j,k;
    int m[5][3] = {{0,1,2},{3,4,5},{6,7,8},{9,10,11},{12,13,14}};
    int *p = (int *)(m+2);
    printf("%d\n", *p);
    printf("%d\n", (m+2)[1][2]);
    printf("%d\n", *(m[1]+4));
    foo(&(m[0][0]));

    int n;
    scanf("%d", &n);
    if (n<1) {
        printf("Number must be positive!\n");
        return 0;
    }
    //printf("%d th fibonacci number is %u\n", n, fibo1(n));
    printf("%d th fibonacci number is %u\n", n, fibo2(n));


    char c[3] = "++";
    printf("%s\n", c+1);

    return 0;
}