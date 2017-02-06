#include <stdio.h>
/*int printf(const char*,...);*/
void fun() {
  printf("xx\n");
  printf("vv\n");
}
int main() {
  printf("Hello CIDE v1.9a\n");
  // printf("h");
  int a;
  scanf("%d", &a);
  fun();
  printf("%d", a);
  return 0;
}