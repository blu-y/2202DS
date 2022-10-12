#include <stdio.h>

// 2 : main 함수를 추가하여 3x4 행렬 {{1,2,3,4},{2,3,4,5},{4,5,6,7}}과
//    4x2 행렬 {{1,2},{3,4},{5,6},{7,8}}의 곱을 계산하여 출력

void multiply_matrix(int m1[], int m2[], int m3[], int m, int n, int l) 
{
    int i, j, k;

    for (i = 0; i < m; i++)
        for (j = 0; j < l; j++) {
            m3[i*l+j] = 0;
            for (k = 0; k < n; k++)
                m3[i*l+j] += m1[i*n+k]*m2[k*l+j];
        }
}

main() {
    int a[3][4] = {{1,2,3,4},{2,3,4,5},{4,5,6,7}};
    int b[4][2] = {{1,2},{3,4},{5,6},{7,8}};
    int c[3][2];
    int m=3, n=4, l=2;
    int i, j;
    multiply_matrix(&(a[0][0]),&(b[0][0]),&(c[0][0]),m,n,l);
    for (i=0; i<m; i++){
        for (j=0; j<l; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
}


