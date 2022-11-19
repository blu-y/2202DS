#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

main() {
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		printf("%d ", rand()%1000);
	}
}