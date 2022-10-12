#include <stdio.h>

// 1 : n*n 2���� �迭�� �밢�� ������ ���� ���ϴ� �Լ��� �ۼ��϶�.
//    ans : 15, 18

int sumDiag(int *a, int n){
    int s = 0;
    int i;
    for (i = 0; i < n; i++)
        s = s + *(a + (i * n) + i);
    return s;
}

main() {
    int x[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int y[4][4] = {{1,2,3,4},{2,3,4,5},{4,5,6,7},{5,6,7,8}};

    printf("%d\n", sumDiag(&(x[0][0]), 3)); //x[0]�� ����
    printf("%d\n", sumDiag(&(y[0][0]), 4));
}
