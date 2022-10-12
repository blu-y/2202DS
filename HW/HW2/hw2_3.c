#include <stdio.h>
#include <stdlib.h>

// 3. main 함수를 작성하여 (0,0),(0,2),(1,3),(2,2),(3,0),(3,1)위치에
//    1, 2, 3, 4, 5, 6이 저장된 2차원 4X4 행렬을 희소행렬 표현으로 저장,
//    transpose 함수를 적용한 전치 행렬을 출력하는 프로그램을 작성

void matprint(int a[], int m, int l) {
    for (int i=0; i<m; i++){
        for (int j=0; j<l; j++)
            printf("%d ", a[i*l+j]);
        printf("\n");
    }
    printf("\n");
}

void transpose(int a[][3], int b[][3]) {
    int n=a[0][1]; int terms = a[0][2];
    int *s = (int *)calloc(n,sizeof(int));
    int *t = (int *)calloc(n,sizeof(int)); 
    int i,j; 
    b[0][0]=n; b[0][1]=a[0][0]; b[0][2]=terms;
    for (i=1; i<=terms; i++) s[a[i][1]]++;
    t[0] = 1;
    for (i=1; i<n; i++) t[i]=t[i-1]+s[i-1];
    for (i=1; i<=terms; i++) {
        j = t[a[i][1]];
        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];
        t[a[i][1]] = j+1;
    }
    free(s);
    free(t);
}

void transpose2(int a[][3], int b[][3]) {
    int n=a[0][1]; int terms = a[0][2];
    int s[n], t[n];
    int i,j; 
    for (i=0; i<n; i++) {
        s[i] = 0;
        t[i] = 0;
    }
    b[0][0]=n; b[0][1]=a[0][0]; b[0][2]=terms;
    for (i=1; i<=terms; i++) s[a[i][1]]++;
    t[0] = 1;
    for (i=1; i<n; i++) t[i]=t[i-1]+s[i-1];
    for (i=1; i<=terms; i++) {
        j = t[a[i][1]];
        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];
        t[a[i][1]] = j+1;
    }
}

main() {
    // 희소행렬의 크기 = (요소+1)X(차원+1) >> 7X3
    int a[7][3] = {{4,4,6},{0,0,1},{0,2,2},{1,3,3},{2,2,4},{3,0,5},{3,1,6}};
    int b[7][3];
    transpose(a, b);
    printf("transpose\n");
    matprint(&(b[0][0]), 7, 3);
    int c[7][3];
    transpose2(a, c);
    printf("transpose2\n");
    matprint(&(c[0][0]), 7, 3);
}

