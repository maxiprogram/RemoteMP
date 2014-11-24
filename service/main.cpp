//#define _AFXDLL


#include <afxwin.h> 
//#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "ManagerProcess.h"


using namespace std;


LPTSTR ServiceName=TEXT("TihonovRMP");
SERVICE_STATUS_HANDLE ssHandle;
SERVICE_STATUS ss;
DWORD Port=2207;
bool kill=false;
SOCKET ssock;
ManagerProcess mp;

void WINAPI ServiceMain(int,LPTSTR*);
void WINAPI ServiceControl(DWORD);
void SetSomeServiceStatus(DWORD,DWORD,DWORD);
void InitSomeServiceData(int,LPTSTR*);
void StopSomeService();

UINT OnAccept(LPVOID);
UINT OnRead(LPVOID);


void main(int argc,LPTSTR argv[])
{

	SERVICE_TABLE_ENTRY DispatcherTable[]={{ServiceName,(LPSERVICE_MAIN_FUNCTION)ServiceMain},{NULL,NULL}};
	
	if(!StartServiceCtrlDispatcher(DispatcherTable))
	{
		printf("StartServiceCtrlDispatcher: Error %ld\n",GetLastError());
		getch();
		return;
   }

}

void WINAPI ServiceMain(int argc,LPTSTR argv[])
{
	ssHandle=RegisterServiceCtrlHandler(ServiceName,ServiceControl);
	if(!ssHandle)
	{
		printf("Error registering ServiceControl\n");
		getch();
		return;
	}

	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
	SetSomeServiceStatus(SERVICE_START_PENDING,NO_ERROR,4000);
	InitSomeServiceData(argc,argv);
	SetSomeServiceStatus(SERVICE_RUNNING,NO_ERROR,0);

	if (!AfxWinInit(::GetModuleHandle(NULL),NULL,::GetCommandLine(),0))
	{
		printf("MFC Failed to initialize.\n");
		getch();
		return;
	}

	WSADATA WsaData;
	int err=WSAStartup(0x0101,&WsaData);
	if (err==SOCKET_ERROR)
	{
           printf ("WSAStartup() failed: %ld\n",GetLastError());
		   getch();
           return;
	}


	CRegKey key(HKEY_CURRENT_USER);
	LONG status=key.Open(HKEY_CURRENT_USER,TEXT("Software\\TihonovM\\service"));
	if (status==ERROR_SUCCESS)
	{
		status=key.QueryDWORDValue(TEXT("port"),Port);
		if (status!=ERROR_SUCCESS)
			key.SetDWORDValue(TEXT("port"),Port);
	}else
	{
		status=key.Create(HKEY_CURRENT_USER,TEXT("Software\\TihonovM\\service"));
		status=key.SetDWORDValue(TEXT("port"),Port);
	}
	key.Close();


	ssock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	SOCKADDR_IN adress;
	adress.sin_family=AF_INET;
	adress.sin_port=htons(Port);
	adress.sin_addr.s_addr=htonl(INADDR_ANY);//inet_addr("192.168.1.2");//htonl(INADDR_ANY);

	if (bind(ssock,(sockaddr*)&adress,sizeof(adress))==-1)
	{
		printf ("bind() failed\n");
		getch();
        return;
	}

	if (listen(ssock,10)==0)
		AfxBeginThread(OnAccept,(LPVOID)&ssock);
}

void WINAPI ServiceControl(DWORD dwControlCode)
{
	switch(dwControlCode)
	{
		case SERVICE_CONTROL_STOP:
		{
			SetSomeServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
			StopSomeService();
			SetSomeServiceStatus(SERVICE_STOPPED,NO_ERROR,0);
			break;
		}

		case SERVICE_CONTROL_INTERROGATE:
		{
			SetSomeServiceStatus(ss.dwCurrentState,NO_ERROR,0);
			break;
		}
		default:
		{
			SetSomeServiceStatus(ss.dwCurrentState,NO_ERROR,0);
			break;
		}
	}
}

void SetSomeServiceStatus(DWORD dwCurrentState,DWORD dwWin32ExitCode,DWORD dwWaitHint)
{
	static DWORD dwCheckPoint=1;
	if(dwCurrentState==SERVICE_START_PENDING)
		ss.dwControlsAccepted=0;
	else
		ss.dwControlsAccepted=SERVICE_ACCEPT_STOP;
   
	ss.dwCurrentState=dwCurrentState;
	ss.dwWin32ExitCode=dwWin32ExitCode;
	ss.dwWaitHint=dwWaitHint;

	if(dwCurrentState==SERVICE_RUNNING || dwCurrentState==SERVICE_STOPPED)
		ss.dwCheckPoint=0;
	else
		ss.dwCheckPoint=dwCheckPoint++;
	
	SetServiceStatus(ssHandle,&ss);
}

