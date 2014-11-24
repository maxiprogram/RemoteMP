#pragma once


// диалоговое окно FORM_CONNECT

class FORM_CONNECT : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_CONNECT)

public:
	FORM_CONNECT(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~FORM_CONNECT();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void* f_main;
	afx_msg void OnBnClickedOk();
	CString m_Edit1;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
