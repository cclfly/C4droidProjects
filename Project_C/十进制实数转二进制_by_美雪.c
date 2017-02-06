#include <stdio.h>
#include <math.h>

void convert(double n, double t, int i){
	double temp=pow(2, i);
	if (i==-1) putchar('.');
	if (t+temp<=n){
		putchar('1');
		t=t+temp;
	}
	else putchar('0');
	if (t!=n && i>=-20)
	    convert(n, t, i-1);
}

void toBin(double n){
	int i=-1;
	double t=1;
	for (; t<n; i++)
	    t=t*2;
	convert(n, 0, i+(i==-1));
}

int main(){
	double n=10.1;
	toBin(n);
}