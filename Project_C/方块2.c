// v 2.0
// 新增块
// 支持变形
// 支持加速下落
// By >> 百度贴吧 @复而旦兮
#include<stdio.h>
#include<time.h>
#include <conio.h>
#include<stdlib.h>
#define Difficulty 5
/* 难度，越大越难 */
#define H 25
#define W 20
#define Up '2'
#define Down '8'
#define Lift '4'
#define Right '6'
int p[H][W];
int found(int v, int i, int w, int m)	// 创建移动过程
{
	if (v == 0)
	{
		p[i][w] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
		p[i + 2][w + 1] = m;
	}							// 竖右拐
	if (v == 1)
	{
		p[i][w + 1] = m;
		p[i][w + 2] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
	}							// 正拐
	if (v == 2)
	{
		p[i][w] = m;
		p[i][w + 1] = m;
		p[i][w + 2] = m;
		p[i][w + 3] = m;
	}							// 直线
	if (v == 3)
	{
		p[i][w] = m;
		p[i][w + 1] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
	}							// 正方
	if (v == 4)
	{
		p[i][w] = m;
		p[i][w + 1] = m;
		p[i + 1][w + 1] = m;
		p[i + 1][w + 2] = m;
	}							// 正反拐

	if (v == 5)
	{
		p[i][w + 1] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
		p[i + 2][w] = m;
	}							// 竖左拐
	if (v == 6)
	{
		p[i][w] = m;
		p[i][w + 1] = m;
		p[i][w + 2] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 2] = m;
		p[i + 2][w] = m;
		p[i + 2][w + 1] = m;
		p[i + 2][w + 2] = m;
	}							// 口形
	if (v == 7)
	{
		p[i][w] = m;
		p[i + 1][w] = m;
		p[i + 2][w] = m;
		p[i + 3][w] = m;
	}							// 竖直线
	if (v == 8)
	{
		p[i][w] = m;
		p[i][w + 1] = m;
		p[i][w + 2] = m;
		p[i][w + 3] = m;
		p[i][w + 4] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 2] = m;
		p[i + 1][w + 4] = m;
	}							// 盖E
	if (v == 9)
	{
		p[i][w + 1] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
		p[i + 1][w + 2] = m;
	}							// 土形
	if (v == 10)
	{
		p[i][w] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
		p[i + 2][w] = m;
	}							// 右土
	if (v == 11)
	{
		p[i][w] = m;
		p[i][w + 1] = m;
		p[i][w + 2] = m;
		p[i + 1][w + 1] = m;
	}							// 倒土
	if (v == 12)
	{
		p[i][w + 1] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
		p[i + 2][w + 1] = m;
	}							// 左土
	if (v == 13)
	{
		p[i][w] = m;
		p[i][w + 2] = m;
		p[i][w + 4] = m;
		p[i + 1][w] = m;
		p[i + 1][w + 1] = m;
		p[i + 1][w + 2] = m;
		p[i + 1][w + 3] = m;
		p[i + 1][w + 4] = m;
	}							// 上E
	if (v > 13)
	{
		p[i][w] = m;
	}							// 炸弹
}

int math()
{
	int v;
	srand((int)time(NULL));
	v = rand() % 17;
	return v;
}

int getscan(int w, int *v, int i, int *di)	// 读取输入
{
	int r, t;
	if (*v == 0 || *v == 10 || *v == 12)
		r = 2;
	if (*v == 1 || *v == 11)
		r = 3;
	if (*v == 2)
		r = 4;
	if (*v == 3)
		r = 2;
	if (*v == 9 || *v == 6)
		r = 3;
	if (*v == 5)
		r = 2;
	if (*v == 7 || *v > 13)
		r = 1;
	if (*v == 8 || *v == 13)
		r = 5;
	if (*v == 4)
		r = 3;
	while (kbhit())
	{
		t = getch();
		if (t == Lift && w != 0 && p[i][w - 1] != 1 && *v != 1	/* 修复吞块问题 
																 */ )
			w--;
		if (t == Lift && w != 0 && p[i][w] != 1 && *v == 1
			&& p[i + 1][w - 1] != 1)
			w--;
		if (t == Right && w + r != W && p[i][w + r] != 1)
			w++;

		if (t == Up)
		{
			if (*v==1||*v==0)
			{
			if (*v==1)*v=0;
		else*v=1;break;
			}
			if (*v==2||*v==7)
			{
			if (*v==2)*v=7;
		else	*v=2;
			break;}
			if (*v==5||*v==4)
			{
			if (*v==5)*v=4;
		else *v=5;
			break;}
			if (*v==8||*v==13)
			{
			if (*v==8)*v=13;
		else	*v=8;
			break;}
		if (*v>8&&*v<12) {*v+=1;break;}
		if (*v==12) *v=9;
		}
		if (t == Down)
			*di = 40;			// 此行控制确认下滑速度
	}
	/* while (kbhit()) t = getch(); */
	return w;
}

