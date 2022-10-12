// HW1 문제 3.
// 2x2 행렬 두 개를 받아서 두 행렬의 곱을 
// 다음과 같이 출력하는 프로그램을 작성하시오.
// 2016121150 윤준영

#include <stdio.h>

void matgen(int a[], int m, int l) {
    for (int i=0; i<m; i++){
        for (int j=0; j<l; j++)
            scanf("%d", &(a[i*l+j]));
    }
}

void matprint(int a[], int m, int l) {
    for (int i=0; i<m; i++){
        for (int j=0; j<l; j++)
            printf("%d ", a[i*l+j]);
        printf("\n");
    }
}

void matmul(int m1[], int m2[], int m3[], int m, int n, int l) 
{
    int i, j, k;
    for (i=0; i<m; i++)
        for (j=0; j<l; j++) {
            m3[i*l+j] = 0;
            for (k=0; k<n; k++)
            m3[i*l+j] += m1[i*n+k]*m2[k*l+j];
        }
}

int main(){
    int a[2][2];
    int b[2][2];
    int c[2][2];
    printf("Input elements of the first 2x2 matrix: ");
    matgen(&(a[0][0]), 2, 2);
    printf("Input elements of the second 2x2 matrix: ");
    matgen(&(b[0][0]), 2, 2);
    matmul(&(a[0][0]),&(b[0][0]),&(c[0][0]),2,2,2);
    matprint(&(c[0][0]), 2, 2);
    return 0;
}

// Input elements of the first 2x2 matrix: 1 3 2 4
// Input elements of the second 2x2 matrix: 1 2 2 1
// The result of multiplication
// 7 5 
// 10 8

