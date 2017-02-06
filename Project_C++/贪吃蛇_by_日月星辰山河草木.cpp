#include<iostream>
#include<conio.h>
#include<stdlib.h>
#define H 13
#define W 50
#define FOOD '1'
#define HALL '2'
#define HEAD '3'
#define BODY '4'
using namespace std;
void move();
void go();
void over();
void draw();
int judge();
void init();
void getfood();
int x,y;
int a,b;
char map[W][H];
char *head;
char *food;
char*body[H*W];
int jg;
int l=1;/*length of snail*/
void init()
{
	x=W/2;
	y=H/2;
	for(int i=0;i!=H;i++)
	for(int j=0;j!=W;j++)
	if(i==0||i==H-1||j==0||j==W-1)
	map[j][i]=HALL;
	else
	map[j][i]=' ';
	head=&map[x][y];
	*head=HEAD;
	body[0]=&map[x-1][y];
	*body[0]=BODY;
	//body[1]=&map[x-2][y];
//	*body[1]=BODY;
}
void move()
{
	static char td='6', /*temp_direction*/
direction='6';
	while(kbhit())
	direction=getch();
	loop:switch (direction)
	{
		case '2':
		y--;break;
		case '4':
		x--;break;
		case '6':
		x++;break;
		case '8':
		y++;break;
		default:
		direction=td;
		goto loop;
		break;
	}
	head=&map[x][y];
	if(head==body[1])
	{
		switch (direction)
		{
			case '2':
			y++;break;
			case '4':
			x++;break;
			case '6':
			x--;break;
			case '8':
			y--;break;
		}
	direction=td;
	goto loop;
	}
	td=direction;
	while(kbhit())
	getch();
	
}
void go()
{
	for(int i=l;i!=0;i--)
	body[i]=body[i-1];
	body[0]=head;
	*body[0]=BODY;
	if(jg==1)
	*body[l]=BODY;
	else
	*body[l]=' ';
}
void getfood()
{
	srand(time(0));
	do{
	a=rand()%(H-2)+1;
	b=rand()%(W-2)+1;
	}
	while(map[a][b]!=' ');
	food=&map[a][b];
	*food=FOOD;
}
int judge()
{
		for(int i=0;i!=H;i++)
	for(int j=0;j!=W;j++)
	switch (*head)
	{
		case HALL:
		case BODY:
		over();
		return -1;
		break;
		case FOOD:
		l++;
		*head=HEAD;
		getfood();
		return 1;
		break;
		default:
		*head=HEAD;
		break;
	}
	return 0;
}
void over()
{
	gotoxy(1,H+2);
	cout<<"gameover!!!"<<endl;
	exit(0);
}
void draw()
{
	clrscr();
		for(int i=0;i!=H;i++)
		{
	for(int j=0;j!=W;j++)
	switch (map[j][i])
	{
		case HALL:
		cout<<"\033[46;34m#\033[0m";
		break;
		case HEAD:
		cout<<"\033[46;34m+\033[0m";
		break;
		case FOOD:
		cout<<"\033[46;34m@\033[0m";
		break;
		case BODY:
		cout<<"\033[46;34m*\033[0m";
		break;
		default:
		cout<<"\033[47;37m ";
		break;
	}
	cout<<endl;
		}
}
int main()
{
	init();
	getfood();
	jg=judge();
	while(2)
	{
		go();
		move();
		judge();
		draw();
		usleep(200000);
	}
	return 1;
}