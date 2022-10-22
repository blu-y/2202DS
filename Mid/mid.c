#include <stdio.h>
#include <stdlib.h>
#define MAX1 3
#define MAX 10

int mat_avg(int a[0], int n){
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) sum += a[i];
    return (sum/n);
}
void mat_print(int a[], int m, int l) {
    printf("\n");
    for (int i=0; i<m; i++){
        for (int j=0; j<l; j++)
            printf("%d ", a[i*l+j]);
        printf("\n");
    }
}
int mat_sum(int m[][4], int n){
    int i, j, s = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < 4; j++)
            s = s + m[i][j];
    return s;
}
int mat_sum_ptr(int *m, int n, int l){
    int i, j, s = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < 4; j++)
            s = s + *(m+(i*l+j));
    return s;
}
void mat_mul(int m1[], int m2[], int m3[], int m, int n, int l){
    int i, j, k;
    for (i = 0; i < m; i++)
        for (j = 0; j < l; j++){
            m3[i*l+j] = 0;
            for (k = 0; k < n; k++)
                m3[i*l+j] += m1[i*n+k] * m2[k*l+j];
        }
}
void mat_sps_tp(int a[][3], int b[][3]){
    int n = a[0][1];
    int t = a[0][2];
    int col, p;
    int q = 1;
    b[0][0] = n; b[0][1] = a[0][0]; b[0][2] = t;
    if (t==0) return;
    for (col = 0; col < n; col++)
        for (p=1; p<=t; p++)
            if (a[p][1] == col){
                b[q][0] = a[p][1];
                b[q][1] = a[p][0];
                b[q][2] = a[p][2];
                q++;
            }
}
void mat_sps_tp2(int a[][3], int b[][3]){
    int n = a[0][1]; int terms = a[0][2];
    int *s = (int *)calloc(n, sizeof(int));
    int *t = (int *)calloc(n, sizeof(int));
    int i, j;
    b[0][0] = n; b[0][1] = a[0][0]; b[0][2] = terms;
    for (i = 1; i<=terms; i++) s[a[i][1]]++; // terms
    t[0] = 1;
    for (i = 1; i < n; i++) t[i] = t[i-1] + s[i-1];
    for (i = 1; i <= terms; i++){
        j = t[a[i][1]];
        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];
        t[a[i][1]] = j + 1;
    }
    free(s);
    free(t);
}
void array(void){
    // 2. Array
    int array[MAX1];
    int i;
    printf("\nInput %d integer -> ", MAX1);
    for (i = 0; i < MAX1; i++) scanf("%d", array+i);
    printf("\nAverage of %d integer is %d", MAX1, mat_avg(array,MAX1));

    int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    int b[2][4] = {{1,2,3,4},{5,6,7,8}};
    printf("\nSum of a: %d", mat_sum(a,3));
    printf("\nSum of b: %d", mat_sum(b,2));
    printf("\nSum of a: %d", mat_sum_ptr(a,3,4));
    printf("\nSum of a: %d", mat_sum_ptr(&a[0][0],3,4)); //a¡Õ&a[0][0]

    int sps[9][3] = {{6,6,8},{0,0,1},{0,4,2},{1,3,3},{2,3,4},{2,5,5},{3,0,6},{4,5,7},{5,1,8}};
    mat_print(sps, 9, 3);
    int stp[9][3]; int stp2[9][3];
    mat_sps_tp(sps, stp);
    mat_sps_tp2(sps, stp2);
    mat_print(stp, 9, 3);
    mat_print(stp2, 9, 3);
}

typedef struct _node {
    int key;
    struct _node *next;
} node;
node* list_init(void){
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));
    if (head==NULL || tail==NULL) return NULL;
    head->next = tail;
    tail->next = tail;
    printf("\nList init complete!\n");
    return head;
}
void list_print(node* h){
    h = h->next;
    printf("\nList elements: ");
    while (h != h->next){
        printf("%d ", h->key);
        h = h->next;
    }
    printf("\n");
}
node *list_empty(node *head){
    node *s, *t;
    t = head->next;
    while (t->next != t){
        s = t; t = t->next; free(s);
    }
    head->next = t;
    return head;
}
node *list_insert_after(int k, node* t){
    // insert k after node t
    node *s;
    if (!t || t->next == t) return t;
    s = (node*)malloc(sizeof(node));
    if (s==NULL) return s;
    s->key = k;
    s->next = t->next;
    t->next = s;
    return s;
}
node *list_insert_bef(node *h, int t, int k){
    // insert t before k
    while (h->next->key != k && h->next->next != h->next)
        h = h->next; //find h->next->key == k until h == tail
    if (h->next->next != h->next) list_insert_after(t, h);
    return h->next;
}
int list_del_next(node *t){
    // delete next t
    node *s;
    if (t->next->next == t->next || !t) return 0;
    s = t->next;
    t->next = t->next->next;
    free(s);
    return 1;
}
int list_del(node* h, int k){
    while (h->next->key != k && h->next != h) h = h->next;
    return (list_del_next(h));
}
node *list_find(node* head, int k){
    node *s;
    if (!head) return head;
    s = head->next;
    while(s->key != k && s->next != s) s = s->next;
    // until s->key == k or s == tail
    return s;
}
typedef struct _dnode{
    int key;
    struct _dnode *prev;
    struct _dnode *next;
} dnode;
void list(void){
    // 3. List
    node *h1 = list_init();
    node *s1;
    list_insert_after(1, h1);
    list_insert_after(2, h1);
    list_insert_after(3, h1);
    list_print(h1); // h1 -> 3 -> 2 -> 1 -> t
    list_del_next(h1->next->next);
    list_print(h1); // h1 -> 3 -> 2 -> t
    s1 = list_find(h1, 2);
    printf("found: %d\n", s1->key);
    list_del(h1, 2);
    list_print(h1); // h1 -> 3 -> t
    list_insert_bef(h1, 1, 3);
    list_print(h1); // h1 -> 1-> 3 -> t
}

int stack[MAX];
int top;
void stack_init(void){
    top = -1;
}
int stack_push(int t){
    if (top >= MAX -1){
        printf("\n  Stack overflow\n");
        return -1;
    }
    stack[++top] = t;
    return t;
}
int stack_pop(void){
    if (top<0){
        printf("\n  Stack underflow\n");
        return -1;
    }
    return stack[top--];
}
void stack_print(void){
    int i;
    printf("\n  Stack contents : Top --> Bottom\n");
    for (i = top; i >= 0; i--)  printf("%-6d", stack[i]);
}
void stack_(void){
}

int main(void){
    array();
    list();
    return 0;
}