int move(int s)					// 消行函数
{
	int i, j;
	for (i = s; i > 0; i--)
		for (j = 0; j < W; j++)
			p[i][j] = p[i - 1][j];
}

int main()						// 主函数
{
	int j, i, k, v, max = 0, u, t, r, q, e = 0, f, w = W / 2, g = 0;	// 变量声明
	int di = Difficulty;
	for (i = 0; i < H; i++)
		for (j = 0; j < W; j++)
			p[i][j] = 0;		// 产生数组
	v = math();					// 随机数
	for (i = 0; i < 100; i++)	// 主循环
	{
		w = getscan(w, &v, i, &di);	// 输入值？
		found(v, i, w, 1);		// 移动
		for (j = 3; j < H; j++)
		{
			printf("┊");
			for (k = 0; k < W; k++)
			{
				if (p[j][k] == 0)
					printf("　");
				else
					printf("圆");
			}
			printf("┊");
			printf("\n");
		};						// 打印
		if (e == 0)
			found(v, i, w, 0);	// 消除
		e = 0;
		if (v == 0)				// 第一个图形判断
			if (i == H - 3 || p[i + 2][w] == 1 || p[i + 3][w + 1] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 1)				// 
			if (i == H - 2 || p[i + 2][w] == 1 || p[i + 2][w + 1] == 1
				|| p[i + 1][w + 2] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			}
		if (v == 2)				// 
			if (i == H - 1 || p[i + 1][w] == 1 || p[i + 1][w + 1] == 1
				|| p[i + 1][w + 2] == 1 || p[i + 1][w + 3] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;

			}
		if (v == 3)
			if (i == H - 2 || p[i + 2][w] == 1 || p[i + 2][w + 1] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 4)
			if (i == H - 2 || p[i + 1][w] == 1 || p[i + 2][w + 1] == 1
				|| p[i + 2][w + 2] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};

		if (v == 5)
			if (i == H - 3 || p[i + 3][w] == 1 || p[i + 2][w + 1] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 6)
			if (i == H - 3 || p[i + 3][w] == 1 || p[i + 3][w + 1] == 1
				|| p[i + 3][w + 2] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 7)
			if (i == H - 4 || p[i + 4][w] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 8)
			if (i == H - 2 || p[i + 2][w] == 1 || p[i + 1][w + 1] == 1
				|| p[i + 2][w + 2] == 1 || p[i + 1][w + 3] == 1
				|| p[i + 2][w + 4] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 9)
			if (i == H - 2 || p[i + 2][w] == 1 || p[i + 2][w + 1] == 1
				|| p[i + 2][w + 2] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 10)
			if (i == H - 3 || p[i + 3][w] == 1 || p[i + 2][w + 1] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 11)
			if (i == H - 2 || p[i + 1][w] == 1 || p[i + 2][w + 1] == 1
				|| p[i + 1][w + 2] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 12)
			if (i == H - 3 || p[i + 2][w] == 1 || p[i + 3][w + 1] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v == 13)
			if (i == H - 2 || p[i + 2][w] == 1 || p[i + 2][w + 1] == 1
				|| p[i + 2][w + 2] == 1 || p[i + 2][w + 3] == 1
				|| p[i + 2][w + 4] == 1)
			{
				found(v, i, w, 1);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;
			};
		if (v > 13)
			if (i == H - 1 || p[i + 1][w] == 1)
			{
				p[i - 1][w - 1] = 0;
				p[i - 1][w] = 0;
				p[i - 1][w + 1] = 0;
				p[i][w - 1] = 0;
				p[i][w] = 0;
				p[i][w + 1] = 0;
				p[i + 1][w - 1] = 0;
				p[i + 1][w] = 0;
				p[i + 1][w + 1] = 0;
				 found(v, i, w, 0);
				w = W / 2;
				i = 0;
				v = math();
				di = Difficulty;

			}
		// 图形判断结束
		q = 0;
		for (t = 0; t < H; t++)
		{
			q = 0;
			for (u = 0; u < W; u++)
			{
				if (max > 1 && p[0][u] == 1)
					i = 100;
				if (p[t][u] == 1)
					q++;
				if (q == W)
				{
					move(t);
					g++;
				}
			}

		}						// 消行
		printf("\n当前分数为：%d\n", g);
		usleep(1000000 / di);
		clrscr();
		max++;					// 用以判断游戏结束
	};
	printf("你输了！！！\n你的得分为：%d", g);
}