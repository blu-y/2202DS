#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int bi_search(int key, int a[], int n) {
	int mid;
	int left = 0;
    int right = n-1;
    int ex=1;
    while (right >= left) {
        mid = (right + left) / 2;
        if (key == a[mid]) {
            printf("%d의 위치 : %d (검사 %d번)\n", key, mid, ex);
            return mid;
        }
        if (key < a[mid]) right = mid - 1;
        else left = mid + 1;
        ex++;
    }
    printf("%d의 위치 : 없음\n", key);
    return -1;
}

int bi_insert(int key, int a[], int *np) {
    int p = 0;
    int i;
    while (key > a[p] && p < *np) p++;
    if (key == a[p]) return -1; // 중복일 경우 -1 반환
    else {
        for (i = *np; i > p; i--) a[i] = a[i-1];
        a[p] = key;
        (*np)++;
        return p;
    }
}

main() {
    int a[1000] = {1000};
    int n = 0;
    int i;
	srand(time(NULL));
	for (i = 0; i < 1000; i++) bi_insert(rand()%1000, a, &n);
    // for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nlength of array : %d\n",n);
    bi_search(111, a, n);
    bi_search(222, a, n);
    bi_search(333, a, n);
    bi_search(444, a, n);
    bi_search(555, a, n);
}