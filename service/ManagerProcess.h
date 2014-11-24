#pragma once

#include <vector>
#include "tlhelp32.h"

using namespace std;

struct PROCESS
{
	PROCESSENTRY32 proc;
	vector<MODULEENTRY32> list_mod;
};

class ManagerProcess
{
private:
	vector<PROCESS> list_proc;
public:
	ManagerProcess();
	~ManagerProcess();
	void Update();
	bool DeleteProc(unsigned long pid);
	vector<PROCESS> GetList();
	bool SetPriority(unsigned long pid,unsigned long prior);
	bool NewProc(TCHAR* name);
};

