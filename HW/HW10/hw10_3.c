#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define BASE(i)     ((char*)base + (i)*width)
typedef int (*FCMP)(const void*, const void*);


void shell_sort(void *base, size_t n, size_t width,
                int (*fcmp)(const void*, const void*)){
    void *v = malloc(width);
    int i, j, k, h;
    for (h = n/2; h > 0; h /= 2) {
	   for (i= 0; i< h; i++) {
	       for (j = i+h; j < n; j += h) {
                memcpy(v, BASE(j), width);
                k = j;
                while (k > h-1 && fcmp(BASE(k-h), v)>0) {
                    memcpy(BASE(k), BASE(k-h), width);
                    k -= h;
                }
                memcpy(BASE(k), v, width);
}}}}

int int_cmp(const void *a, const void *b){
    /* compare float */
    return (*(int *)a - *(int *)b);
}

int double_cmp(const void *a, const void *b){
    /* compare float */
    return (*(double *)a - *(double *)b + 1);
}

int main() {
    int a[] = {9, 8, 7, 5, 1, 6, 7, 8, 6, 5, 4, 3, 1, 1, 0};
    shell_sort(a, 15, sizeof(int), int_cmp);
    for (int i=0; i<15; i++)
        printf("%d ", a[i]);
    printf("\n");

    double b[] = {4.2, 3.4, 5.6, 1.2, 3.3, 7.7};
    shell_sort(b, 6, sizeof(double), double_cmp);
    for (int i=0; i<6; i++)
        printf("%lf ", b[i]);
    printf("\n");
}

