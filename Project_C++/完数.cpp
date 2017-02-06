#include<iostream>
using namespace std;
int main()
{
	int a, i, j, k;
	int *y, *x;
	a = 1;
	while (a <= 1000)
	{
		// cout << "请输入数：" << flush;
		// cin >> a;
		y = (int *)malloc(sizeof(int) * a);
		x = (int *)malloc(sizeof(int) * a);
		for (i = 0; i < a; i++)
		{
			x[i] = i + 1;
		}
		j = 0;
		for (i = 0; i < a; i++)
		{
			y[j] = a / x[i];
			if (y[j] == (float)a / x[i])
			{
				j++;
			}
		}
		int sum;
		sum = 0;
		for (k = 1; k < j; k++)
			sum += y[k];
		if (a == sum)
		{
			cout << a << "\t的因数有：" << endl;
			for (k = j - 1; k >= 0; k--)
				cout << y[k] << "," << flush;
			cout << "\b \t" << j << "个数" << endl;
			if (a == sum)
				cout << a << "是完数" << endl;
			else
				cout << a << "不是完数" << endl;
			cout << endl << endl;
		}
		a++;
	}
}