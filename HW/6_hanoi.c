#include <stdio.h>

void move(int from, int to){
    printf("\nMove from %d to %d", from, to);
}
void hanoi(int n, int from, int by, int to){
    if (n==1) move(from, to);
    else{
        hanoi(n-1, from, to, by);
        move(from, to);
        hanoi(n-1, by, from, to);
    }
}
void main(void){
    int i;
    printf("\nEnter height of HANOI tower -> ");
    scanf("%d", &i);
    if (i>0) hanoi(i, 1, 2, 3);
}