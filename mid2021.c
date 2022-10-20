#include <stdio.h>
#define MaxCut 5
int price[] = {0,1,5,8,9,10};
int maxprices[101] = {0};
int *cut;
int maxp(int m){
    int i,p;
    int max;
    int maxCut = MaxCut;
    int t=0;
    if(m<=0) return 0;
    if (m<MaxCut) maxCut = m;
    max = 0;
    for (i=1; i<=maxCut; i++){
        p = price[i]+maxp(m-1);
        if (p>max){
            max = p;
        }
    }
    return max;
}
int main(){
    int i, len;
    printf("Length of stick? ");
    scanf("%d", &len);
    int p = maxp(len);
    printf("%d\n",p);
    return 0;
}