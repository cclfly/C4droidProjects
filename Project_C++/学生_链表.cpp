#include<iostream>
#include<cstring>
#include<cstdlib>
#include<locale>
using namespace std;
#include<conio.h>
class student
{
  public:
	char num[15];
	wchar_t name[4];
	student *next;
};
student *head = NULL;
student *slink()
{
	student *p1, *p2;
	p1 = new student;
	head = p1;
	p2 = p1;
	cout << "请输入学号，以0结束" << endl;
	cin >> p1->num;
	if (strcmp(p1->num, "0"))
	{
		cout << "请输入学生姓名：" << endl;
		wcin >> p1->name;
	}
	else
	{
		delete p1;
		p2->next = NULL;
		p2 = NULL;
		head = NULL;
		return head;
	}
	while (strcmp(p1->num, "0"))
	{
		clrscr();
		p2 = p1;
		p1 = new student;
		cout << "请输入学号，以0结束" << endl;
		cin >> p1->num;
		if (strcmp(p1->num, "0"))
		{
			cout << "请输入学生姓名：" << endl;
			wcin >> p1->name;
		}
	}
	delete p1;
	p2->next=NULL;
	return head;
}
void plink(student *head)
{
	clrscr();
	while(head)
	{
		cout<<"***********************************"
		<<endl
		<<"学号："<<head->num
		<<endl
		<<"姓名：";
		wcout<<head->name;
		cout<<endl;
		head=head->next;
	}
}
int main()
{
	setlocale(LC_ALL,"chs");
	student *head=NULL;
	head=slink();
	plink(head);
	return 0;
}