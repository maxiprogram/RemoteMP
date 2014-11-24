// Client_Socket.cpp: файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "MAIN.h"
#include "Client_Socket.h"

#include <vector>
#include "tlhelp32.h"

using namespace std;

struct PROCESS
{
	PROCESSENTRY32 proc;
	vector<MODULEENTRY32> list_mod;
};

// Client_Socket

Client_Socket::Client_Socket(FORM_MAIN* f)
{
	forma=f;
}

Client_Socket::~Client_Socket()
{
}


// функции-члены Client_Socket


void Client_Socket::OnReceive(int nErrorCode)
{
	unsigned long cmd;
	Receive(&cmd,sizeof(cmd));
	switch (cmd)
	{
		case 0x0011:
		{
			FORM_MAIN* f=(FORM_MAIN*)forma;
			f->ClearListProc();
			vector<PROCESS>* list=(vector<PROCESS>*)f->list_proc;
			unsigned long countP;
			Receive(&countP,sizeof(countP));
			for (unsigned long i=0;i<countP;i++)
			{
				PROCESS Proc;
				PROCESSENTRY32 tmpP;
				Sleep(1);
				Receive(&tmpP,sizeof(PROCESSENTRY32));
				Proc.proc=tmpP;
				unsigned long countM;
				Receive(&countM,sizeof(countM));
				for (unsigned long j=0;j<countM;j++)
				{
					MODULEENTRY32 tmpM;
					Sleep(1);
					Receive(&tmpM,sizeof(MODULEENTRY32));
					Proc.list_mod.push_back(tmpM);
				}
				list->push_back(Proc);
			}
			f->PrintProc();
			//f->PrintModule();
			break;
		}
		case 0x0055:
		{
			TCHAR str[1024];
			Receive(&str[0],sizeof(TCHAR)*1024);
			FORM_MAIN* f=(FORM_MAIN*)forma;
			f->MessageBox(str);
		}
	}

	CSocket::OnReceive(nErrorCode);
}
