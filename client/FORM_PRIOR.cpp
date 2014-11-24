// FORM_PRIOR.cpp: файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "FORM_PRIOR.h"
#include "MAIN.h"
#include "afxdialogex.h"


// диалоговое окно FORM_PRIOR

IMPLEMENT_DYNAMIC(FORM_PRIOR, CDialogEx)

FORM_PRIOR::FORM_PRIOR(CWnd* pParent /*=NULL*/)
	: CDialogEx(FORM_PRIOR::IDD, pParent)
{

}

FORM_PRIOR::~FORM_PRIOR()
{
}

void FORM_PRIOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ComboBox1);
}


BEGIN_MESSAGE_MAP(FORM_PRIOR, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &FORM_PRIOR::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений FORM_PRIOR


void FORM_PRIOR::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	ComboBox1.Clear();
	ComboBox1.AddString(TEXT("Низкий"));
	ComboBox1.AddString(TEXT("Ниже среднего"));
	ComboBox1.AddString(TEXT("Средний"));
	ComboBox1.AddString(TEXT("Выше среднего"));
	ComboBox1.AddString(TEXT("Высокий"));
	ComboBox1.AddString(TEXT("Реального времени"));
	ComboBox1.SetCurSel(0);
}


void FORM_PRIOR::OnBnClickedOk()
{	
	FORM_MAIN* f=(FORM_MAIN*)f_main;
	POSITION pos=f->m_ListP.GetFirstSelectedItemPosition();
	if (pos!=NULL)
	{
		int item=f->m_ListP.GetNextSelectedItem(pos);
		CString str=f->m_ListP.GetItemText(item,0);
		unsigned long pid=_tstoi(str.GetString());
		if (f->socket!=NULL)
		{
			switch (ComboBox1.GetCurSel())
			{
				case 0:
				{
					CSocket* s=(CSocket*)f->socket;
					unsigned long cmd=0x0044;
					unsigned long prior=IDLE_PRIORITY_CLASS;
					s->Send(&cmd,sizeof(cmd));
					s->Send(&pid,sizeof(pid));
					s->Send(&prior,sizeof(prior));
					break;
				}
				case 1:
				{
					CSocket* s=(CSocket*)f->socket;
					unsigned long cmd=0x0044;
					unsigned long prior=BELOW_NORMAL_PRIORITY_CLASS;
					s->Send(&cmd,sizeof(cmd));
					s->Send(&pid,sizeof(pid));
					s->Send(&prior,sizeof(prior));
					break;
				}
				case 2:
				{
					CSocket* s=(CSocket*)f->socket;
					unsigned long cmd=0x0044;
					unsigned long prior=NORMAL_PRIORITY_CLASS;
					s->Send(&cmd,sizeof(cmd));
					s->Send(&pid,sizeof(pid));
					s->Send(&prior,sizeof(prior));
					break;
				}
				case 3:
				{
					CSocket* s=(CSocket*)f->socket;
					unsigned long cmd=0x0044;
					unsigned long prior=ABOVE_NORMAL_PRIORITY_CLASS;
					s->Send(&cmd,sizeof(cmd));
					s->Send(&pid,sizeof(pid));
					s->Send(&prior,sizeof(prior));
					break;
				}
				case 4:
				{
					CSocket* s=(CSocket*)f->socket;
					unsigned long cmd=0x0044;
					unsigned long prior=HIGH_PRIORITY_CLASS;
					s->Send(&cmd,sizeof(cmd));
					s->Send(&pid,sizeof(pid));
					s->Send(&prior,sizeof(prior));
					break;
				}
				case 5:
				{
					CSocket* s=(CSocket*)f->socket;
					unsigned long cmd=0x0044;
					unsigned long prior=REALTIME_PRIORITY_CLASS;
					s->Send(&cmd,sizeof(cmd));
					s->Send(&pid,sizeof(pid));
					s->Send(&prior,sizeof(prior));
					break;
				}
			}
		}
	}else
		f->MessageBox(TEXT("Нет выделенной строки"));


	CDialogEx::OnOK();
}
