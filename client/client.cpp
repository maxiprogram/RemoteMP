
// client.cpp : Определяет поведение классов для приложения.
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


// создание ClientApp

ClientApp::ClientApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект ClientApp

ClientApp theApp;


// инициализация ClientApp

BOOL ClientApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения. В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
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
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

