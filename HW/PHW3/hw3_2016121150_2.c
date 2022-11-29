/*  HW3 문제 2.
    레코드를 이진검색나무에 저장하고 관리
    (1.load, 2.insert, 3.find, 4.delete, 5.save)
    Input: .txt
        Data order: 이름 학번 전공
    Output: .out
        Sort order: 학번
    2016121150 윤준영 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define NAME_SIZE 12
#define ID_SIZE 12
#define MAJ_SIZE 12
#define LINE_SIZE 36

typedef struct _stdt {
    char name[NAME_SIZE];
    int id;
    char maj[MAJ_SIZE];
    struct _stdt* left;
    struct _stdt* right;
} stdt;

int digit(int i) {
    int digit = 0;
    while (i != 0) {
        i = i/10;
        ++digit;
    }
    return digit;
}
int up(int i) {
    // upper letter
    if (i >=97 && i <= 122) i -=32;
    return i;
}
int idcmp(stdt* a, stdt* b) {
    return a->id - b->id;
}
void input(char* s){
    /* get string and delete new_line */
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
}
int str2int(void){
    /* get integer using input function */
    char s[ID_SIZE];
    input(s);
    return atoi(s);
}
void bintree_init(stdt** s) {
    *s = (stdt *)malloc(sizeof(stdt));
    (*s)->id = INT_MAX;
    (*s)->left = NULL;
    (*s)->right = NULL;
}

int data_insert(stdt* S, stdt* s, int n) {
    stdt* c = S;    // child
    stdt* p;        // parent
    while (c != NULL) {
        // go left if c>s, go right if c<s
        p = c;
        if (idcmp(c, s) > 0) c = c->left;
        else c = c->right;
    }
    s->left = NULL;
    s->right = NULL;
    if (idcmp(p, s) > 0) p->left = s;
    else p->right = s;
    return ++n;
}
int data_load(char* fn, stdt* S) {
    // input: file name, student struct array
    // output: number of student
    FILE* fp;
    stdt* s;
    char line[LINE_SIZE];
    char *lp;
    int i = 0;
    if ((fopen_s(&fp, fn, "r")) != NULL) {
        printf("\nWrong File!");
        return i;
    } // return 0 no file
    while(!feof(fp)) {
        fgets(line, sizeof(line), fp);
        // remove \n if exist
        if (line[strlen(line)-1] == 10) line[strlen(line)-1] = 0;
        s = (stdt *)malloc(sizeof(stdt));
        //printf("%s\n", &line);
        lp = strtok(line, " ");     // get name
        strcpy(s->name, lp);
        lp = strtok(NULL, " ");     // get id
        s->id = atoi(lp);
        lp = strtok(NULL, " ");     // get major
        strcpy(s->maj, lp);
        s->left = NULL;
        s->right = NULL;
        i = data_insert(S, s, i);
    }
    fclose(fp);
    printf("Records ard loaded to binary tree !");
    return i;
}
void inorder_print(stdt* s) {
    while (s != NULL) {
        inorder_print(s->left);
        printf("%s %d %s\n", s->name, s->id, s->maj);
        inorder_print(s->right);
        return;
    }
}
int inorder_save(FILE* fp, stdt* s, int n) {
    char l1[LINE_SIZE];
    char l2[LINE_SIZE];
    char zero[ID_SIZE] = "00000000";
    while (s != NULL) {
        n = inorder_save(fp, s->left, n);
        sprintf(l1, "%s ", s->name);
        strncat(l1, zero, 8-digit(s->id));
        sprintf(l2, "%d %s", s->id, s->maj);
        strcat(l1, l2);
        if (n!=1) strcat(l1, "\n");
        fputs(l1, fp);
        n = n-1;
        n = inorder_save(fp, s->right, n);
        return n;
    }
    return n;
}
void data_save(char* fn, stdt* S, int n) {
    FILE* fp;
    char line[LINE_SIZE];
    fopen_s(&fp, fn, "w");
    inorder_save(fp, S, n);
    fclose(fp);
    printf("%d records are saved in %s!", n, fn);
}
void data_find(stdt* S, int id) {
    stdt* s = S->left;
    while (s != NULL) {
        if (s->id == id) {
            printf("found! : [%s %d %s]", s->name, s->id, s->maj);
            return;
        } 
        if (s->id > id) s = s->left;
        else s = s->right;
    }
    printf("[%d] is not found.", id);
}
int data_delete(stdt* S, int id, int n) {
    stdt* p = S;
    stdt* s = S->left;
    stdt* des;
    int d = -1;
    while (s != NULL) {
        if (s->id == id) {
            printf("[%s %d %s] is deleted!", s->name, s->id, s->maj);
            if (s->right == NULL) {
                if (d == 1) p->right = s->left;
                else p->left = s->left;
            }
            else if (s->right->left == NULL) {
                s->right->left = s->left;
                if (d == 1) p->right = s->right;
                else p->left = s->right;
            }
            else {
                des = s->right;
                while (des->left->left != NULL) des = des->left;
                if (d == 1) p->right = des->left;
                else p->left = des->left;
                des->left->left = s->left;
                des->left = des->left->right;
            }
            free(s);
            return --n;
        } 
        else if (s->id > id) {
            p = s;
            s = s->left;
            d = -1;
        }
        else {
            p = s;
            s = s->right;
            d = 1;
        }
    }
    printf("[%d] is not found", id);
    return n;
}

int main(void) {
    stdt* S;
    stdt* s = (stdt *)malloc(sizeof(stdt));
    bintree_init(&S);
    int c = 0;
    int n = 0;
    int id;
    char fn[MAX];
    do {
        printf("\n Select one (1:load, 2:insert, 3:find, 4:delete, 5:Save, 6:Quit) : ");
        c = str2int();
        switch (c) {
            case 1: // load
                printf("Input file name : ");
                input(fn);
                n = data_load(fn, S);
                break;
            case 2: // insert
                printf("Input Name : ");
                input(s->name);
                printf("Input Id : ");
                s->id = str2int();
                printf("Input Major : ");
                input(s->maj);
                n = data_insert(S, s, n);
                printf("Data Inserted!");
                break;
            case 3: // find
                printf("Input Id : ");
                id = str2int();
                data_find(S, id);
                break;
            case 4: // delete
                printf("Input Id : ");
                id = str2int();
                n = data_delete(S, id, n);
                break;
            case 5: // Save
                printf("Input file name : ");
                input(fn);
                data_save(fn, S->left, n);
                break;
            case 9:
                inorder_print(S->left);
                printf("number of id: %d", n);
                break;
            default:
                break;
        }
    } while (c != 6);
    printf("Good bye~\n");
    return 0;
}
