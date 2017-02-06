#include<dlfcn.h>

int main()
{
	void* hptr=dlopen("/system/lib/libc.so",RTLD_LAZY);
	if(hptr==0)return -1;
	int(*fuck)(char*)=(int(*)(char*))dlsym(hptr,"puts");
	fuck("无形装逼，最为致命");
	dlclose(hptr);
	return 0;
}