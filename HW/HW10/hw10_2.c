/* 1. main 함수를 작성하여 배열 a[] = {'t','h','i','s','p','r','o','b','l','e','m'}을 정렬
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

unsigned bits(unsigned x, int k, int j) {
    return (x >> k) & ~(~0 << j);
}

void radix_exchange_sort(char a[], int n, int b) {
    int i, j;
    char t;
    if (n > 1  &&  b >= 0) {
        i= 0;
        j = n-1;
        while (i!= j) {
            while (bits(a[i], b, 1) == 0 && i < j) i++;
            while (bits(a[j], b, 1) != 0 && i < j) j--;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        if (bits(a[n-1], b, 1) == 0) {
                j++;
                printf("%c %d\n",a[n-1], n-1);
        }
        radix_exchange_sort(a, j, b-1);
        radix_exchange_sort(a+j, n-j, b-1);
    }
}

int main() {
    char a[] = {'t','h','i','s','p','r','o','b','l','e','m'};
    radix_exchange_sort(a, 11, 7);
    for (int i=0; i<11; i++)
        printf("%c ", a[i]);
    printf("\n");
}

/*
[thisproblem](00000000000)      n=11, b=7               print m 10
[thisproblem](11111111111)      n=11, b=6
[thisproblem](11111111111)      n=11, b=5
[thisproblem](10011100000)      n=11, b=4
    [mhielbo](1110101)          n=7, b=3
        [be](01)                n=2, b=2
            [b](1)              n=1, b=1    sorted b
            [e](0)              n=1, b=1    sorted e
        [ihlmo](00111)          n=5, b=2
            [ih](00)            n=2, b=1                print h 1
                [h](0)          n=1, b=0    sorted h
                [i](1)          n=1, b=0    sorted i
            [lmo](001)          n=3, b=1
                [lm](01)        n=2, b=0
                    [l]         n=1, b=-1   sorted l
                    [m]         n=1, b=-1   sorted m
                [o](1)          n=1, b=-1   sorted o
    [rpst](0000)                n=4, b=3                print t 3
        [rpst](0001)            n=4, b=2
            [rps](101)          n=3, b=1
                [p](0)          n=1, b=0    sorted p
                [rs](01)        n=2, b=0
                    [r]         n=1, b=-1   sorted r
                    [s]         n=1, b=-1   sorted s
            [t](0)              n=1, b=1    sorted t
>>  b e h i l m o p r s t
*/
