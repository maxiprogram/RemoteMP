#include <afxwin.h> 
#include "ManagerProcess.h"

ManagerProcess::ManagerProcess()
{
	Update();
}


ManagerProcess::~ManagerProcess()
{
	while (!list_proc.empty())
	{
		PROCESS tmp=list_proc.back();
		list_proc.pop_back();
		while (!tmp.list_mod.empty())
			tmp.list_mod.pop_back();
	}
}

void ManagerProcess::Update()
{
	while (!list_proc.empty())
	{
		PROCESS tmp=list_proc.back();
		list_proc.pop_back();
		while (!tmp.list_mod.empty())
			tmp.list_mod.pop_back();
	}
	HANDLE h=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 tmp_proc;
	tmp_proc.dwSize=sizeof(PROCESSENTRY32);
	if (Process32First(h,&tmp_proc))
	{
		PROCESS tmp;
		tmp.proc=tmp_proc;
		HANDLE hm=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,tmp_proc.th32ProcessID);
		MODULEENTRY32 tmp_mod;
		tmp_mod.dwSize=sizeof(MODULEENTRY32);
		if (Module32First(hm,&tmp_mod))
		{
			tmp.list_mod.push_back(tmp_mod);
			while (Module32Next(hm,&tmp_mod))
				tmp.list_mod.push_back(tmp_mod);
		}
		list_proc.push_back(tmp);
		CloseHandle(hm);
		while (Process32Next(h,&tmp_proc))
		{
			PROCESS tmp;
			hm=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,tmp_proc.th32ProcessID);
			tmp.proc=tmp_proc;
			if (Module32First(hm,&tmp_mod))
			{
				tmp.list_mod.push_back(tmp_mod);
				while (Module32Next(hm,&tmp_mod))
					tmp.list_mod.push_back(tmp_mod);
			}
			list_proc.push_back(tmp);
			CloseHandle(hm);
		}
	}
	CloseHandle(h);

}

bool ManagerProcess::DeleteProc(unsigned long pid)
{
	HANDLE kill=OpenProcess(PROCESS_ALL_ACCESS,false,pid);
	if (kill!=NULL)
	{
		TerminateProcess(kill,1);
		CloseHandle(kill);
		return true;
	}else
		return false;
}

vector<PROCESS> ManagerProcess::GetList()
{
	return list_proc;
}

bool ManagerProcess::SetPriority(unsigned long pid,unsigned long prior)
{
	HANDLE h=OpenProcess(PROCESS_ALL_ACCESS,false,pid);
	if (h!=NULL)
	{
		if (SetPriorityClass(h,prior))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool ManagerProcess::NewProc(TCHAR* name)
{
	STARTUPINFO info_s;
	ZeroMemory(&info_s,sizeof(info_s));
	info_s.cb=sizeof(info_s);
	PROCESS_INFORMATION info_p;
	ZeroMemory(&info_p,sizeof(info_p));
	if (CreateProcess(NULL,name,NULL,NULL,false,0,NULL,NULL,&info_s,&info_p))
		return true;
	else
		return false;
}