/* 일반적인 자료형을 위한 쉘 정렬 함수로 고쳐 작성 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define BASE(i)     ((char*)base + (i)*width)
typedef int (*FCMP)(const void*, const void*);

void shell_sort(int a[], int n) {
    int i, j, k, h, v;
    for (h = n/2; h > 0; h /= 2) {
	   for (i= 0; i< h; i++) {
	       for (j = i+h; j < n; j += h) {
                v = a[j];
                k = j;
                while (k > h-1 && a[k-h] > v) {
                    a[k] = a[k-h];
                    k -= h;
                }
                a[k] = v;
}}}}

int double_cmp(const void *a, const void *b){
    /* compare float */
    return (*(double *)a - *(double *)b + 1);
}

int main() {
    int a[] = {9, 8, 7, 5, 1, 6, 7, 8, 6, 5, 4, 3, 1, 1, 0};
    dist_count(a, 15);
    for (int i=0; i<15; i++)
        printf("%d ", a[i]);
    printf("\n");
}

