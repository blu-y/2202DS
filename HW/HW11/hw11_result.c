#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp;
	int size = sizeof(int);
	fp = fopen("RANDOM.DAT", "rb");
	if (fp == NULL) printf("���� ���� ����\n");
	fseek(fp, 0L, SEEK_END);
	int count = (int)(ftell(fp) / size);
	fseek(fp, 0L, SEEK_SET);
	int output[count];
	for (int i = 0; i < count; i++) {
		fread(&output[i], size, 1, fp);
		printf("%d ", output[i]);
	}
	printf("\n\n");
	fclose(fp);
	fp = fopen("RESULT.DAT", "rb");
	if (fp == NULL) printf("���� ���� ����\n");
	int result[count];
	for (int i = 0; i < count; i++) {
		fread(&result[i], size, 1, fp);
		printf("%d ", result[i]);
	}
	printf("\n");
	fclose(fp);
	return 0;
}