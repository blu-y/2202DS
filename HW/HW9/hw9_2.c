#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define BASE(i)     ((char*)base + (i)*width)
typedef int (*FCMP)(const void*, const void*);

void bubble_sort(void *base, size_t n, size_t width,
                 int (*fcmp)(const void*, const void*)) {
    void *tmp = malloc(width);
    int i, j;
    for (i = n-1; i > 0; i--)
        for (j = 1; j <= i; j++)
            if (fcmp(BASE(j-1), BASE(j)) > 0){
                memcpy(tmp, BASE(j-1), width);
                memcpy(BASE(j-1), BASE(j), width);
                memcpy(BASE(j), tmp, width);
            }
    free(tmp);
}

int double_cmp(const void *a, const void *b){
    /* compare float */
    return (*(double *)a - *(double *)b + 1);
}

int main() {
    double a[] = {4.2, 3.4, 5.6, 1.2, 3.3, 7.7};
    bubble_sort(a, 6, sizeof(double), double_cmp);
    for (int i=0; i<6; i++)
        printf("%lf ", a[i]);
    printf("\n");
}


