// HW2 문제 2.
// x에 대한 함수를 후위 표기법으로 수식나무에 저장
// 1. 입력(저장), 2. 함수값 계산, 3. 중위식 출력, 4.종료
// (x의 값과 계산 결과는 정수형)
// 2016121150 윤준영

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct _node *nodeptr;
typedef struct _node {
    /* define node struct */
    char val;
    nodeptr left;
    nodeptr right;
} node;

typedef struct _hnode {
    nodeptr stack[MAX];
    int top;
    nodeptr tree;
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
} /* true if i is an operator, else 0 */

int num(int i){
    if (i >= 48 && i <= 57) return i-48;
    else return i;
} /* make str number to int */

nodeptr pop(hnode *h){
    if (h->top == -1){
        printf("Stack underflow!\n");
        return NULL;
    }
    return h->stack[h->top--];
} /* pop top node, top-- */

void push(node *a, hnode *h){
    if (h->top == 99){
        printf("Stack overflow!\n");
        return;
    }
    h->stack[++h->top] = a;
} /* top ++, push node to top*/

void parse_tree(char *s, hnode *h){
    node *n;
    node *tail = h->tree;
    h->top = -1;
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
    l = l-48;
    r = r-48;
    if (n->val == '+') return l + r + 48;
    if (n->val == '-') return l - r + 48;
    if (n->val == '*') return l * r + 48;
    if (n->val == '/') return l / r + 48;
}

int parse_tree_calc(int x, node *t){
    /* 1. if t is not leaf (if t->left and t-> right is not same(tail)),
          then it is operator: calculate chilren first
       2. if t is a leaf:
         2-1. if t->val is x, return x
         2-2. if t->val is number, return number
    */
    if (t->left != t->right){
        int l = parse_tree_calc(x, t->left);
        int r = parse_tree_calc(x, t->right);
        return operate(t, l, r);
    }
    if (t->val == 'x') return x+48;
    else{
        return t->val;
    }
}

int order(int s){
    /* return order of operator
       order : num >> * > / >> + > -
    */
    if (is_operator(s)){
        if (s == '*') return 5;
        if (s == '/') return 4;
        if (s == '+') return 2;
        if (s == '-') return 1;
    }
    return 9;
}

void parse_tree_inorder(node *t, int b){
    if (!((t->left == t) && (t->right == t))){
        if (b) printf("( ");
        parse_tree_inorder(t->left, order(t->val) > (order(t->left->val)+1));
        printf("%c ", t->val);
        parse_tree_inorder(t->right, order(t->val) >= order(t->right->val));
        if (b) printf(") ");
    }
}

int main(void){
    int stack[MAX] = {0};
    hnode *h1 = tree_init();
    int c;
    char fx[MAX];
    int x;
    int result;
    do{
        printf("> 원하는 연산을 선택하세요 (1:f(x)입력, 2:함수값 계산, 3:중위식 출력, 4:종료): ");
        c = str2int();
        switch (c){
            case 1:
                printf("함수 f(x)를 후위식으로 입력하세요: ");
                input(fx);
                parse_tree(fx, h1);
                break;
            case 2:
                printf("x값을 을 입력하세요: ");
                x = str2int();
                result = parse_tree_calc(x, h1->tree);
                printf("f(%d) = %d\n", x, result-48);
                break;
            case 3:
                printf("f(x) = ");
                parse_tree_inorder(h1->tree, 0);
                printf("\n");
                break;
            default:
                break;
        }
    } while(c != 4); // if input is 4
    printf("Bye~\n");
    return 0;
}

/*
> 원하는 연산을 선택하시오 (1:f(x)입력, 2:함수값 계산, 3:중위식 출력, 4:종료): 1
함수 f(x)를 후위식으로 입력하세요: x x * x 2 - * 3 x * + x 1 - -
> 원하는 연산을 선택하시오 (1:f(x)입력, 2:함수값 계산, 3:중위식 출력, 4:종료): 2
x값을 입력하세요: 3
f(3) = 16
> 원하는 연산을 선택하시오 (1:f(x)입력, 2:함수값 계산, 3:중위식 출력, 4:종료): 2
x값을 입력하세요: 4
f(4) = 41
> 원하는 연산을 선택하시오 (1:f(x)입력, 2:함수값 계산, 3:중위식 출력, 4:종료): 3
f(x) = x * x * (x - 2) + 3* x - (x - 1)
> 원하는 연산을 선택하시오 (1:f(x)입력, 2:함수값 계산, 3:중위식 출력, 4:종료): 4
Bye~
*/