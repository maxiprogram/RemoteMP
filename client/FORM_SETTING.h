#pragma once


// ���������� ���� FORM_SETTING

class FORM_SETTING : public CDialogEx
{
	DECLARE_DYNAMIC(FORM_SETTING)

public:
	FORM_SETTING(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~FORM_SETTING();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void* f_main;
	CString m_Edit1;
	UINT m_Edit2;
	UINT m_Edit3;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
};
