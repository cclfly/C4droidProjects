#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
    string path = MDIR;
    string dir1 = path+"/include/SDL";
    string dir2 = path+"/lib";
    string note = "安装失败！请确认是否安装gcc插件和sdl插件。";
    bool error = false;
    string cmd1 = "cp -f ./SDL_draw.h "+dir1;
    string cmd2 = "cp -f ./libSDL_draw.a "+dir2;
    
    if(access(dir1.c_str(),F_OK|R_OK|W_OK)==0)
    {
        system(cmd1.c_str());
        cout<<"SDL_draw.h 复制安装成功！"<<endl;
    }
    else
    {
        cout<<"SDL_draw.h 复制安装失败！"<<endl;
        error = true;
    }
    if(access(dir2.c_str(),F_OK|R_OK|W_OK)==0)
    {
        system(cmd2.c_str());
        cout<<"libSDL_draw.lib 复制安装成功！"<<endl;
    }
    else
    {
        cout<<"libSDL_draw.lib 复制安装失败！"<<endl;
        error = true;
    }
    
    if(error)
    {
        cout<<note<<endl;
    }
    else
    {
        cout<<"安装成功！"<<endl;
    }
    
    return 0;
}