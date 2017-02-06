#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;
#include<conio.h>
int main(int agec,char *agev[])
{
	short **a;
	short M,N;
	short i,j;
	srand(time(0));
	cout<<"\t矩阵大小："<<endl;
	cout<<"行："<<flush;
	cin>>M;
	a=(short**)malloc(sizeof(short*)*M);
	cout<<"列："<<flush;
	cin>>N;
	for(i=0;i<M;i++)
	*(a+i)=(short*)malloc(sizeof(short)*N);
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			*(*(a+i)+j)=((rand()%5==0)?(-1):(1))*(rand()%100);
		}
	}
	clrscr();
	cout<<"\t自动生成矩阵为："<<endl<<endl;
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			cout<<setw(6)<<a[i][j];
		}
		cout<<endl<<endl<<endl;
	}
	return 0;
}