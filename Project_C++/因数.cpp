#include<iostream>
using namespace std;
int main()
{
	int a, i, j = 0;
	int *y, *x;
	cout << "请输入数：" << flush;
	cin >> a;
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
	cout << "因数有：" << endl;
	for(int k=j-1;k>=0;k--)
	cout<<y[k]<<","<<flush;
	cout<<"\b \t"<<j<<"个数"<<endl;
}