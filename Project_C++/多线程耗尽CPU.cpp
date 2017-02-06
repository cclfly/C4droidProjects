#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>
#include<pthread.h>
#include<sstream>
#include<pthread.h>
#include<math.h>
#define FLUSH_TIME 900000
#define MAX_CORE_NUMBER 4
using std::stringstream;
using std::endl;
unsigned int current_num[MAX_CORE_NUMBER] = { 0 };

int thread_end_flag = false;
int id = 0;

typedef struct CPUTimeInfo
{
	int idle;
	int user;
	int nice;
	int system_t;
	int iowait;
	int irq;
	int softirq;
	int CPUtime;
};


int GetCPUCoreNumber()
{
	int count = 0;
	char s[10] = { 0 };
	char str[255] = { 0 };
	FILE *file = NULL;
	file = fopen("/proc/stat", "r");
	int i = 0;
	int k = 0;
	for (i;; i++)
	{
		sprintf(s, "cpu%d", i);
		fseek(file, 0, SEEK_SET);
		for (k; !feof(file); k++)
		{
			fgets(str, 255, file);
			if (strstr(str, s) != NULL)
			{
				count++;
				break;
			}
		}
		if (strstr(str, s) == NULL)
			break;
	}
	fclose(file);
	return count;
}

CPUTimeInfo GetCPUTimeInfo(int index)
{
	CPUTimeInfo temp;
	char str[256] = { 0 };
	char s[10] = { 0 };
	FILE *file = NULL;
	file = fopen("/proc/stat", "r");
	fgets(str, 255, file);
	if (index)
		for (int i = 0; i < index; i++)
			fgets(str, 255, file);
	strtok(str, " ");
	temp.user = atoi(strtok(NULL, " "));
	temp.nice = atoi(strtok(NULL, " "));
	temp.system_t = atoi(strtok(NULL, " "));
	temp.idle = atoi(strtok(NULL, " "));
	temp.iowait = atoi(strtok(NULL, " "));
	temp.irq = atoi(strtok(NULL, " "));
	temp.softirq = atoi(strtok(NULL, " "));
	temp.CPUtime =
		temp.user + temp.nice + temp.system_t + temp.idle + temp.iowait +
		temp.irq + temp.softirq;
	fclose(file);
	return temp;
}

void *mem(void *data)
{
	int i = 0;
	stringstream *y = new stringstream();
	while (1)
	{
		*y << i++ << endl;
	}
}

int GetCPUIdleTime(CPUTimeInfo * cti)
{
	return cti->idle;
}

int GetCPUAllTime(CPUTimeInfo * cti)
{
	return cti->CPUtime;
}

int main()
{
	int coreNumber = GetCPUCoreNumber();
	pthread_t t[coreNumber];
	for (int i = 0; i < coreNumber; i++)
		pthread_create(&t[i], NULL, mem, NULL);
	CPUTimeInfo cti_start[MAX_CORE_NUMBER + 1];
	CPUTimeInfo cti_end[MAX_CORE_NUMBER + 1];
	int idleTime[MAX_CORE_NUMBER + 1] = { 0 };
	int allTime[MAX_CORE_NUMBER + 1] = { 0 };

	while (1)
	{
		coreNumber = GetCPUCoreNumber();
		printf("核心数:%d\n", coreNumber);
		for (int i = 0; i < MAX_CORE_NUMBER; i++)
			if (current_num[i] != 0)
				printf("id:%d 当前素数%d\n", i, current_num[i]);
		for (int i = 0; i <= coreNumber; i++)
			cti_start[i] = GetCPUTimeInfo(i);
		usleep(FLUSH_TIME);
		for (int i = 0; i <= coreNumber; i++)
			cti_end[i] = GetCPUTimeInfo(i);
		for (int i = 0; i <= coreNumber; i++)
		{
			idleTime[i] =
				GetCPUIdleTime(&cti_end[i]) - GetCPUIdleTime(&cti_start[i]);
			allTime[i] =
				GetCPUAllTime(&cti_end[i]) - GetCPUAllTime(&cti_start[i]);
		}
		clrscr();
		printf("总使用率:%lf%%\n",
			   ((((double)allTime[0] - idleTime[0]) / (allTime[0])) * 100));
		for (int i = 1; i <= coreNumber; i++)
		{
			double cpu =
				(((((double)allTime[i] - idleTime[i]) / (allTime[i])) * 100));
			printf("Core%d:%lf%%\n", i, cpu);
		}
		fflush(stdout);
	}
	return 0;
}//实时显示CPU使用率的版本