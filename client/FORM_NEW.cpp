// FORM_NEW.cpp: файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "FORM_NEW.h"
#include "MAIN.h"
#include "afxdialogex.h"


// диалоговое окно FORM_NEW

IMPLEMENT_DYNAMIC(FORM_NEW, CDialogEx)

FORM_NEW::FORM_NEW(CWnd* pParent /*=NULL*/)
	: CDialogEx(FORM_NEW::IDD, pParent)
	, Edit1(_T(""))
{

}

FORM_NEW::~FORM_NEW()
{
}

void FORM_NEW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Edit1);
	DDV_MaxChars(pDX, Edit1, 1024);
}


BEGIN_MESSAGE_MAP(FORM_NEW, CDialogEx)
	ON_BN_CLICKED(IDOK, &FORM_NEW::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений FORM_NEW


void FORM_NEW::OnBnClickedOk()
{
	UpdateData(true);
	FORM_MAIN* f=(FORM_MAIN*)f_main;
	if (f->socket!=NULL)
	{
		CSocket* s=(CSocket*)f->socket;
		unsigned long cmd=0x0033;
		s->Send(&cmd,sizeof(cmd));
		s->Send(Edit1,sizeof(TCHAR)*1024,0);
	}

	CDialogEx::OnOK();
}