#pragma once
#include "afxwin.h"


// ���������� ���� FORM_PRIOR

class FORM_PRIOR : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_PRIOR)

public:
	FORM_PRIOR(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~FORM_PRIOR();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void* f_main;
	CComboBox ComboBox1;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
};
