#include <stdio.h>

int price[] = {0,1,5,8,9,10,17,17,20,22,26};
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

int main() {
   int l;
   printf("Length of stick? ");
   scanf("%d", &l);
   int p = maxp(l);
   printf("Maximum price:%d\n",p);
   return 0;
}
