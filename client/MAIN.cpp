
// MAIN.cpp : файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "MAIN.h"
#include "FORM_SETTING.h"
#include "FORM_CONNECT.h"
#include "FORM_NEW.h"
#include "FORM_FIND.h"
#include "FORM_PRIOR.h"
#include "Client_Socket.h"
#include "afxdialogex.h"

#include <vector>
#include "tlhelp32.h"

using namespace std;

struct PROCESS
{
	PROCESSENTRY32 proc;
	vector<MODULEENTRY32> list_mod;
};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно FORM_MAIN




FORM_MAIN::FORM_MAIN(CWnd* pParent /*=NULL*/)
	: CDialogEx(FORM_MAIN::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void FORM_MAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListP);
	DDX_Control(pDX, IDC_LIST2, m_ListM);
}

BEGIN_MESSAGE_MAP(FORM_MAIN, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32775, &FORM_MAIN::On32775)
	ON_COMMAND(ID_32771, &FORM_MAIN::On32771)
	ON_COMMAND(ID_32772, &FORM_MAIN::On32772)
	ON_WM_TIMER()
	ON_COMMAND(ID_32776, &FORM_MAIN::On32776)
	ON_WM_CLOSE()
	ON_COMMAND(ID_32774, &FORM_MAIN::On32774)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &FORM_MAIN::OnNMClickList1)
	ON_COMMAND(ID_32773, &FORM_MAIN::On32773)
	ON_COMMAND(ID_32778, &FORM_MAIN::On32778)
	ON_COMMAND(ID_32777, &FORM_MAIN::On32777)
END_MESSAGE_MAP()


// обработчики сообщений FORM_MAIN

BOOL FORM_MAIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	CRect rect;
	GetClientRect(&rect);
	//m_List.Create(WS_CHILD|LVS_REPORT|WS_VISIBLE,rect,this,IDC_LIST1);
	m_ListP.ModifyStyle(0,WS_CHILD|LVS_REPORT|WS_VISIBLE);
	m_ListP.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListP.InsertColumn(0,TEXT("PID"),0,120);
	m_ListP.InsertColumn(1,TEXT("Имя процесса"),0,120);
	m_ListP.InsertColumn(2,TEXT("PID родителя"),0,120);
	m_ListP.InsertColumn(3,TEXT("Потоки"),0,80);
	m_ListP.InsertColumn(4,TEXT("Приоритет"),0,80);

	m_ListM.ModifyStyle(0,WS_CHILD|LVS_REPORT|WS_VISIBLE);
	m_ListM.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ListM.InsertColumn(0,TEXT("PID"),0,120);
	m_ListM.InsertColumn(1,TEXT("Имя модуля"),0,120);
	m_ListM.InsertColumn(2,TEXT("Путь модуля"),0,120);
	m_ListM.InsertColumn(3,TEXT("Размер"),0,120);
	socket=NULL;
	list_proc=new vector<PROCESS>();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void FORM_MAIN::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR FORM_MAIN::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void FORM_MAIN::On32775()
{
	//MessageBox(TEXT("W"),TEXT("W"),0);
	FORM_SETTING f;
	f.f_main=this;
	f.DoModal();
}


void FORM_MAIN::On32771()
{
	FORM_CONNECT f;
	f.f_main=this;
	f.DoModal();
}


void FORM_MAIN::On32772()
{
	KillTimer(ID_TIMER);
	if (socket!=NULL)
	{
		unsigned long cmd=0x00ff;
		Client_Socket* b=(Client_Socket*)socket;
		b->Send(&cmd,sizeof(cmd));
		b->Close();
		delete b;
		socket=NULL;
	}
	SetWindowText(TEXT("Удаленный диспетчер --Нет подключения!--"));
}


void FORM_MAIN::OnTimer(UINT_PTR nIDEvent)
{
	//MessageBox(TEXT("TIMER"));
	unsigned long cmd=0x0011;//Update
	if (socket!=NULL)
	{
		Client_Socket* s=(Client_Socket*)socket;
		s->Send(&cmd,sizeof(unsigned long));
	}

	CDialogEx::OnTimer(nIDEvent);
}


void FORM_MAIN::On32776()
{
	unsigned long cmd=0x0011;
	if (socket!=NULL)
	{
		Client_Socket* s=(Client_Socket*)socket;
		s->Send(&cmd,sizeof(unsigned long));
	}
}


