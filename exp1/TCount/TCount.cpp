#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

DWORD WINAPI threadWork(LPVOID threadNo);
static int runFlag=TRUE;

void main(int argc, char* argv[])
{
	int count=0;
	DWORD targetThreadID;

	while(runFlag)
	{
		if(CreateThread(NULL,0,threadWork,NULL,0,&targetThreadID)==NULL)
		{
			runFlag=false;
			break;
		}
		else
			count++;
		printf("%d ",count);
	}
	Sleep(5000);
	printf("max threads num:%d\n",count);
	printf("Program ends successfully\n");
}

DWORD WINAPI threadWork(LPVOID threadNo)
{
	DWORD result=0;
	while(runFlag)
	{
	Sleep(100000);
	}
	//Terminate
	return result;
}
