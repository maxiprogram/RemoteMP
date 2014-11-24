#pragma once


// диалоговое окно FORM_SETTING

class FORM_SETTING : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_SETTING)

public:
	FORM_SETTING(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~FORM_SETTING();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void* f_main;
	CString m_Edit1;
	UINT m_Edit2;
	UINT m_Edit3;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
};
