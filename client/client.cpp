
// client.cpp : ���������� ��������� ������� ��� ����������.
//

#include "stdafx.h"
#include "client.h"
#include "MAIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClientApp

BEGIN_MESSAGE_MAP(ClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// �������� ClientApp

ClientApp::ClientApp()
{
	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ ClientApp

ClientApp theApp;


// ������������� ClientApp

BOOL ClientApp::InitInstance()
{
	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������. � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// ������� ��������� ��������, � ������, ���� ���������� ���� ��������
	// ������������� ������ �������� ��� �����-���� ��� �������� ����������.
	CShellManager *pShellManager = new CShellManager;

	// ����������� �������������
	// ���� ��� ����������� �� ������������ � ���������� ��������� ������
	// ��������� ������������ �����, ���������� ������� �� ���������
	// ���������� �������� �������������, ������� �� ���������
	// �������� ������ �������, � ������� �������� ���������
	// TODO: ������� �������� ��� ������ �� ���-������ ����������,
	// �������� �� �������� �����������
	FORM_MAIN dlg;
	SetRegistryKey(TEXT("TihonovM"));
	dlg.ip=GetProfileString(TEXT(""),TEXT("ip"));
	if (dlg.ip=="")
	{
		dlg.ip="127.0.0.1";
		WriteProfileString(TEXT(""),TEXT("ip"),TEXT("127.0.0.1"));
	}
	dlg.port=GetProfileInt(TEXT(""),TEXT("port"),0);
	if (dlg.port==0)
	{
		dlg.port=2207;
		WriteProfileInt(TEXT(""),TEXT("port"),2207);
	}
	dlg.t_out=GetProfileInt(TEXT(""),TEXT("time_out"),0);
	if (dlg.t_out==0)
	{
		dlg.t_out=60000;
		WriteProfileInt(TEXT(""),TEXT("time_out"),60000);
	}

	
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "��"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ������� ��� ��� ��������� �������� ����������� ����
		//  � ������� ������ "������"
	}

	// ������� ��������� ��������, ��������� ����.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������� ���������� ���� �������, ���������� �������� FALSE, ����� ����� ���� ����� ��
	//  ���������� ������ ������� ���������� ��������� ����������.
	return FALSE;
}

