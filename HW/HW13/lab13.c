/*                                                           */
/*  SCHASH1.C  :  Example of separate chaining hash           */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct _node
{
	int key;
	struct _node* next;
} node;

int hash_func(int key)
{
	int h;
	h = key / TABLE_SIZE + key % TABLE_SIZE;
	h = h % TABLE_SIZE;
	return h;
}

node* hsc_search(int key, node a[], int* np)
{
	node* t;
	int b = hash_func(key);
	t = a[b].next;
	int n = 0;
	while (t != NULL && t->key != key) {
		t = t->next;
		n += 1;
		}
	if (t != NULL) printf("%d번째 버킷 %d번째 노드에 있음", b, n);
	else printf("%d없음", key);
	return t;
}

node* hsc_insert(int key, node a[], int* np)
{
	int try;
	node* t;
	t = (node*)malloc(sizeof(node));
	try = hash_func(key);
	t->next = a[try].next;
	t->key = key;
	a[try].next = t;
	(*np)++;
	return t;
}

node* hsc_delete(int key, node a[], int* np)
{
	node* p;
	node* t;
	if (*np > 0)
	{
		p = &a[hash_func(key)];
		t = p->next;
		while (t != NULL && t->key != key)
		{
			p = t;
			t = t->next;
		}
		if (t == NULL) return NULL;
		p->next = t->next;
		free(t);
		(*np)--;
		return p;
	}
	return NULL;
}

int hsc_init(node a[], int* np, int N)
{
	int i;
	for (i = 0; i < N; i++) a[i].next = NULL;
	*np = 0;
	return 1;
}

int hsc_deleteall(node a[], int* np, int N)
{
	node* t, * p;
	int i;
	for (i = 0; i < N; i++)
	{
		t = a[i].next;
		while (t != NULL)
		{
			p = t;
			t = t->next;
			free(p);
		}
	}
	(*np) = 0;
	return 1;
}

int hsc_create(node * *a, int* np, int N)
{
	int i;
	*a = (node*)malloc(sizeof(node) * N);
	hsc_init(*a, np, N);
	return 1;
}

int hsc_list(node a[], int N)
{
	int i;
	node* t;
	for (i = 0; i < N; i++)
	{
		printf("\nBucket %d :", i);
		t = a[i].next;
		while (t != NULL)
		{
			printf(" -> %d", t->key);
			t = t->next;
		}
	}
	return 1;
}



void main(void)
{
	node* bucket;
	int nitem = 0;
	hsc_create(&bucket, &nitem, TABLE_SIZE);

	hsc_insert(12, bucket, &nitem);
	hsc_insert(32, bucket, &nitem);
	hsc_insert(79, bucket, &nitem);
	hsc_insert(11, bucket, &nitem);
	hsc_insert(22, bucket, &nitem);

	hsc_search(22, bucket, &nitem);
	
	hsc_list(bucket, TABLE_SIZE);
	hsc_deleteall(bucket, &nitem, TABLE_SIZE);
	free(bucket);
}





