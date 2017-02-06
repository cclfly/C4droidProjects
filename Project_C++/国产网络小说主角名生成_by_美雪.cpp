#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

int main(){
	srand(time(nullptr));
	std::cout << "国产网络小说主角名生成："<<std::endl;
	char * words=
	             "殇琉璃安静明婉宛若皓子薰辰颜"
	             "影希江欧阳沫梦雨依梓晨伊希雪"
	             "欣蓝流苏心寒南宫薇瑾璟菁婧旌"
	             "慕泪舞浅容芷轩陌百沐楚楣凝霖";
	int size=strlen(words)/3;
	for (int i=0; i<200; i++){
		int namelen=rand()%2+2;
	    for (int j=0; j<namelen; j++){
	    	char* start=words+(rand()%size)*3;
	        for (int k=0; k<3; k++)
	        	std::cout << *(start+k);
	    }
	    std::cout << " ";
	}
}