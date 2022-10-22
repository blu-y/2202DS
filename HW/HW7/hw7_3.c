// apply dynamic programming to part 2

#include <stdio.h>
#include <sys/time.h>

int price[] = {0,1,5,8,9,10,17,17,20,22,26};

int main() {
   struct timeval tstart, tfinish;
   double tsecs;
   int l;
   printf("Length of stick? ");
   scanf("%d", &l);
   gettimeofday(&tstart, NULL);
   int p = maxp(l);
   gettimeofday(&tfinish, NULL);
   tsecs = (tfinish.tv_sec-tstart.tv_sec) + 
      1e-6 * (tfinish.tv_usec-tstart.tv_usec); 
   printf("Maximum price:%d\n",p);
   printf("time: %f\n", tsecs);
}
