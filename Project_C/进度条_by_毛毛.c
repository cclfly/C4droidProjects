#include<stdio.h>
#include<unistd.h>

void ShowProgressBar(int progress,int len)
{
    printf("[");
    for(int i=0;i<len;++i)
    if(i<progress)printf("#");
    else printf(" ");
    printf("]%d%%\r",(int)((progress/(double)len)*100));
    fflush(stdout);
}

int main()
{
    for(int i=0;i<=40;i++)
    {
        ShowProgressBar(i,40);
        usleep(100000);
    }
}