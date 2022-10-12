#include <stdio.h>
#include <sys/time.h>

int foo1(int a[], int n) {
    int i, j;
    int s = 0;
    for (i=1; i<=n; i=i+1) {
        for (j=0; j<i; j++)
            s+=a[j];
    }
    return s;
}

main() {
    struct timeval tstart, tfinish;
    double tsecs;
    int x[1000];
    int i;
    int r=0;
    for (i=0; i<1000; i++)
        x[i] = i;
    gettimeofday(&tstart, NULL);
    r = foo1(x, 1000);
    gettimeofday(&tfinish, NULL);
    tsecs = (tfinish.tv_sec-tstart.tv_sec) + 
        1e-6 * (tfinish.tv_usec-tstart.tv_usec);
    printf("time: %f\n", tsecs);
    printf("value: %d\n", r);

    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    int array2[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    printf("%d\n", (array+2)[3]);
    // 6
    printf("%d\n", (array2+1)[1][2]);
    // 11

    int a[3][4][5];
    int *b = &(a[0][0][0]);
    if ( &(a[1][3][2]) == b + 37)
        printf("Hello");
        // 1*(4*5)+3*(5)+2 = 20+15+2 = 37
    
}
