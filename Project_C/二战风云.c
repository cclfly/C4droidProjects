#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<conio.h>
#include<time.h>

#define  ROOT "/sdcard/l_二战风云/"
#define MAXCITYSUM 18
#define MAXOFFICERSUM 10
#define MAXGUILDHALLGRADE 12
#define MAXBUILDSUM 42
#define SCIENCESUM 21
#define TITLE printf("\033[47;34ms)刷	b)报	h)首\033[0m\n%s(%d,%d)\n",CityName[Ci],CityCoord[Ci][0],CityCoord[Ci][1])

char user_name[100],account[100], password[16],
	CityOfficerName[MAXCITYSUM][MAXOFFICERSUM][100], CityName[MAXCITYSUM][100];


char RandOfficerName[10][4]={"梅","格","里","斯","基","德","伦","英","理","南"};
int Ci,Prestige, CitySum, Diamond, CityCoord[MAXCITYSUM][2],
	CityResource[MAXCITYSUM][12], CityPopularfeel[MAXCITYSUM],
	CityTax[MAXCITYSUM], CityArmy[MAXCITYSUM][20],
	CityOfficer[MAXCITYSUM][MAXOFFICERSUM][7], CityWildSum[MAXCITYSUM],
	CityOfficerSum[MAXCITYSUM], CityWild[MAXCITYSUM][MAXGUILDHALLGRADE][3],
	CityBuildSum[MAXCITYSUM], CityBuild[MAXCITYSUM][MAXBUILDSUM][2],
	CityArmyBuildSum[MAXCITYSUM], ScienceGrade[SCIENCESUM];

long unsigned CityBuildTime[MAXCITYSUM][MAXBUILDSUM];	// 时间，用long型


void init();					// 初始化数据
void updata();					// 更新文件数据
void pr(int page);


int main()
{
	int page=0,ch;
	init();
	fflush(stdin);
	getch();
	while (1)
	{
		pr(page);
		fflush(stdin);
		switch (ch=getch())
		{
			case 's':page=0;break;
			case 'b':page=1;break;
		}
		printf("%d",ch);
	}
}

void pr(int page)
{
	TITLE;
	switch (page)
	{
		case 0:
		printf("%d\n",page);break;
		case 1:
		printf("%d\n",page);break;
	}
}


