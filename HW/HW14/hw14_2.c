#include <stdlib.h>
#include <stdio.h>
#define MAX_VERTICES 7
#define MAX INT_MAX

void allcosts(int cost[][MAX_VERTICES], 
                 int distance[][MAX_VERTICES], int n){
/* 각 정점에서 다른 모든 정점으로의 거리 계산,cost:인접 행렬, distance:거리값*/
    int i, j, k;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            distance[i][j] = cost[i][j];
    for (k=0; k<n; k++)
        for (i=0; i<n; i++)  
            for (j=0; j<n; j++)
                if (distance[i][k]+distance[k][j] < distance[i][j])
                    if (distance[i][k] != MAX && distance[k][j] != MAX){
                        distance[i][j] = distance[i][k] + distance[k][j];
                        printf("%d-%d-%d:%d\n",i,k,j,distance[i][j]);
                    }
}

int main(void) {
    int cost[7][7] = {{0, 7, 9, 3, MAX, MAX, MAX},
                      {MAX, 0, 1, MAX, 6, 9, MAX},
                      {MAX, MAX, 0, MAX, MAX, MAX, MAX},
                      {MAX, 2, MAX, 0, 11, MAX, MAX},
                      {MAX, MAX, MAX, MAX, 0, 2, 1},
                      {MAX, MAX, 1, MAX, MAX, 0, MAX},
                      {9, MAX, MAX, MAX, MAX, MAX, 0}};
    int dist[7][7];
    int n = 7;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (i!=j && cost[i][j]!=MAX)
                printf("%d->%d : %d\n", i, j, cost[i][j]);
    printf("\nallcosts\n");
    allcosts(cost, dist, n);
    printf("\nallcosts\n");
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (i!=j && dist[i][j]!=MAX)
                printf("%d->%d : %d\n", i, j, dist[i][j]);
    return 0;
}

