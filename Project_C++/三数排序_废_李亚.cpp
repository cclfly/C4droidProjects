#include<iostream>
using namespace std;
void swap(int *, int *, int *, int, int, int );
int main()
{
	int *a, *b, *c, x, y, z;
	cout << "x=";
	cin >> x;
	cout << "y=";
	cin >> y;
	cout << "z=";
	cin >> z;
	a=&x;b=&y;c=&z;
	swap(a, b, c, x, y, z);
	cout << *a << *b << *c;
};

void swap(int *a, int *b, int *c, int x, int y, int z)
{
	if (x > y)
	{
		if (x > z)
		{
			if (y > z)
			{
				a = &x;
				b = &y;
				c = &z;
			}
			else
			{
				a = &x;
				b = &z;
				c = &y;
			}
		}
		else
		{
			a = &z;
			b = &x;
			c = &y;
		}
	}
	else if (x > z)
	{
		a = &y;
		b = &x;
		c = &z;
	}
	else
	{
		a = &y;
		b = &z;
		c = &x;
	}
	cout<<*a<<*b<<*c<<endl;
}