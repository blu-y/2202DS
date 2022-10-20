#include<stdio.h>

int value(int mat[][3], int i, int j){
    int v = 0;
    int k = 1;
    while(mat[k][0]!=i||mat[k][1]!=j){
        k++;
        if (k==mat[0][2]+1) break;
    }
    if (k != mat[0][2]+1) v = mat[k][2];
    return v;
}

int sum(int *a, int n){
    int s=0;
    for (int i=0; i<n; i++) s+= *(a+(i*n)+i);
    return s;
}

int main(){
    int i,j,k;
    int mat[][3] = {{3,4,4},{0,0,3},{1,3,5},{2,1,8},{2,3,7}};
    k = 1;
    for (i=0; i<mat[0][0]; i++){
        for (j=0; j<mat[0][1]; j++)
        if ((k<=mat[0][2])&&(mat[k][0]==i)&&(mat[k][1]==j))
            printf("%d ", mat[k++][2]);
        else printf("0 ");
        printf("\n");
    }
    printf("mat[%d][%d]: %d\n", 1, 2, value(mat,1,2));
    printf("mat[%d][%d]: %d\n", 2, 1, value(mat,2,1));
    printf("mat[%d][%d]: %d\n", 2, 3, value(mat,2,3));

    int a[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
    int b[4][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
    printf("%d\n", sum(a, 3));
    printf("%d\n", sum(b, 4));

}