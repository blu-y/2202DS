#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int min(int x, int y) {
    if (x < y) return x;
    else return y;
}

void merge(int a[], int b[], int c[], int na, int nb) {
    int i = 0, j = 0, k = 0;
    while (k < na+nb)
        if (a[i] <= b[j])
            if (i < na) c[k++] = a[i++];
            else c[k++] = b[j++];
        else
            if (j < nb) c[k++] = b[j++];
            else c[k++] = a[i++];
}

void merge_sort(int a[], int n) {
    int i, j, k, first, second, size;
    int *b = (int *)malloc(sizeof(int)*n);
    for (size = 1; size < n; size <<= 1) {
        first = 0; second = first + size;
        while (first < n) {
            merge(a+first, a+second, b+first, size, min(size, n-second));
            first = second + size; second = first + size;
        }
        for (i = 0; i < n; i++) a[i] = b[i]; /* memcpy (a, b, sizeof(int)*n); */
    }
    free(b);
}

int main(int argc, char* argv[]) {
    int a[] = {6, 5, 9, 4, 7, 1, 2, 8, 3};
    merge_sort(a, 9);
    for (int i = 0; i < 9; i++) printf("%d ", a[i]);
    printf("\n");
}