/*
test threadNo runSecs 
*/

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define Type float

static int runFlag=TRUE;

DWORD WINAPI threadWork(LPVOID threadNo);
int parseArgToInt(char* inNumChar);
Type eRandom(int upLimit);

typedef struct
{
	int data;
}INTEGER;

void main(int argc, char* argv[])
{
	unsigned int runTime;
	int i;
	int threadNum;
	//int N;

	SYSTEMTIME now;
	WORD stopTimeMinute,stopTimeSecond;
	DWORD targetThreadID;

	//Get command line argument£¬N

	if(argc!=3)
	{
		printf("please enter:NThread <ThreadNum> <runTime>\n");
		return;
	}

	threadNum=parseArgToInt(argv[1]);
	runTime=parseArgToInt(argv[2]);
	//Get the time the threads should run£¬runtime
	//Calculate time to halt
	// runTime=60;/*in seconds.*/

	GetSystemTime(&now);
	printf("mthread:Suite starting aty system time%d£¬%d£¬%d\n",now.wHour,now.wMinute,now.wSecond);
	stopTimeSecond=(now.wSecond+(WORD)runTime)%60;

	stopTimeMinute=now.wMinute+(now.wSecond+(WORD)runTime)/60;

	//FOR 1 TO N

	INTEGER* tmpInt;

	for(i=0;i<threadNum;i++)
	{
		//CREATE A NEW THREAD TO EXECUTE SIMULATED WORK;
		//threadWork(i);

		tmpInt=(INTEGER*)malloc(sizeof(INTEGER));
		tmpInt->data=i;
		CreateThread(NULL,0,threadWork,tmpInt,0,&targetThreadID);
		Sleep(100);//Let newly created thread run
	}

	//Cycle while children work...

	while(runFlag)
	{
		GetSystemTime(&now);
		if((now.wMinute>=stopTimeMinute)&&(now.wSecond>=stopTimeSecond))
		runFlag=FALSE;
		Sleep(1000);
	}
	Sleep(5000);
	printf("Program ends successfully\n");
}

DWORD WINAPI threadWork(LPVOID threadNo)
{
	//local variables
	double y;
	const double x=3.14159;
	const double e=2.7183;
	int i;
	const int napTime=1000;//in milliseconds
	const int busyTime=400;
	int tNo=((INTEGER*)threadNo)->data;
	int sleepTime;
	DWORD result=0;

	/*randomasize the random num seeds.*/

	srand((unsigned int)time (NULL));

	while(runFlag)
	{
		//Parameterized processor burst phase
		for(i=0;i<busyTime;i++)
		y=pow(x,e);

		//Parameterized sleep phase

		sleepTime=1000+30*(int)eRandom(50+tNo);
		Sleep(sleepTime);
		printf("I am thread No.%d£¬sleep sec:%ds\n",tNo,sleepTime);
	}

	//Terminate
	return result;
}

int parseArgToInt(char* inNumChar)
{
	int equipData=0,i=0;
	while(inNumChar[i]>='0'&&inNumChar[i]<='9')
	{
		equipData=10*equipData+(inNumChar[i]-48);
		i++;
	}
	return equipData;
}

Type eRandom(int upLimit)
{
	Type tmpData;
	do
	{
		tmpData=((Type)rand()/(Type)32767)*(Type)100.0*(Type)upLimit;
	}
	while(tmpData>upLimit);
	return tmpData;
}
