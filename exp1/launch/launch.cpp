#include <windows.h>
#include <stdio.h>
#include <string.h>
#define MAX_LINE_LEN 80

int main(int argc,char* argv[])
{
	//local variables
	FILE* fid;
	char cmdLine[MAX_LINE_LEN];
	
	//CreateProcess parameters
	LPSECURITY_ATTRIBUTES processA=NULL;//Default
	LPSECURITY_ATTRIBUTES threadA=NULL;//Default
	BOOL shareRights=TRUE;//Default
	DWORD creationMask=CREATE_NEW_CONSOLE;//Window per process.
	LPVOID enviroment=NULL;//Default
	LPSTR curDir=NULL;//Default
	STARTUPINFO startInfo;//Result
	PROCESS_INFORMATION procInfo;//Result

	//1.Read the command line parameters
	if(argc!=2)
	{
		fprintf(stderr,"Usage:lanch<launch_set_filename>\n");
		exit(0);
	}

	//2.Open a file that coutain a set of commands
	fid=fopen(argv[1],"r");

	//3.For every command in the launch file
	while(fgets(cmdLine,MAX_LINE_LEN,fid)!=NULL)
	{
		//Read a command from the file
		if(cmdLine[strlen(cmdLine)-1]=='\n')
			cmdLine[strlen(cmdLine)-1]='\0';//Remove NEWLINE
		
		//Create a new process to execute the command
		ZeroMemory(&startInfo,sizeof(startInfo));
		startInfo.cb=sizeof(startInfo);
		if(!CreateProcess(
			NULL,//File name of executable
			cmdLine,//command line
			processA,//Process inherited security
			threadA, //Thread inherited security
			shareRights,//Rights propagation
			creationMask,//various creation flags
			enviroment,//Enviroment variable
			curDir,//Child's current directory
			&startInfo,
			&procInfo 
			)
		)
		{
			fprintf(stderr,"CreatProcess failed on error %d\n",GetLastError());
			ExitProcess(0);
		} 
	}
	//Terminate after all commands have finished.
	return 0;
}