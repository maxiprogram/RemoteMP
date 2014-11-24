#pragma once
#include "afxwin.h"


// диалоговое окно FORM_PRIOR

class FORM_PRIOR : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_PRIOR)

public:
	FORM_PRIOR(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~FORM_PRIOR();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void* f_main;
	CComboBox ComboBox1;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
};