void updata()
{
	FILE *f;
	f = fopen(account, "w");
	char putch[100];

	// 分**隔**线

	fputs(password, f);			// 写入密码信息
	fputs("\n", f);				// 分隔记号，下同
	sprintf(putch, "%d", Prestige);	// 转化数据格式，下同
	fputs(putch, f);			// 写入声望数
	memset(putch, 0, sizeof(char) * 100);	// 释放临时字符串变量内存，下同
	fputs(",", f);
	sprintf(putch, "%d", CitySum);
	fputs(putch, f);			// 写入城市数
	memset(putch, 0, sizeof(char) * 100);
	fputs(",", f);
	sprintf(putch, "%d", Diamond);
	fputs(putch, f);			// 写入钻石数
	memset(putch, 0, sizeof(char) * 100);
	fputs("\n", f);
	for (int n = 0; n < CitySum; n++)	// 城市信息循环
	{
		for (int j = 0; j < 2; j++)	// 写入城市坐标
		{
			sprintf(putch, "%d", CityCoord[n][j]);
			fputs(putch, f);
			memset(putch, 0, sizeof(char) * 100);
			fputs(",", f);
		}
		fputs(CityName[n], f);
		fputs(",", f);
		for (int j = 0; j < 12; j++)	// 写入城市资源
		{
			sprintf(putch, "%d", CityResource[n][j]);
			fputs(putch, f);
			memset(putch, 0, sizeof(char) * 100);
			fputs(",", f);
		}
		sprintf(putch, "%d", CityPopularfeel[n]);
		fputs(putch, f);		// 写入民心
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
		sprintf(putch, "%d", CityTax[n]);
		fputs(putch, f);		// 写入税率
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
		for (int j = 0; j < 20; j++)	// 写入城市军队信息
		{
			sprintf(putch, "%d", CityArmy[n][j]);
			fputs(putch, f);
			memset(putch, 0, sizeof(char) * 100);
			fputs(",", f);
		}
		sprintf(putch, "%d", CityOfficerSum[n]);
		fputs(putch, f);		// 写入城市军官数
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
		for (int j = 0; j < CityOfficerSum[n]; j++)	// 写入军官名字信息
		{
			fputs(CityOfficerName[n][j], f);
			fputs(",", f);
		}
		for (int j = 0; j < CityOfficerSum[n]; j++)	// 写入城市军官信息数据
		{
			for (int m = 0; m < 7; m++)
			{
				sprintf(putch, "%d", CityOfficer[n][j][m]);
				fputs(putch, f);
				memset(putch, 0, sizeof(char) * 100);
				fputs(",", f);
			}
		}
		sprintf(putch, "%d", CityWildSum[n]);
		fputs(putch, f);		// 写入城市野地数
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
		for (int j = 0; j < CityWildSum[n]; j++)	// 写入城市野地数据
		{
			for (int m = 0; m < 3; m++)
			{
				sprintf(putch, "%d", CityWild[n][j][m]);
				fputs(putch, f);
				memset(putch, 0, sizeof(char) * 100);
				fputs(",", f);
			}
		}
		sprintf(putch, "%d", CityBuildSum[n]);
		fputs(putch, f);		// 写入城市建筑数量
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
		for (int j = 0; j < CityBuildSum[n]; j++)	// 写入城市建筑信息
		{
			for (int m = 0; m < 2; m++)
			{
				sprintf(putch, "%d", CityBuild[n][j][m]);
				fputs(putch, f);
				memset(putch, 0, sizeof(char) * 100);
				fputs(",", f);
				if (m == 1 && CityBuild[n][j][m] != 0)	// 写入城市建筑相关时间
				{
					sprintf(putch, "%d", CityBuildTime[n][j]);
					fputs(putch, f);
					memset(putch, 0, sizeof(char) * 100);
					fputs(",", f);
				}
			}
		}
		sprintf(putch, "%d", CityArmyBuildSum[n]);	// 写入军工厂数量
		fputs(putch, f);
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
	}							
	
	/* 城市信息循环结束*/
	
	
	for (int j = 0; j < SCIENCESUM; j++)	// 科技等级写入循环
	{
		sprintf(putch, "%d", ScienceGrade[j]);
		fputs(putch, f);
		memset(putch, 0, sizeof(char) * 100);
		fputs(",", f);
	}
	sprintf(putch, "%d",Ci);//当前城市编号
	fputs(putch, f);
	memset(putch, 0, sizeof(char) * 100);
	fputs(",", f);
	fclose(f);					// 关闭打开的文件

}

