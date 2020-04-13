#pragma once

#include "stdafx.h"
#include "afxwin.h"
// CInputDialog �Ի���

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
	CInputDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputDialog();

	int ShowInput(wstring* url);
	

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	
	CButton m_Etr;
	CEdit m_Edt;
	wstring m_Text;
};
