#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 3000

int main()
{
	int buff[N] = {0};
	int r = 0;
	srand(time(NULL));
	for (int n = 0; n < N; n++) buff[n] = rand();
	FILE *fp;
	int size, count;

	fp = fopen("RANDOM.DAT", "wb");
	if (fp == NULL) printf("파일 열기 실패\n");

	size = sizeof(int);
	count = sizeof(buff) / sizeof(int);

	fwrite(&buff, size, count, fp);
	fclose(fp);
	return 0;
}