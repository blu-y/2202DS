#include <stdio.h>
#include <sys/time.h>

int price[] = {0,1,5,8,9,10,17,17,20,22,26};
int maxprices[100] = {0}; /* 최대 가격을 일단 0으로 초기화 */
int maxp(int m) {
   int i,p;
   int max; //최대 가격
   int maxCut = 10;
   if (m<=0) return 0;
   if (m<=10) maxCut = m;
   max = 0;
   for (i=1; i<=maxCut; i++) {  
      p = price[i] + maxp(m-i);
      if (p > max) max = p;
   }
   return max;
}

int maxp2(int m) {
   if (maxprices[m]!=0) return maxprices[m];
   int i,p;
   int max;
   int maxCut = 10;
   if (m<=0) return 0;
   if (m<=10) maxCut = m;
   max = 0;
   for (i=1; i<=maxCut; i++) {
      p = price[i] + maxp2(m-i);
      if (p > max) max = p;
   }
   maxprices[m] = max;
   return max;
}

int main() {
   struct timeval tstart1, tfinish1;
   struct timeval tstart2, tfinish2;
   double tsecs1, tsecs2;
   int l;
   printf("Length of stick? ");
   scanf("%d", &l);
   gettimeofday(&tstart1, NULL);
   int p = maxp(l);
   gettimeofday(&tfinish1, NULL);
   tsecs1 = (tfinish1.tv_sec-tstart1.tv_sec) + 
      1e-6 * (tfinish1.tv_usec-tstart1.tv_usec); 
   printf("Maximum price:%d\n",p);
   printf("time: %f\n", tsecs1);
   gettimeofday(&tstart2, NULL);
   int q = maxp2(l);
   gettimeofday(&tfinish2, NULL);
   tsecs2 = (tfinish2.tv_sec-tstart2.tv_sec) + 
      1e-6 * (tfinish2.tv_usec-tstart2.tv_usec); 
   printf("Maximum price(dynamic):%d\n",q);
   printf("time(dynamic): %f\n", tsecs2);
   return 0;
}
