/**
 * @brief 表达式转逆波兰式
 * @author cclfly
 * @version 0.0.1
 * 11月19日14:51 开坑
 */
#include <iostream>
#include <stack>

using namespace std;

enum class SymbolType{number};

SymbolType symType(string symbol)
{
	return SymbolType(0);
}

void func(string str)
{
	str += '#';
	string tmp;
	stack<string> stk;
	for (int i=0;i<str.length();i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			tmp += str[i];
		}
		else
		{
			stk.push(tmp);
			cout << tmp << endl;
			tmp.clear();
		}
	}
}

int main()
{
	string str;
	cin>>str;
	cout << "< " << str;
	/*cout << "> " << */func(str);
	return 0;
}