// FORM_FIND.cpp: файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "FORM_FIND.h"
#include "MAIN.h"
#include "afxdialogex.h"

#include <vector>
#include "tlhelp32.h"

using namespace std;

struct PROCESS
{
	PROCESSENTRY32 proc;
	vector<MODULEENTRY32> list_mod;
};


// диалоговое окно FORM_FIND

IMPLEMENT_DYNAMIC(FORM_FIND, CDialogEx)

FORM_FIND::FORM_FIND(CWnd* pParent /*=NULL*/)
	: CDialogEx(FORM_FIND::IDD, pParent)
	, Edit1(_T(""))
{

}

FORM_FIND::~FORM_FIND()
{
}

void FORM_FIND::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ComboBox1);
	DDX_Text(pDX, IDC_EDIT1, Edit1);
}


BEGIN_MESSAGE_MAP(FORM_FIND, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &FORM_FIND::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений FORM_FIND


void FORM_FIND::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	ComboBox1.Clear();
	ComboBox1.AddString(TEXT("PID"));
	ComboBox1.AddString(TEXT("Название процесса"));
	ComboBox1.AddString(TEXT("PID родителя"));
	ComboBox1.AddString(TEXT("Потоки"));
	ComboBox1.SetCurSel(0);
}


void FORM_FIND::OnBnClickedOk()
{
	UpdateData(true);
	FORM_MAIN* f=(FORM_MAIN*)f_main;

	f->m_ListP.DeleteAllItems();
	vector<PROCESS>* list=(vector<PROCESS>*)f->list_proc;

	int sel=ComboBox1.GetCurSel();

	vector<PROCESS>::iterator it;
	unsigned long i=0;
	
	for (it=list->begin();it!=list->end();it++)
	{
		switch (sel)
		{
			case 0:
			{	
				unsigned long b=_tstoi(Edit1.GetString());
				//MessageBox(Edit1);
				//MessageBox(str);
				if (it->proc.th32ProcessID==b)
				{
					CString str;
					str.Format(TEXT("%d"),it->proc.th32ProcessID);
					f->m_ListP.InsertItem(i,str);
					str.Format(TEXT("%s"),it->proc.szExeFile);
					f->m_ListP.SetItemText(i,1,str);
					str.Format(TEXT("%d"),it->proc.th32ParentProcessID);
					f->m_ListP.SetItemText(i,2,str);
					str.Format(TEXT("%d"),it->proc.cntThreads);
					f->m_ListP.SetItemText(i,3,str);
					str.Format(TEXT("%d"),it->proc.pcPriClassBase);
					f->m_ListP.SetItemText(i,4,str);
					i++;
				}
				break;
			}
			case 1:
			{
				unsigned long b=_tstoi(Edit1.GetString());
				if (b==it->proc.th32ParentProcessID)
				{
					CString str;
					str.Format(TEXT("%d"),it->proc.th32ProcessID);
					f->m_ListP.InsertItem(i,str);
					str.Format(TEXT("%s"),it->proc.szExeFile);
					f->m_ListP.SetItemText(i,1,str);
					str.Format(TEXT("%d"),it->proc.th32ParentProcessID);
					f->m_ListP.SetItemText(i,2,str);
					str.Format(TEXT("%d"),it->proc.cntThreads);
					f->m_ListP.SetItemText(i,3,str);
					str.Format(TEXT("%d"),it->proc.pcPriClassBase);
					f->m_ListP.SetItemText(i,4,str);
					i++;
				}
				break;
			}
			case 2:
			{
				CString str;str.Format(TEXT("%s"),it->proc.szExeFile);
				if (Edit1.CompareNoCase(str)==0)
				{
					CString str;
					str.Format(TEXT("%d"),it->proc.th32ProcessID);
					f->m_ListP.InsertItem(i,str);
					str.Format(TEXT("%s"),it->proc.szExeFile);
					f->m_ListP.SetItemText(i,1,str);
					str.Format(TEXT("%d"),it->proc.th32ParentProcessID);
					f->m_ListP.SetItemText(i,2,str);
					str.Format(TEXT("%d"),it->proc.cntThreads);
					f->m_ListP.SetItemText(i,3,str);
					str.Format(TEXT("%d"),it->proc.pcPriClassBase);
					f->m_ListP.SetItemText(i,4,str);
					i++;
				}
				break;
			}
			case 3:
			{
				unsigned long b=_tstoi(Edit1.GetString());
				if (b==it->proc.cntThreads)
				{
					CString str;
					str.Format(TEXT("%d"),it->proc.th32ProcessID);
					f->m_ListP.InsertItem(i,str);
					str.Format(TEXT("%s"),it->proc.szExeFile);
					f->m_ListP.SetItemText(i,1,str);
					str.Format(TEXT("%d"),it->proc.th32ParentProcessID);
					f->m_ListP.SetItemText(i,2,str);
					str.Format(TEXT("%d"),it->proc.cntThreads);
					f->m_ListP.SetItemText(i,3,str);
					str.Format(TEXT("%d"),it->proc.pcPriClassBase);
					f->m_ListP.SetItemText(i,4,str);
					i++;
				}
				break;
			}
		}
		
	}
	
	//if (ComboBox1.GetCurSel()==0)
	//{
	//	TCHAR str[1024]=TEXT("3224");

	//	//TCHAR* str=Edit1.GetString()
	//	LVFINDINFO find;
	//	find.flags=LVFI_PARTIAL|LVFI_STRING;
	//	find.psz=&str[0];
	//	int it;
	//	if ((it=f->m_ListP.FindItem(&find))!=-1)
	//	{
	//		f->m_ListP.SetItemState(it,LVIS_SELECTED,LVIS_SELECTED);
	//		f->m_ListP.EnsureVisible(it,false);
	//		MessageBox(TEXT("YES"));
	//	}else
	//		MessageBox(TEXT("Нет такого процесса!"));
	//}
	//if (ComboBox1.GetCurSel()==1)
	//{
	//	TCHAR str[1024]=TEXT("456");

	//	//TCHAR* str=Edit1.GetString()
	//	LVFINDINFO find;
	//	find.flags=LVFI_PARTIAL|LVFI_STRING;
	//	find.lParam=2;
	//	find.psz=&str[0];
	//	int it;
	//	if ((it=f->m_ListP.FindItem(&find))!=-1)
	//	{
	//		f->m_ListP.SetItemState(it,LVIS_SELECTED,LVIS_SELECTED);
	//		f->m_ListP.SetSelectionMark(it);
	//		f->m_ListP.EnsureVisible(it,false);
	//		MessageBox(TEXT("YES"));
	//	}else
	//		MessageBox(TEXT("Нет такого процесса!"));
	//}


	CDialogEx::OnOK();
}