void init()
{
	FILE *fp;
	int ReadPassword, ch;
	char root[50] = ROOT, getch[100];
	int i = 0, sum = 1;
	mkdir(root, S_IRUSR);		// 建立系统根文件夹

	// //分**割**线///
	
	
	printf("欢迎！！输入用户名登录或注册:\n");
	scanf("%s", &user_name);	// 获取输入：用户名
	while (strlen(user_name) > 100 - strlen(root) || strlen(user_name) < 5)	// 判断输入的用户名是否符合要求
	{
		printf("长度过长或过短！！\n");
		scanf("%s", user_name);
	}
	for (i = 0; i < strlen(root); i++)	// 先引入根目录
	{
		account[i] = root[i];
	}
	for (i = 0; i < strlen(user_name); i++)	// 再引入用户文件名
	{
		account[strlen(root) + i] = user_name[i];
	}
	clrscr();					// 清屏

	// /分**割**线////

	if ((fp = fopen(account, "r")) == NULL)	// 若该用户名不存在
	{
		printf("新用户，请设置密码:(16位以内,建议为数字)\n");
		scanf("%s", password);	// 输入新密码
		while ((strlen(password)) > 16)	// 判断密码是否符合要求
		{
			printf("过长，重新输入:(16位以内)\n");
			scanf("%s", password);
		}
		printf("通过！！！\n");
		if ((fp = fopen(account, "w")) == NULL)	// 创建用户根文件并判断
		{
			printf
				("失败！！！请退出重试\n详情请联系QQ:384426186\n");
			exit(0);
		}

		// 分**割**线


		/* 初始化数据 */
		srand((int)time(NULL));
		Prestige = 0;
		CitySum = 1;
		Ci=0;
		Diamond = 500;
		CityCoord[0][0] = rand()%501;
		CityCoord[0][1] = rand()%501;
		for (int j = 0; j < 12; j++)
			CityResource[0][j] = 100;
		CityPopularfeel[0] = 90;
		CityTax[0] = 10;
		CityArmy[0][3] = 500;
		char name[20] = "二战风云";
		for (int j = 0; j < strlen(name); j++)
			CityName[0][j] = CityOfficerName[0][0][j] = name[j];
		CityOfficer[0][0][0] = 0;
		CityOfficer[0][0][1] = 3;
		CityOfficer[0][0][2] = rand()%10+1;
		CityOfficer[0][0][3] = 120;
		CityOfficer[0][0][4] = 45;
		CityOfficer[0][0][5] = 20;
		CityOfficer[0][0][6] = 0;
		CityWildSum[0] = 0;
		CityOfficerSum[0] = 1;
		CityBuildSum[0] = 1;
		CityBuild[0][0][0] = 1;
		CityBuild[0][0][1] = 0;
		CityArmyBuildSum[0] = 0;
		for (int j = 0; j < SCIENCESUM; j++)
			ScienceGrade[j] = 0;
			
			
		/* 初始化数据完毕 */


		updata();				// 更新文件
		printf("成功！！！\n即将进入。。。\n");
		usleep(1000000);
		 clrscr();
	}//新建用户完毕

	// /分**割**线////

	else						// 若用户名存在
	{
		while (i != sum)		// 密码验证
		{
			printf("输入密码:\n");
			scanf("%s", password);
			i = sum = 0;
			fseek(fp, 0l, SEEK_SET);	// 将文件指针移至开始处
			while ((ReadPassword = getc(fp)) != '\n')	// 读取用户文件内的密码字符
			{
				if ((strlen(password)) >= i && password[i] == ReadPassword)
					sum++;		// 若输入与密码对应字符匹配，匹配数量加1
				i++;			// 文件内密码长度
			}
			if ((strlen(password)) != i)
				i = -1;			// 确保密码正确
			if (i != sum)
			{
				printf("密码错误！！！\n");
			}
		}
		printf("登录成功！！！\n");
		usleep(1000000);
		clrscr();

		/*开始获取数据*/

		i = 0;
		while ((ch = getc(fp)) != ',')
		{
			getch[i] = ch;
			i++;
		}
		Prestige = atoi(getch);	// 声望
		memset(getch, 0, sizeof(char) * 100);
		i = 0;
		while ((ch = getc(fp)) != ',')
		{
			getch[i] = ch;
			i++;
		}
		CitySum = atoi(getch);	// 城市数
		memset(getch, 0, sizeof(char) * 100);
		i = 0;
		while ((ch = getc(fp)) != '\n')
		{
			getch[i] = ch;
			i++;
		}
		Diamond = atoi(getch);	// 钻石数
		memset(getch, 0, sizeof(char) * 100);
		
		/*城市循环*/
		
		for (int n = 0; n < CitySum; n++)	// /城市循环
		{
			for (int j = 0; j < 2; j++)
			{
				i = 0;
				while ((ch = getc(fp)) != ',')
				{
					getch[i] = ch;
					i++;
				}
				CityCoord[n][j] = atoi(getch);	// 城市坐标
				memset(getch, 0, sizeof(char) * 100);
			}
			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				CityName[n][i] = ch;//城市名
				i++;
			}
			for (int j = 0; j < 12; j++)
			{

				i = 0;
				while ((ch = getc(fp)) != ',')
				{
					getch[i] = ch;
					i++;
				}
				CityResource[n][j] = atoi(getch);	// 城市资源
				memset(getch, 0, sizeof(char) * 100);
			}
			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			CityPopularfeel[n] = atoi(getch);	// 民心
			memset(getch, 0, sizeof(char) * 100);
			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			CityTax[n] = atoi(getch);	// 税率
			memset(getch, 0, sizeof(char) * 100);
			for (int j = 0; j < 20; j++)
			{

				i = 0;
				while ((ch = getc(fp)) != ',')
				{
					getch[i] = ch;
					i++;
				}
				CityArmy[n][j] = atoi(getch);	// 城市军队数
				memset(getch, 0, sizeof(char) * 100);
			}

			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			CityOfficerSum[n] = atoi(getch);	// 城市军官数
			memset(getch, 0, sizeof(char) * 100);
			for (int j = 0; j < CityOfficerSum[n]; j++)
			{
				i = 0;
				while ((ch = getc(fp)) != ',')
				{
					CityOfficerName[n][j][i] = ch;//城市军官名字
					i++;
				}
			}
			for (int m = 0; m < CityOfficerSum[n]; m++)
			{
				for (int j = 0; j < 7; j++)
				{
					i = 0;
					while ((ch = getc(fp)) != ',')
					{
						getch[i] = ch;
						i++;
					}
					CityOfficer[n][m][j] = atoi(getch);	// 城市军官信息
					memset(getch, 0, sizeof(char) * 100);
				}
			}

			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			CityWildSum[n] = atoi(getch);	// 城市野地数量
			memset(getch, 0, sizeof(char) * 100);
			for (int j = 0; j < CityWildSum[n]; j++)
			{
				for (int m = 0; m < 3; m++)
				{
					i = 0;
					while ((ch = getc(fp)) != ',')
					{
						getch[i] = ch;
						i++;
					}
					CityWild[n][j][m] = atoi(getch);	// 城市野地信息
					memset(getch, 0, sizeof(char) * 100);
				}
			}

			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			CityBuildSum[n] = atoi(getch);	// 城市建筑数量
			memset(getch, 0, sizeof(char) * 100);
			for (int j = 0; j < CityBuildSum[n]; j++)
			{
				for (int m = 0; m < 2; m++)
				{

					i = 0;
					while ((ch = getc(fp)) != ',')
					{
						getch[i] = ch;
						i++;
					}
					CityBuild[n][j][m] = atoi(getch);	// 城市建筑信息
					memset(getch, 0, sizeof(char) * 100);
					if (m == 1 && CityBuild[n][j][m] != 0)
					{
						i = 0;
						while ((ch = getc(fp)) != ',')
						{
							getch[i] = ch;
							i++;
						}
						CityBuildTime[n][j] = atoi(getch);	// 城市建筑建造开始时间
						memset(getch, 0, sizeof(char) * 100);
					}
				}
			}
			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			CityArmyBuildSum[n] = atoi(getch);	// 城市军工厂数量
			memset(getch, 0, sizeof(char) * 100);
		}
		
		/*城市信息循环结束*/
		
		
		for (int j = 0; j < SCIENCESUM; j++)//帐号科技信息循环
		{
			i = 0;
			while ((ch = getc(fp)) != ',')
			{
				getch[i] = ch;
				i++;
			}
			ScienceGrade[j] = atoi(getch);	// 科技等级信息
			memset(getch, 0, sizeof(char) * 100);
		}
	}//读取用户信息完毕
	fclose(fp);
}