
// MAIN.h : файл заголовка
//

#pragma once

#define ID_TIMER 1234

// диалоговое окно FORM_MAIN
class FORM_MAIN : public CDialogEx
{
// Создание
public:
	FORM_MAIN(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void* list_proc;
	void* socket; 
	CString ip;
	unsigned long port;
	unsigned long t_out;
	CListCtrl m_ListP;
	CListCtrl m_ListM;
	void ClearListProc();
	void PrintProc();
	void PrintModule(unsigned long pid);
	void StartTimer()
	{
		SetTimer(ID_TIMER,t_out,NULL);
	};
	afx_msg void On32775();
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void On32776();
	afx_msg void OnClose();
	afx_msg void On32774();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32773();
	afx_msg void On32778();
	afx_msg void On32777();
};
