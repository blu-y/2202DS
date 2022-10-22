// 후위표기법의 적법성 검사 > 전위표기법 적법성 검사
#include <stdio.h>

int is_operator(int k){
    return (k=='+' || k=='-' || k=='*' || k=='/');
}

int is_post_legal(char *s) {
   int f = 0;
   while (*s) {
	   while (*s == ' ') s++;
	   if (is_operator(*s))
              f--;
	   else
              f++;
           if (f < 1) /* check situation like A+B */
              break;
	   s++;
   }
   return (f == 1); /* legal if operand-operator==1 */
}

int is_pre_legal(char *s) {
   int f = -1;
   while (*s == ' ') s++;
   if (!is_operator(*s)) return 0; // when first is not op: false
   s++;
   while (*s) {
	   while (*s == ' ') s++;
	   if (is_operator(*s)) f--;
	   else f++;
      if (f > 1) break; // check situation like A+B
	   s++;
   }
   return (f == 1); // legal if operand-operator==1
}

/*
int is_pre_legal(char *s) {
   int f = -1;
   while (*s == ' ') s++;
   printf("%c %d\n", *s, f);
   if (!is_operator(*s)) return 0; //when first is not op: false
   s++;
   while (*s) {
	   while (*s == ' ') s++;
	   if (is_operator(*s)) f--;
	   else f++;
      printf("%c %d\n", *s, f);
      if (f > 1) break; // check situation like A+B
	   s++;
   }
   return (f == 1); // legal if operand-operator==1
}
*/

int main(){
   char l[100] = "+ + 2 1";
   //printf("String: ");
   //gets_s("%s", &l);
   printf("%d\n", is_pre_legal(l));
}