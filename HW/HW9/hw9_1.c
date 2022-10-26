#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define BASE(i)     ((char*)base + (i)*width)
typedef int (*FCMP)(const void*, const void*);

void select_sort(void *base,size_t nelem,size_t width,
                    int (*fcmp)(const void*, const void*)) {
    void *min;
    int minindex, i, j;
    min = malloc(width);
    for (i = 0; i < nelem - 1; i++)     {
            minindex = i;
            for (j = i + 1; j < nelem; j++)
                if (fcmp(BASE(minindex), BASE(j)) > 0)
                    minindex = j;
            memcpy(min, BASE(minindex), width);
            memcpy(BASE(minindex), BASE(i), width);
            memcpy(BASE(i), min, width);
         }
    free(min);
}
// 함수 추가 필요



int main() {
   double a[] = {4.2, 3.4, 5.6, 1.2, 3.3, 7.7};

   // select_sort 함수 호출 필요

   
   for (int i=0; i<6; i++)
        printf("%lf ", a[i]);
   printf("\n");
}