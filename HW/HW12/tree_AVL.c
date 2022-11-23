#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
} node;
void init_tree(node** p) {
	*p = (node*)malloc(sizeof(node));
	(*p)->left = NULL;
	(*p)->right = NULL;
}

#define print_tree(tree) inorder_print(tree->left)
void inorder_print(node *t) {
	if (t != NULL) {
		inorder_print(t->left);
		printf("%d ",t->key);
		inorder_print(t->right);
	}
}

#define print_tree_post(tree) postorder_print(tree->left)
void postorder_print(node *t) {
	if (t != NULL) {
		postorder_print(t->left);
		postorder_print(t->right);
		printf("%d ",t->key);
	}
}

void postorder_sum(node *t) {
	if (t != NULL) {
		postorder_sum(t->left);
		postorder_sum(t->right);
		if (t->left != NULL) t->key += t->left->key;
		if (t->right != NULL) t->key += t->right->key;
		printf("%d ", t->key);
	}
}
void sum_tree(node *t) {
	postorder_sum(t->left);
	printf("\nsum: %d", t->left->key);
}

node* bti_search(int key, node* base, int* num) {
	node* s;
	s = base->left; /* base 포인터의 left child가 루트 노드 */
	while (s != NULL && key != s->key)
		/* tail 노드를 사용하지 않음. NULL 포인터로 대체 */
		if (key < s->key)
			s = s->left;
		else	s = s->right;
	return s;
}

node* bti_insert(int key, node* base, int* num) {
	node* p, * s;
	p = base;
	s = base->left;
	while (s != NULL) {
		p = s;
		if (key < s->key) s = s->left;
		else s = s->right;
	}
	if ((s = (node*)malloc(sizeof(node))) == NULL)
		return NULL;
	s->key = key;
	s->left = NULL;
	s->right = NULL;
	if (key < p->key || p == base) p->left = s;
	else
		p->right = s;
	(*num)++;
	return s;
}

main() {
	node* tree;
	int num = 0;
	init_tree(&tree);
	bti_insert(8, tree, &num);
	bti_insert(4, tree, &num);
	bti_insert(9, tree, &num);
	bti_insert(1, tree, &num);
	bti_insert(6, tree, &num);
	bti_insert(0, tree, &num);
	printf("\ninorder: ");
	print_tree(tree);

	node *tmp, *p, *s;
	p = tree->left;
	s = p->left;
	p->left = s->right;
	s->right = p;
	tree->left = s;

	printf("\ninorder(AVL): ");
	print_tree(tree);
	printf("\npostorder(AVL): ");
	print_tree_post(tree);
}