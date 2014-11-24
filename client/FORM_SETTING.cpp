// FORM_SETTING.cpp: файл реализации
//

#include "stdafx.h"
#include "client.h"
#include "FORM_SETTING.h"
#include "MAIN.h"
#include "afxdialogex.h"


// диалоговое окно FORM_SETTING

IMPLEMENT_DYNAMIC(FORM_SETTING, CDialogEx)

FORM_SETTING::FORM_SETTING(CWnd* pParent /*=NULL*/)
	: CDialogEx(FORM_SETTING::IDD, pParent)
{

	m_Edit1 = _T("");
	m_Edit2 = 0;
	m_Edit3 = 0;
}

FORM_SETTING::~FORM_SETTING()
{
}

void FORM_SETTING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	//  DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	//  DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Edit3);
}


BEGIN_MESSAGE_MAP(FORM_SETTING, CDialogEx)
//	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &FORM_SETTING::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений FORM_SETTING


void FORM_SETTING::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	FORM_MAIN* t=(FORM_MAIN*)f_main;
	m_Edit1=t->ip;
	UpdateData(false);
	m_Edit2=t->port;
	UpdateData(false);
	m_Edit3=t->t_out;
	UpdateData(false);
}


void FORM_SETTING::OnBnClickedOk()
{
	FORM_MAIN* t=(FORM_MAIN*)f_main;
	UpdateData(true);
	t->ip=m_Edit1;
	UpdateData(true);
	t->port=m_Edit2;
	UpdateData(true);
	t->t_out=m_Edit3;

	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileString(TEXT(""),TEXT("ip"),t->ip);
	pApp->WriteProfileInt(TEXT(""),TEXT("port"),t->port);
	pApp->WriteProfileInt(TEXT(""),TEXT("time_out"),t->t_out);
	CDialogEx::OnOK();
}
