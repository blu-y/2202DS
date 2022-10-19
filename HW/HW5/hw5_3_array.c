/* 배열 사용 프로그램 */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct {
        int front;
        int rear;
        int data[MAX1];
} queue;
queue * create_queue() {
   queue *q = (queue *)malloc(sizeof(queue));
   q->front = q->rear = 0;
   return q;
}

void clear_queue(queue *q) {
   q->front = q->rear;
}

int put(queue *q, int k)
{
    if ((q->rear + 1) % MAX1 == q->front) /* full */
    {
        printf("\n    Queue overflow.");
        return -1;
    }
    q->data[q->rear] = k;
    q->rear = ++q->rear % MAX1;
    return k;
}
int get(queue *q){
    int i;
    if (q->front == q->rear)   /* queue is empty */
    {
        printf("\n    Queue underflow.");
        return -1;
    }
    i= q->data[q->front];
    q->front = ++q->front % MAX1;
    return i;
}
void print_queue(queue *q)  {
    int i;
    printf("\n  Queue contents : Front ----> Rear\n");
    for (i= q->front; i!=q->rear; i= ++i% MAX1)
        printf("%-6d", q->data[i]);
}
void main(void){
    int i;
    queue *q = create_queue();
    printf("\nPut5, 4, 7, 8, 2, 1");
    put(q, 5); put(q, 4); put(q, 7);
    put(q, 8); put(q, 2); put(q, 1);
    print_queue(q);
    printf("\nGet"); i= get(q);
    print_queue(q);
    printf("\n   getting value is %d", i);
    printf("\nPut3, 2, 5, 7");
    put(q,3); put(q, 2); put(q, 5); put(q, 7);
    print_queue(q);
    printf("\nNowqueue is full, put 3");
    put(q, 3);
    print_queue(q);
    printf("\nInitializequeue");
    clear_queue(q);
    print_queue(q);
    printf("\nNowqueue is empty, get");
    i= get(q);
    print_queue(q);
    printf("\n   getting value is %d\n", i);
}