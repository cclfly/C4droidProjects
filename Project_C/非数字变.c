#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void check_x(char *str1, char *str2) {
  // str2 = (char *)malloc(sizeof(char) * strlen(str1));
  while (*str1) {
    if (*str1 >= '0' && *str1 <= '9')
      *str2 = *str1;
    else
      *str2 = '*';
    str1++;
    str2++;
  }
  *str2 = '\0';
}
int check_y(char *str) {
  int i = 0, j = 0;
  while (*str) {
    str[i++] = str[j];
    do {
      j++;
    } while (str[j] == '*');
  }
  str[i++] = '\0';
  return i;
}
void check(char *str1, char *str2) {
  check_x(str1, str2);
  puts(str2);
  realloc(str2, check_y(str2));
}
int main() {
  char *str1, *str2;
  str1 = (char *)malloc(sizeof(char) * 1000);
  gets(str1);
  realloc(str1, strlen(str1));
  str2 = (char *)malloc(strlen(str1));
  check(str1, str2);
  puts(str2);
  free(str1);
  free(str2);
  return 0;
}