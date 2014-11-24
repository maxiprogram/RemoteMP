#pragma once
#include "afxwin.h"


// диалоговое окно FORM_FIND

class FORM_FIND : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_FIND)

public:
	FORM_FIND(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~FORM_FIND();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void* f_main;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CComboBox ComboBox1;
	afx_msg void OnBnClickedOk();
	CString Edit1;
};
