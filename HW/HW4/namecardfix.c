#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE  21
#define CORP_SIZE  31
#define TEL_SIZE   16
#define REC_SIZE   (NAME_SIZE + CORP_SIZE + TEL_SIZE)
#define FILE_SIZE  64

typedef struct _card
{
	char name[NAME_SIZE];
	char corp[CORP_SIZE];
	char tel[TEL_SIZE];
	struct _card* next;
} card;

card* head, * tail;

void init_card(void)
{
	head = (card*)malloc(sizeof(card));
	tail = (card*)malloc(sizeof(card));
	head->next = tail;
	tail->next = tail;
}

char* erase_nl(char* s) {
	if (s[strlen(s) - 1] == '\n')
		s[strlen(s) - 1] = '\0';
	return s;
}

void input_card(void)
{
	card* t;
	card* s;
	t = (card*)malloc(sizeof(card));
	s = (card*)malloc(sizeof(card));
	s = head;
	printf("\nInput namecard menu : ");
	printf("\n   Input name -> ");
	//gets(t->name);
	fgets(t->name, NAME_SIZE, stdin);
	erase_nl(t->name);
	printf("\n   Input corporation -> ");
	//gets(t->corp);
	fgets(t->corp, CORP_SIZE, stdin);
	erase_nl(t->corp);
	printf("\n   Input telephone number -> ");
	//gets(t->tel);
	fgets(t->tel, TEL_SIZE, stdin);
	erase_nl(t->tel);
	int i = 0;
	while (s->next!=tail){
		if (s->next->name[i] == t->name[i]) i+=1;
		else if (s->next->name[i] < t->name[i]){
			s = s->next;
			i = 0;
		}
		else break;
	}
	t->next = s->next;  /* insert at s */
	s->next = t;
}

void print_card(card * t, FILE * f)
{
	fprintf(f, "\n%-20s    %-30s    %-15s", t->name, t->corp, t->tel);
}

void print_header(FILE * f)
{
	fprintf(f, "\nName                    "
		"Corporation                      "
		"Telephone number");
	fprintf(f, "\n--------------------    "
		"-----------------------------    "
		"----------------");
}

void load_cards(char* s)
{
	FILE* fp;
	card* t;
	card* u;
	//if ((fp = fopen(s, "rb")) == NULL)
	if ((fopen_s(&fp, s, "rb")) != NULL)
	{
		printf("\n    Error : %s is not exist.", s);
		return;
	}
	t = head->next;
	while (t != tail)
	{
		u = t;
		t = t->next;
		free(u);
	}
	head->next = tail;
	while (1)
	{
		t = (card*)malloc(sizeof(card));
		if (!fread(t, REC_SIZE, 1, fp))   /* if file end... */
		{
			free(t);
			break;
		}
		t->next = head->next;
		head->next = t;
	}
	fclose(fp);
}
void save_cards(char* s)
{
	FILE* fp;
	card* t;
	//if ((fp = fopen(s, "wb")) == NULL)
	if ((fopen_s(&fp, s, "wb")) != NULL)
	{
		printf("\n    Error : Disk write failure.");
		return;
	}
	t = head->next;
	while (t != tail)
	{
		fwrite(t, REC_SIZE, 1, fp);
		t = t->next;
	}
	fclose(fp);
}

int delete_card(char* s)
{
	card* t;
	card* p;
	p = head;
	t = p->next;
	while (strcmp(s, t->name) != 0 && t != tail)
	{
		p = p->next;
		t = p->next;
	}
	if (t == tail)
		return 0;   /* not found */
	p->next = t->next;
	free(t);
	return 1;
}

card* search_card(char* s)
{
	card* t;
	t = head->next;
	while (strcmp(s, t->name) != 0 && t != tail)
		t = t->next;
	if (t == tail)
		return NULL;  /* not found */
	else
		return t;
}
int select_menu(void)
{
	int i;
	char s[10];
	printf("\n\nNAMECARD Manager");
	printf("\n----------------------------");
	printf("\n1. Input  Namecard");
	printf("\n2. Delete Namecard");
	printf("\n3. Search Namecard");
	printf("\n4. Load   Namecard");
	printf("\n5. Save   Namecard");
	printf("\n6. List   Namecard");
	printf("\n7. Print  Namecard");
	printf("\n8. End    Program");
	do
	{
		printf("\n\n   : select operation -> ");
		i = atoi(erase_nl(fgets(s, 10, stdin)));
	} while (i < 0 || i > 8);
	return i;
}

void main(void)
{
	//char* fname = "NAMECARD3.DAT";
	char fname[FILE_SIZE];
	char name[NAME_SIZE];
	int i;
	card* t;
	init_card();
	while ((i = select_menu()) != 8)
	{
		switch (i)
		{
		case 1: input_card();
			break;
		case 2: printf("\n    Input name to delete -> ");
			//gets(name);
			erase_nl(fgets(name, NAME_SIZE, stdin));
			if (!delete_card(name))
				printf("\n        Can't find that name.");
			break;
		case 3: printf("\n    Input name to search -> ");
			//gets(name);
			erase_nl(fgets(name, NAME_SIZE, stdin));
			t = search_card(name);
			if (t == NULL)
			{
				printf("\n        Can't find that name.");
				break;
			}
			print_header(stdout);
			print_card(t, stdout);
			break;
		case 4: printf("\n    Input file name to load -> ");
			erase_nl(fgets(fname, FILE_SIZE, stdin));
			load_cards(fname);
			break;
		case 5: printf("\n    Input file name to save -> ");
			erase_nl(fgets(fname, FILE_SIZE, stdin));
			save_cards(fname);
			break;
		case 6: t = head->next;
			print_header(stdout);
			while (t != tail)
			{
				print_card(t, stdout);
				t = t->next;
			}
			break;
		case 7: t = head->next;
			print_header(stdout);
			while (t != tail)
			{
				print_card(t, stdout);
				t = t->next;
			}
			break;
		}
	}
	printf("\n\nProgram ends...");
}
