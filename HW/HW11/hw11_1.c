#include <stdio.h>

void upheap(int a[], int k) {
    int v = a[k];
    while (a[k/2] <= v) {
        a[k] = a[k/2];
        k /= 2;
    }
    a[k] = v;
}

void downheap(int a[], int n, int k) {
    int i, v;
    v = a[k];
    while (k <= n/2) {
        i = k<<1;
        if (i < n && a[i] < a[i+1]) i++;
        if (v >= a[i]) break;
        a[k] = a[i];
        k = i;
    }
    a[k] = v;
}

void heap_sort(int a[], int n){
    int i;
    for (i = 2; i <= n; i++) {
        upheap(a, i);
        //for (int k = 1; k <= 9; k++) printf("%d ", a[k]);
        //printf("\n");
    }
    for (i = n; i > 1; i--) {
        int v = a[1];
        a[1] = a[i];
        a[i] = v;
        downheap(a, i-1, 1);
    }
}

int main(int argc, char* argv[]) {
    int a[] = {999, 6, 5, 9, 4, 7, 1, 2, 8, 3};
    heap_sort(a, 9);
    for (int i = 1; i <= 9; i++) printf("%d ", a[i]);
    printf("\n");
}