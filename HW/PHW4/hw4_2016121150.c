/*  HW4 문제 1.
    Dijkstra 알고리즘을 사용하여,
    0 노드에서 다른 노드들까지의 최단거리 계산
    Input: .txt
        no. of node
        0 1 50
        0 2 10
        0 4 45
        ...
    Output: 
        0 --> 1 : 45
        0 --> 2 : 10
        0 --> 3 : 25
        ...
    > HW\PHW4\hw4_2016121150.exe graph.txt
    2016121150 윤준영 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 16

int* loadfile(char* fn, int* n) {
    // input: file name, student struct array
    // output: number of student
    FILE* fp;
    char line[LINE_SIZE];
    char *lp;
    *n = 0;
    int a, b, c;
    if ((fopen_s(&fp, fn, "r")) != NULL) {
        printf("\nWrong File!");
        return NULL;
    } // return NULL, no file
    fgets(line, sizeof(line), fp);
    if (line[strlen(line)-1] == 10) line[strlen(line)-1] = 0;
    // remove \n if exist
    *n = atoi(line);
    int *cost = (int *)calloc((*n)*(*n), sizeof(int));
    // make cost matrix
    while(1) {
        fgets(line, sizeof(line), fp);
        if (line[strlen(line)-1] == 10) line[strlen(line)-1] = 0;
        // remove \n if exist
        //printf("%s\n", &line);
        lp = strtok(line, " ");     // get src
        a = atoi(lp);
        lp = strtok(NULL, " ");     // get dst
        b = atoi(lp);
        lp = strtok(NULL, " ");     // get cost
        c = atoi(lp);
        cost[a*(*n)+b] = c;
        if (feof(fp)) break;
    }
    fclose(fp);
    return cost;
}

void printcost(int* cost, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", cost[i*n+j]);
        printf("\n");
    }
}

int* getcost(int* cost, int n, int s){
    int* found = (int *)calloc(n, sizeof(int));
    int* dist = (int *)calloc(n, sizeof(int));
    found[s] = 1;
    int j;
    for (j = 0; j < n; j++) dist[j] = cost[j+s*n];
    int sf = 0;
    int osf = 0;
    int min;
    int i;
    while (sf < n) {
        // while sum of found < n
        min = INT_MAX;
        i = -1;
        for (j = 0; j < n; j++)
        // find minimum dist in which found is false
            if (!found[j] && dist[j] && dist[j] <= min){
            // if found is false and dist is not 0 and minimum, update min and index i
                min = dist[j];
                i = j;
            }
        if (i != -1){
            found[i] = 1;
            for (j = 0; j < n; j++)
                if (cost[i*n+j] && s!=j && (!dist[j] || dist[i]+cost[i*n+j] < dist[j]))
                // if cost[i][j] don't exists, skip
                // if s = j, skip
                // if dist is 0(MAX), update
                // if dist[i]+cost[i][j] < dist[j], update
                    dist[j] = dist[i] + cost[i*n+j];
        }
        osf = sf;
        sf = 0;
        for (j = 0; j < n; j++) sf += found[j];
        if (osf == sf) break;
        // update sum of found
        // if found array is not changed, break
    }
    for (j = 0; j < n; j++) {
        cost[j+s*n] = dist[j];
        if (s!=j) {
            if (dist[j]) printf("%d --> %d : %d\n", s, j, dist[j]);
            else printf("%d --> %d : No path\n", s, j);
        }
    }
    return cost;
}

int main(int argc, char* argv[]) {
    int n;
    int* cost = loadfile(argv[1], &n);
    //printcost(cost, n);
    cost = getcost(cost, n, 0);
    return 0;
}