void FORM_MAIN::OnClose()
{
	if (socket!=NULL)
	{
		unsigned long cmd=0x00ff;
		Client_Socket* b=(Client_Socket*)socket;
		b->Send(&cmd,sizeof(cmd));
		b->Close();
		delete b;
		socket=NULL;
	}
	void ClearListProc();
	delete list_proc;

	CDialogEx::OnClose();
}


void FORM_MAIN::On32774()
{
	unsigned long cmd=0x0022; //Delete
	POSITION pos=m_ListP.GetFirstSelectedItemPosition();
	if (pos!=NULL)
	{
		int item=m_ListP.GetNextSelectedItem(pos);
		CString str=m_ListP.GetItemText(item,0);
		unsigned long pid=_tstoi(str.GetString());
		if (socket!=NULL)
		{
			CSocket* s=(CSocket*)socket;
			s->Send(&cmd,sizeof(cmd));
			s->Send(&pid,sizeof(pid));
		}
		m_ListP.DeleteItem(item);
	}else
		MessageBox(TEXT("Нет выделенной строки"));
}

void FORM_MAIN::PrintProc()
{
	vector<PROCESS>* list=(vector<PROCESS>*)list_proc;
	m_ListP.DeleteAllItems();
	vector<PROCESS>::iterator it;
	unsigned long i=0;
	for (it=list->begin();it!=list->end();it++)
	{
		CString str;
		str.Format(TEXT("%d"),it->proc.th32ProcessID);
		m_ListP.InsertItem(i,str);
		str.Format(TEXT("%s"),it->proc.szExeFile);
		m_ListP.SetItemText(i,1,str);
		str.Format(TEXT("%d"),it->proc.th32ParentProcessID);
		m_ListP.SetItemText(i,2,str);
		str.Format(TEXT("%d"),it->proc.cntThreads);
		m_ListP.SetItemText(i,3,str);
		str.Format(TEXT("%d"),it->proc.pcPriClassBase);
		m_ListP.SetItemText(i,4,str);
		i++;
	}
	CString str;str.Format(TEXT("%d"),list->size());
	SetDlgItemText(IDC_C_P,str);
}


void FORM_MAIN::ClearListProc()
{
	vector<PROCESS>* list=(vector<PROCESS>*)list_proc;
	while (!list->empty())
	{
		PROCESS tmp=list->back();
		list->pop_back();
		while (!tmp.list_mod.empty())
			tmp.list_mod.pop_back();
	}
}

void FORM_MAIN::PrintModule(unsigned long pid)
{
	vector<PROCESS>* list=(vector<PROCESS>*)list_proc;
	vector<PROCESS>::iterator it;
	unsigned long i=0;
	for (it=list->begin();it!=list->end();it++)
	{
		if (it->proc.th32ProcessID==pid)
		{
			vector<MODULEENTRY32>::iterator itm;
			for (itm=it->list_mod.begin();itm!=it->list_mod.end();itm++)
			{
				CString str;str.Format(TEXT("%d"),itm->th32ProcessID);
				m_ListM.InsertItem(i,str);
				str.Format(TEXT("%s"),itm->szModule);
				m_ListM.SetItemText(i,1,str);
				str.Format(TEXT("%s"),itm->szExePath);
				m_ListM.SetItemText(i,2,str);
				str.Format(TEXT("%d"),itm->modBaseSize);
				m_ListM.SetItemText(i,3,str);
				i++;
			}
			break;
		}
	}
	CString str;str.Format(TEXT("%d"),i);
	SetDlgItemText(IDC_C_M,str);
}

void FORM_MAIN::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	m_ListM.DeleteAllItems();
	POSITION pos=m_ListP.GetFirstSelectedItemPosition();
	if (pos!=NULL)
	{
		int item=m_ListP.GetNextSelectedItem(pos);
		CString str=m_ListP.GetItemText(item,0);
		unsigned long pid=_tstoi(str.GetString());
		PrintModule(pid);
	}
		

	*pResult = 0;
}


void FORM_MAIN::On32773()
{
	FORM_NEW f;
	f.f_main=this;
	f.DoModal();
}

void FORM_MAIN::On32778()
{
	FORM_FIND f;
	f.f_main=this;
	f.DoModal();
}


void FORM_MAIN::On32777()
{
	POSITION pos=m_ListP.GetFirstSelectedItemPosition();
	if (pos!=NULL)
	{
		FORM_PRIOR f;
		f.f_main=this;
		f.DoModal();
	}else
		MessageBox(TEXT("Нет выделенной строки"));
}
