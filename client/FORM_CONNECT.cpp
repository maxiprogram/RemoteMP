// FORM_CONNECT.cpp: файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "FORM_CONNECT.h"
#include "MAIN.h"
#include "Client_Socket.h"
#include "afxdialogex.h"


// диалоговое окно FORM_CONNECT

IMPLEMENT_DYNAMIC(FORM_CONNECT, CDialogEx)

FORM_CONNECT::FORM_CONNECT(CWnd* pParent /*=NULL*/)
	: CDialogEx(FORM_CONNECT::IDD, pParent)
{

	m_Edit1 = _T("");
}

FORM_CONNECT::~FORM_CONNECT()
{
}

void FORM_CONNECT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
}


BEGIN_MESSAGE_MAP(FORM_CONNECT, CDialogEx)
	ON_BN_CLICKED(IDOK, &FORM_CONNECT::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// обработчики сообщений FORM_CONNECT


void FORM_CONNECT::OnBnClickedOk()
{
	FORM_MAIN* t=(FORM_MAIN*)f_main;
	Client_Socket* b;
	if (t->socket!=NULL)
	{
		b=(Client_Socket*)t->socket;
		b->Close();
		delete b;
		t->socket=new Client_Socket(t);
	}
	else
		t->socket=new Client_Socket(t);
	b=(Client_Socket*)t->socket;
	b->Create();
	if (b->Connect(m_Edit1,t->port))
	{
		t->SetWindowText(TEXT("Удаленный диспетчер --Есть подключение--"));
		MessageBox(TEXT("Удачное подключение"),TEXT("Подключение"),0);
		//t->StartTimer();
		//unsigned long tmp=0x0011;
		//b->Send(&tmp,sizeof(unsigned long));
	}
	else
	{
		t->SetWindowText(TEXT("Удаленный диспетчер --Нет подключения!--"));
		MessageBox(TEXT("Ошибка подключения!"),TEXT("Ошибка!"),0);
	}

	CDialogEx::OnOK();
}


void FORM_CONNECT::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	FORM_MAIN* t=(FORM_MAIN*)f_main;
	m_Edit1=t->ip;
	UpdateData(false);
}
