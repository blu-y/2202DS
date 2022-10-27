// HW2 ���� 2.
// x�� ���� �Լ��� ���� ǥ������� ���ĳ����� ����
// 1. �Է�(����), 2. �Լ��� ���, 3. ������ ���, 4.����
// (x�� ���� ��� ����� ������)
// 2016121150 ���ؿ�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct _node {
    /* define node struct */
    int val;
    struct _node *left;
    struct _node *right;
} node;

typedef struct _hnode {
    node* stack[MAX];
    int top;
    struct _node *tree;
} hnode;

hnode* tree_init(void){
    /* initialize list
       return : list head node
    */
    hnode *head = (hnode*)malloc(sizeof(hnode));
    node *tail = (node*)malloc(sizeof(node));
    if (head==NULL || tail==NULL) return NULL;
    // if memory allocation fail, return NULL
    head->top = -1;
    head->tree = tail;
    tail->left = tail;
    tail->right = tail;
    return head;
}

void input(char* s){
    /* get string and delete new_line */
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}

int str2int(void){
    /* get integer using input function */
    char s[5];
    input(s);
    return atoi(s);
}

int is_operator(int i){
    return (i == '+' || i == '-' || i == '*' || i == '/');
}

int is_num(int i){
    if (i >= 48 && i <= 57) return i-48;
    else return i;
}

node* pop(hnode *h){
    if (h->top == -1){
        printf("Stack underflow!\n");
        return NULL;
    }
    node* ret = h->stack[h->top];
    h->top -= 1;
}

void push(node *a, hnode *h){
    if (h->top == 99){
        printf("Stack overflow!\n");
        return;
    }
    h->top += 1;
    h->stack[h->top] = a;
}

void parse_tree(char *s, hnode *h){
    node *n;
    node *tail = h->tree;
    while(*s){
        while (*s == ' ') s++; // skip ' '
        n = (node*)malloc(sizeof(node));
        n->val = *s;
        n->left = tail;
        n->right = tail;
        if (is_operator(*s)){
            n->right = pop(h);
            n->left = pop(h);
        }
        push(n, h);
        s++;
    }
    h->tree = pop(h);
}

int operate(node *n, int l, int r){
    if (n->val == '+') return l + r;
    if (n->val == '-') return l - r;
    if (n->val == '*') return l * r;
    if (n->val == '/') return l / r;
}

int parse_tree_calc(int x, node *t){
    /* 1. if t is not leaf (if t->left and t-> right is not same(tail)),
          then it is operator: calculate chilren first
       2. if t is a leaf:
         2-1. if t->val is x, return x
         2-2. if t->val is number, return number
    */
    int ret = 0;
    int l = 0;
    int r = 0;
    // �������� ��
    if (t->left != t->right){
        printf("one %d ", ret);
        l = parse_tree_calc(x, t->left);
        r = parse_tree_calc(x, t->right);
        ret = operate(t, l, r);
        printf("one %d ", ret);
        return ret;
    }
    if (t->val == 'x'){
        printf("two %d ", x);
        return x;
    }
    else{
        printf("three %d ", t->val);
        return t->val;
    }
}

void parse_tree_pre2in(hnode *h, char *fx){



    printf("f(x) = %s\n", fx);
}

int main(void){
    int stack[MAX] = {0};
    hnode *h1 = tree_init();
    int c;
    char fx[MAX];
    char fx2[MAX];
    int x;
    int result;
    do{
        printf("> ���ϴ� ������ �����ϼ��� (1:f(x)�Է�, 2:�Լ��� ���, 3:������ ���, 4:����): ");
        c = str2int();
        switch (c){
            case 1:
                printf("�Լ� f(x)�� ���������� �Է��ϼ���: ");
                input(fx);
                parse_tree(fx, h1);
                break;
            case 2:
                printf("x���� �� �Է��ϼ���: ");
                x = str2int();
                result = parse_tree_calc(x, h1->tree);
                printf("f(%d) = %d\n", x, result);
                break;
            case 3:
                parse_tree_pre2in(h1, fx2);
                break;
            default:
                break;
        }
    } while(c != 4); // if input is 4
    printf("Bye~\n");
    return 0;
}

/*
> ���ϴ� ������ �����Ͻÿ� (1:f(x)�Է�, 2:�Լ��� ���, 3:������ ���, 4:����): 1
�Լ� f(x)�� ���������� �Է��ϼ���: x x * x 2 - * 3 x * + x 1 - -
> ���ϴ� ������ �����Ͻÿ� (1:f(x)�Է�, 2:�Լ��� ���, 3:������ ���, 4:����): 2
x���� �Է��ϼ���: 3
f(3) = 16
> ���ϴ� ������ �����Ͻÿ� (1:f(x)�Է�, 2:�Լ��� ���, 3:������ ���, 4:����): 2
x���� �Է��ϼ���: 4
f(4) = 31
> ���ϴ� ������ �����Ͻÿ� (1:f(x)�Է�, 2:�Լ��� ���, 3:������ ���, 4:����): 3
f(x) = x * x * (x - 2) + 3* x - (x - 1)
> ���ϴ� ������ �����Ͻÿ� (1:f(x)�Է�, 2:�Լ��� ���, 3:������ ���, 4:����): 4
Bye~
*/

