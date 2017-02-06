#include <iostream>
using namespace std;

class Car{
public:
	virtual void drive()
	{
		cout<<"应该走路"<<endl;
	}
};

class bmCar:public Car{
public:
	void drive()
	{
		cout<<"开宝马车"<<endl;
	}
};

class bcCar:public Car{
public:
	void drive()
	{
		cout<<"开奔驰车"<<endl;
	}
};

class Drives{
public:
	static Car *use(const char *car)
	{
		if(!strcmp(car,"bm"))
			return new bmCar;
		else if(!strcmp(car,"bc"))
		    return new bcCar;
		return new Car;
	}
};

int main()
{
	Car *car = Drives::use("bm");
	car->drive();
	return 0;
}