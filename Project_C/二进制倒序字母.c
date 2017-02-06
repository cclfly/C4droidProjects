#include <stdio.h>
#include <math.h>

int fun(int x) {
	int sum=0;
	for (int i=0;i<7;i++) {
		sum+=x%2*pow(2,6-i);
		x/=2;
	}
	return sum;
}

int main() {
  int ic;
  while (1) {
    scanf("%d", &ic);
    if (ic == 0)
      break;
    printf("%c",fun(ic));
  }
  return 0;
}

//73 2 27 123 55 83 2 79 123 87 66 0
//I love you!