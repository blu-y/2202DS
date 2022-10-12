#include <stdio.h>

int main()
{
    printf("Put text and press ENTER!\n");
    char a[256];
    scanf("%s", a);

    printf("text: \" %s \".\n", a);
    return 0;
}