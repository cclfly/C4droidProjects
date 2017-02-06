/*
 * 阴爻 - 1
 * 阳爻 - 0
 * 乾三连 - 7 - 0
 * 坤六断 - 0 - 7
 * 震仰盂 - 4 - 3
 * 艮覆碗 - 1 - 6
 * 离中虚 - 5 - 2
 * 坎中满 - 2 - 5
 * 兑上缺 - 6 - 1
 * 巽下断 - 3 - 4
 */

#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <cstdlib>
#include <cmath>
using namespace std;
map<int,string> FuXi{
	{0,"乾"},
	{1,"兑"},
	{2,"离"},
	{3,"震"},
	{4,"巽"},
	{5,"坎"},
	{6,"艮"},
	{7,"坤"}
};
int main()
{
	bitset<3> BaGua=rand()%7;
	cout<<FuXi[BaGua.to_ulong()]<<endl;
	return 0;
}