#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void dist_count(int a[], int n) {
    int i;
    int *b, *count;
    b = (int *)malloc(sizeof(int)*n);
    count = (int *)malloc(sizeof(int)*10);
    for (i = 0; i < 10; i++) count[i] = 0;              // 0���� �ʱ�ȭ
    for (i = 0; i < n; i++) count[a[i]]++;              // �ش��ϴ� �� count
    for (i = 1; i < 10; i++) count[i] += count[i-1];    // �������� ����
    for (i = n-1; i >= 0; i--) b[--count[a[i]]] = a[i];    // b��Ŀ� ������� ����
    for (i = 0; i < n; i++) a[i] = b[i];               // a��Ŀ� b��� copy
}

int main() {
    int a[] = {9, 8, 7, 5, 1, 6, 7, 8, 6, 5, 4, 3, 1, 1, 0};
    dist_count(a, 15);
    for (int i=0; i<15; i++)
        printf("%d ", a[i]);
    printf("\n");
}

