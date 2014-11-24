#pragma once
#include "afxwin.h"


// диалоговое окно FORM_NEW

class FORM_NEW : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_NEW)

public:
	FORM_NEW(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~FORM_NEW();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString Edit1;
	void* f_main;
};
