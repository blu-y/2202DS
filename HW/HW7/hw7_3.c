// apply dynamic programming to part 2

#include <stdio.h>

int maxprices[100] = {0}; /* 최대 가격을 일단 0으로 초기화 */
int price[] = {0,1,5,8,9,10,17,17,20,22,26};
int maxp(int m) {
   if (maxprices[m]!=0) return maxprices[m];
   int i,p;
   int max;
   int maxCut = 10;
   if (m<=0) return 0;
   if (m<=10) maxCut = m;
   max = 0;
   for (i=1; i<=maxCut; i++) {
      p = price[i] + maxp(m-i);
      if (p > max) max = p;
   }
   maxprices[m] = max;
   return max;
}

int main() {
   int l;
   printf("Length of stick? ");
   scanf("%d", &l);
   int p = maxp(l);
   printf("Maximum price:%d\n",p);
}