void InitSomeServiceData(int,LPTSTR*)
{

	return;
}
void StopSomeService()
{
	kill=true;
	return;
}

UINT OnAccept(LPVOID p)
{
	SOCKET* s=(SOCKET*)p;
	SOCKET csock;
	SOCKADDR_IN adress;
	int size=sizeof(adress);
	while (!kill)
	{
		csock=accept(*s,(sockaddr*)&adress,&size);
		AfxBeginThread(OnRead,(LPVOID)&csock);
	}
	return 0;
}

UINT OnRead(LPVOID p)
{
	bool exit=false;
	unsigned long cmd;
	SOCKET* s=(SOCKET*)p;
	while (!kill && !exit)
	{
		while(recv(*s,(char*)&cmd,sizeof(cmd),0)!=SOCKET_ERROR && !exit)
		{
			switch(cmd)
			{
				case 0x0011://Update
				{
					mp.Update();
					vector<PROCESS> list=mp.GetList();
					unsigned long count=list.size();
					send(*s,(char*)&cmd,sizeof(cmd),0);
					send(*s,(char*)&count,sizeof(count),0);
					while (!list.empty())
					{
						PROCESS tmpP=list.back();
						list.pop_back();
						send(*s,(char*)&tmpP.proc,sizeof(PROCESSENTRY32),0);
						unsigned long countDLL=tmpP.list_mod.size();
						send(*s,(char*)&countDLL,sizeof(countDLL),0);
						while (!tmpP.list_mod.empty())
						{
							MODULEENTRY32 tmpM=tmpP.list_mod.back();
							tmpP.list_mod.pop_back();
							send(*s,(char*)&tmpM,sizeof(MODULEENTRY32),0);
						}
					}
					break;
				}
				case 0x00ff:
				{
					exit=true;
					break;
				}
				case 0x0022://Delete
				{
					unsigned long pid;
					recv(*s,(char*)&pid,sizeof(pid),0);
					if (mp.DeleteProc(pid))
					{
						unsigned long cmdd=0x0055;
						TCHAR msg[1024]=TEXT("Процесс завершен");
						send(*s,(char*)&cmdd,sizeof(cmdd),0);
						send(*s,(char*)&msg[0],sizeof(TCHAR)*1024,0);
					}else
					{
						unsigned long cmdd=0x0055;
						TCHAR msg[1024]=TEXT("Процесс неудолось завершить!");
						send(*s,(char*)&cmdd,sizeof(cmdd),0);
						send(*s,(char*)&msg[0],sizeof(TCHAR)*1024,0);
					}
					break;
				}
				case 0x0033://New
				{
					TCHAR name[1024];
					recv(*s,(char*)&name[0],sizeof(TCHAR)*1024,0);
					if (mp.NewProc(&name[0]))
					{
						unsigned long cmdd=0x0055;
						TCHAR msg[1024]=TEXT("Процесс запущен");
						send(*s,(char*)&cmdd,sizeof(cmdd),0);
						send(*s,(char*)&msg[0],sizeof(TCHAR)*1024,0);
					}
					else
					{
						unsigned long cmdd=0x0055;
						TCHAR msg[1024]=TEXT("Процесс неудолось запустить!");
						send(*s,(char*)&cmdd,sizeof(cmdd),0);
						send(*s,(char*)&msg[0],sizeof(TCHAR)*1024,0);
					}
					break;
				}
				case 0x0044://Prior
				{
					unsigned long pid,prior;
					recv(*s,(char*)&pid,sizeof(pid),0);
					recv(*s,(char*)&prior,sizeof(prior),0);
					if (mp.SetPriority(pid,prior))
					{
						unsigned long cmdd=0x0055;
						TCHAR msg[1024]=TEXT("Приоритет процесса изменён");
						send(*s,(char*)&cmdd,sizeof(cmdd),0);
						send(*s,(char*)&msg[0],sizeof(TCHAR)*1024,0);	
					}else
					{
						unsigned long cmdd=0x0055;
						TCHAR msg[1024]=TEXT("Приоритет процесса не изменён!");
						send(*s,(char*)&cmdd,sizeof(cmdd),0);
						send(*s,(char*)&msg[0],sizeof(TCHAR)*1024,0);
					}
					break;
				}
				
			}
		}
	}
	return 0;
}