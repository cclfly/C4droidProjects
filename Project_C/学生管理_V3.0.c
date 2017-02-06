/*
 *  此程序使用数据结构线性表的顺序储存（数组）的思想编写
 *  成绩均使用百分制，所以单人平均成绩未加权
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

#ifdef _WIN32
#define clrscr() system("cls")
#endif

#if(_MSC_VER>=1800)
#pragma warning (disable : 4996)
#endif

 //学生
typedef struct Student
{
	char ID[18];
	char name[16];
	float Chinese;
	float Math;
	float English;
	float Physics;
	float CLanguage;
	double sum;
	double average;
}Student;

//学生数组
typedef struct StuArr
{
	Student *students;
	int length;
}StuArr;

//排序比较的回调函数By总分(高到低)
int cmpBySum(const void *a, const void *b)
{
	return (int)(*(Student*)b).sum - (int)(*(Student*)a).sum;
}

//拷贝函数b-->a
void cpy(Student *a, Student b)
{
	strcpy((*a).ID, b.ID);
	strcpy((*a).name, b.name);
	(*a).Chinese = b.Chinese;
	(*a).Math = b.Math;
	(*a).English = b.English;
	(*a).Physics = b.Physics;
	(*a).CLanguage = b.CLanguage;
	(*a).average = b.average;
	(*a).sum = b.sum;
}

//学生成绩求和
double getSum(Student stu)
{
	return stu.sum = stu.Chinese + stu.Math + stu.English + stu.Physics + stu.CLanguage;
}

//学生成绩求平均
double getAve(Student stu)
{
	return stu.average = getSum(stu) / 5;
}

//输入
Student input()
{
	Student stu;

	printf("输入学号：\n\t");
	scanf("%s", stu.ID);
	printf("输入姓名：\n\t");
	scanf("%s", stu.name);
	printf("输入成绩：\n");
	printf("\t语文：");
	scanf("%f", &stu.Chinese);
	printf("\t数学：");
	scanf("%f", &stu.Math);
	printf("\t英语：");
	scanf("%f", &stu.English);
	printf("\t物理：");
	scanf("%f", &stu.Physics);
	printf("\tC语言：");
	scanf("%f", &stu.CLanguage);

	stu.sum = stu.Chinese + stu.Math + stu.English + stu.Physics + stu.CLanguage;
	stu.average = stu.sum / 5;

	return stu;
}

//输出
void output(Student stu)
{
	printf("资料：\n");
	printf("\t学号：\t%s\n", stu.ID);
	printf("\t姓名：\t%s\n", stu.name);
	printf("成绩：\n");
	printf("\t语文：\t%.2f\n", stu.Chinese);
	printf("\t数学：\t%.2f\n", stu.Math);
	printf("\t英语：\t%.2f\n", stu.English);
	printf("\t物理：\t%.2f\n", stu.Physics);
	printf("\tC语言：\t%.2f\n", stu.CLanguage);
	printf("合计：\n");
	printf("\t总分：\t%.2lf\n", stu.sum);
	printf("\t平均：\t%.2lf\n", stu.average);
}

//屏幕上输出学生数组
int outArr(StuArr ss)
{
	int i;//万恶的vc++6.0
	puts("\n-------------------------------------------------");
	for (i = 0; i < ss.length; i++)
	{
		output(ss.students[i]);
		puts("-------------------------------------------------");
	}
	return i;
}

//写入文件
int outFile(StuArr aStu)
{
	FILE *pf = NULL;
	int i = 0;//万恶的VC++6.0
	if ((pf = fopen("student.txt", "w")) == NULL)
	{
		printf("打开|创建文件失败！\n");
		return -1;
	}
	fprintf(pf, "%d\n----------------------------\n", aStu.length);
	for (i = 0; i < aStu.length; i++)
	{
		fprintf(pf, "+%s %s\n", aStu.students[i].ID, aStu.students[i].name);
		fprintf(pf,
			"Chinese:%.2f\n"
			"Math:%.2f\n"
			"English:%.2f\n"
			"Physics:%.2f\n"
			"CLanguage:%.2f\n"
			"=sum:%.2f\n"
			"=average:%.2f\n",
			aStu.students[i].Chinese, aStu.students[i].Math, aStu.students[i].English, aStu.students[i].Physics, aStu.students[i].CLanguage, aStu.students[i].sum, aStu.students[i].average);
		fputs("----------------------------\n", pf);
	}
	fclose(pf);
	return 0;
}

//从文件读取
StuArr inFile()
{
	FILE *pf = NULL;
	int i = 0;
	char tmp[255];
	memset(tmp, 0, 255);
	if ((pf = fopen("student.txt", "r")) == NULL)
	{
		fclose(fopen("student.txt", "w"));
		//printf("打开|创建文件失败！\n");
		return (StuArr) { NULL, 0 };
	}
	StuArr aStu = { 0 };
	fscanf(pf, "%d", &aStu.length);
	aStu.students = (Student*)malloc(sizeof(Student)*aStu.length);
	for (i = 0; i < aStu.length; i++)
	{
		while (fgetc(pf) != '+');
		fscanf(pf, "%s%s", aStu.students[i].ID, aStu.students[i].name);
		while (fgetc(pf) != ':');
		fscanf(pf, "%f", &aStu.students[i].Chinese);
		while (fgetc(pf) != ':');
		fscanf(pf, "%f", &aStu.students[i].Math);
		while (fgetc(pf) != ':');
		fscanf(pf, "%f", &aStu.students[i].English);
		while (fgetc(pf) != ':');
		fscanf(pf, "%f", &aStu.students[i].Physics);
		while (fgetc(pf) != ':');
		fscanf(pf, "%f", &aStu.students[i].CLanguage);

		aStu.students[i].sum = aStu.students[i].Chinese + aStu.students[i].Math + aStu.students[i].English + aStu.students[i].Physics + aStu.students[i].CLanguage;
		aStu.students[i].average = aStu.students[i].sum / 5;
	}
	fclose(pf);
	return aStu;
}

//通过总成绩排序
void sortStuBySum(StuArr aStu)
{
	qsort(aStu.students, aStu.length, sizeof(Student), cmpBySum);
}

//通过ID查找，返回索引，失败返回-1
int findStuById(StuArr aStu, const char *id)
{
	int i;
	for (i = 0; i < aStu.length; i++)
	{
		if (!strcmp(aStu.students[i].ID, id))
		{
			return i;
		}
	}
	return -1;
}

//用ID查询顺序表，返回该元素，失败返回全0(NULL)
Student getStuById(StuArr aStu, const char *id)
{
	int i;
	if ((i = findStuById(aStu, id)) != -1)
	{
		return aStu.students[i];
	}
	printf("查询失败\n");
	return (Student) { 0 };
}

//向顺序表中添加元素到末尾
int addStu(StuArr *aStu, Student stu)
{
	if (realloc((*aStu).students, sizeof(Student)*((*aStu).length + 1)) == NULL)
		exit(-1);
	cpy(&(*aStu).students[(*aStu).length], stu);
	(*aStu).length++;

	sortStuBySum(*aStu);
	outFile(*aStu);

	return 0;
}

//从顺序表中删除元素,失败返回负数
int delStu(StuArr *aStu, int n)
{
	int i;
	if (n < 0 || n >= (*aStu).length)
	{
		printf("error:索引值不在表中\n");
		return -2;
	}
	for (i = n; i < (*aStu).length - 1; i++)
	{
		cpy(&(*aStu).students[i], (*aStu).students[i + 1]);
	}
	if (realloc((*aStu).students, sizeof(Student)*((*aStu).length - 1)) == NULL)
	{
		printf("更改内存失败！\n");
		return -1;
	}
	(*aStu).length--;

	sortStuBySum(*aStu);
	outFile(*aStu);

	return 0;
}

//销毁顺序表
void dropStuArr(StuArr *aStu)
{
	free((*aStu).students);
	(*aStu).students = NULL;
	(*aStu).length = 0;
}

//修改顺序表中的某元素，通过索引定位
int updateStu(StuArr aStu, int n)
{
	if (n < 0 || n >= aStu.length)
	{
		printf("索引值超出范围，更新数据失败\n");
		return -2;
	}
	printf("学号：\n\t%s\n", aStu.students[n].ID);
	printf("信息：\n");
	printf("\t姓名：%s  -->  :", aStu.students[n].name);
	scanf("%s", aStu.students[n].name);
	printf("成绩：\n");
	printf("\t语文：%f  \t-->  :", aStu.students[n].Chinese);
	scanf("%f", &aStu.students[n].Chinese);
	printf("\t数学：%f  \t-->  :", aStu.students[n].Math);
	scanf("%f", &aStu.students[n].Math);
	printf("\t英语：%f  \t-->  :", aStu.students[n].English);
	scanf("%f", &aStu.students[n].English);
	printf("\t物理：%f  \t-->  :", aStu.students[n].Physics);
	scanf("%f", &aStu.students[n].Physics);
	printf("\tC语言：%f  \t-->  :", aStu.students[n].CLanguage);
	scanf("%f", &aStu.students[n].CLanguage);

	aStu.students[n].sum = getSum(aStu.students[n]);
	aStu.students[n].average = getAve(aStu.students[n]);

	sortStuBySum(aStu);
	outFile(aStu);

	return 0;
}

//以下写UI(伪)

//单人操作菜单
int conMenu(StuArr *aStu, int i)
{
	puts("===============================================================================================");
	printf("%16s\t%16s\t%16s\t%16s\n:", "1.修改", "2.删除", "", "0.返回");
	switch (getch())
	{
	case'0':
		return 0;
		break;
	case'1':
		clrscr();
		updateStu(*aStu, i);
		return 0;
		break;
	case'2':
		printf("确定？(or N):");
		switch (getch())
		{
		case'y':
		case'Y':
		case'\n':
		case'\r':
			delStu(aStu, i);
			return 0;
			break;
		default:
			break;
		}
	default:
		break;
	}
	return 1;
}

//以列表显示数组
void listView(StuArr *aStu)
{
	printf("%10s%10s%10s%10s%10s%10s%10s%10s%10s\n", "排名", "姓名 ", "语文 ", "数学 ", "英语 ", "物理 ", "C语言", "总分 ", "平均分");
	for (int i = 0; i < (*aStu).length; i++)		//不管vc++6.0了！
	{
		printf("%10d%10s%10.2f%10.2f%10.2f%10.2f%10.2f%10.2lf%10.2lf\n", i + 1, (*aStu).students[i].name, (*aStu).students[i].Chinese, (*aStu).students[i].Math, (*aStu).students[i].English, (*aStu).students[i].Physics, (*aStu).students[i].CLanguage, (*aStu).students[i].sum, (*aStu).students[i].average);
	}
}

//列表视图的菜单
int listViewMenu(StuArr *aStu)
{
	puts("===============================================================================================");
	printf("%16s\t%16s\t%16s\t%16s\n:", "1.详细信息", "2.条件查找*", "", "0.返回");
	switch (getch())
	{
	case'0':
		return 0;
		break;
	case'1':;
		int i;
		printf("请输入目标排名：");
		scanf("%d", &i);
		do {
			clrscr();
			output((*aStu).students[i - 1]);
		}while(conMenu(aStu, i - 1));
		break;
	default:
		break;
	}
	return 1;
}

//主菜单
int menu(StuArr *aStu)
{
	puts("===============================================================================================");
	printf("%16s\t%16s\t%16s\t%16s\n:", "1.添加记录", "2.查看列表", "3.条件查找*", "0.退出系统");
	switch (getch())
	{
	case '0':
		dropStuArr(aStu);
		exit(0);
		break;
	case '1':
		clrscr();
		addStu(aStu, input());
		sortStuBySum(*aStu);
		outFile(*aStu);
		break;
	case '2':
		do {
			clrscr();
			listView(aStu);
		}while(listViewMenu(aStu));
		break;
	case '3':
		break;
	default:;
	}
	return 0;
}

//引导(入口)
void boot()
{
	StuArr aStu = inFile();
	clrscr();
	printf("\n\t系统已记录%5d  条信息\n\n", aStu.length);
	menu(&aStu);
	dropStuArr(&aStu);
}

int main()
{
	while (1)
		boot();
	return 0;
}